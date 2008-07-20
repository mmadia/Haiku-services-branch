/*
 * Copyright 2004-2007, Axel Dörfler, axeld@pinc-software.de.
 * Based on code written by Travis Geiselbrecht for NewOS.
 *
 * Distributed under the terms of the MIT License.
 */


#include "mmu.h"

#include <boot/platform.h>
#include <boot/stdio.h>
#include <boot/kernel_args.h>
#include <boot/stage2.h>
#include <arch/cpu.h>
#include <arch_kernel.h>
#include <kernel.h>

#include <OS.h>

#include <string.h>

#include "arch_040_mmu.h"


#define TRACE_MMU
#ifdef TRACE_MMU
#	define TRACE(x) dprintf x
#else
#	define TRACE(x) ;
#endif


extern page_root_entry *gPageRoot;


static void
initialize(void)
{
	TRACE(("mmu_040:initialize\n"));
	//XXX TESTING for bitfield order
	long_page_directory_entry ent;
	*(uint64 *)&ent = 0LL;
	TRACE(("ent: %llx [0] %02x\n", ent, *(uint8 *)&ent));
	ent.type=3;
	TRACE(("ent: %llx [0] %02x\n", ent, *(uint8 *)&ent));
	ent.addr = 0x0aaaaaaa;
	TRACE(("ent: %llx [0] %02x\n", ent, *(uint8 *)&ent));
}


static status_t
set_tt(int which, addr_t pa, size_t len, uint32 perms /* NOTUSED */)
{
	TRACE(("mmu_040:set_tt(%d, 0x%lx, 0x%lx, 0x%08lx)\n", which, pa, len, perms));
	uint32 mask;
	uint32 ttr = 0;
	mask = 0x0000ffff;
	if (len) {
		len = (len >> 24) & 0x00ff;
		while (len >>= 1)
			mask <<= 1;
		// enable, super only, upa=0,
		// cachable write-through, rw
		ttr = 0x0a000;
		ttr |= (pa & 0xff000000);
		ttr |= (mask & 0x00ff0000);
	}
	TRACE(("mmu_040:set_tt: 0x%08lx\n", ttr));
	

	switch (which) {
		case 0:
			asm volatile(  \
				"movec %0,%%dtt0\n"				\
				"movec %0,%%itt0\n"				\
				: : "d"(ttr));
			break;
		case 1:
			asm volatile(  \
				"movec %0,%%dtt1\n"				\
				"movec %0,%%itt1\n"				\
				: : "d"(ttr));
			break;
		default:
			return EINVAL;
	}
	return B_OK;
}


static status_t
load_rp(addr_t pa)
{
	TRACE(("mmu_040:load_rp(0x%lx)\n", pa));
	// sanity check
	if (pa & ((1 << 9) - 1)) {
		panic("mmu root pointer missaligned!");
		return EINVAL;
	}
	/* mc68040 user's manual, 6-37 */
	/* pflush before... why not after ? */
	asm volatile(		   \
		"pflusha\n"		   \
		"movec %0,%%srp\n" \
		"movec %0,%%urp\n" \
		"pflusha\n"		   \
		: : "d"(pa));
	return B_OK;
}


static status_t
enable_paging(void)
{
	TRACE(("mmu_040:enable_paging\n"));
	uint16 tcr = 0x8000; // Enable, 4K page size
	asm volatile( \
		"pflusha\n"		   \
		"movec %0,%%tcr\n" \
		"pflusha\n"		   \
		: : "d"(tcr));
	return B_OK;
}


static status_t
add_page_table(addr_t virtualAddress)
{
	page_root_entry *pr = gPageRoot;
	page_directory_entry *pd;
	page_table_entry *pt;
	addr_t tbl;
	uint32 index;
	uint32 i;
	
	TRACE(("mmu->add_page_table(base = %p)\n", (void *)virtualAddress));

	// everything much simpler here because pa = va
	// thanks to transparent translation

	index = VADDR_TO_PRENT(virtualAddress);
	if (pr[index].type != DT_ROOT) {
		unsigned aindex = index & ~(NUM_DIRTBL_PER_PAGE-1); /* aligned */
		TRACE(("missing page root entry %d ai %d\n", index, aindex));
		tbl = mmu_get_next_page_tables();
		if (!tbl)
			return ENOMEM;
		// for each pgdir on the allocated page:
		for (i = 0; i < NUM_DIRTBL_PER_PAGE; i++) {
			page_root_entry *apr = &pr[aindex + i];
			apr->addr = TA_TO_PREA(tbl);
			apr->type = DT_ROOT;
			TRACE(("inserting tbl @ %p as %08x entry %08x\n", tbl, TA_TO_PREA(tbl), *(uint32 *)apr));
			// clear the table
			TRACE(("clearing table[%d]\n", i));
			pd = (page_directory_entry *)tbl;
			for (int32 j = 0; j < NUM_DIRENT_PER_TBL; j++)
				*(page_directory_entry_scalar *)(&pd[j]) = DFL_DIRENT_VAL;
			tbl += SIZ_DIRTBL;
		}
	}
	TRACE(("B %08lx\n", PRE_TO_TA(pr[index])));
	pd = (page_directory_entry *)PRE_TO_TA(pr[index]);
	TRACE(("C\n"));

	index = VADDR_TO_PDENT(virtualAddress);
	TRACE(("checking pgdir@%p[%d]\n", pd, index));
	if (pd[index].type != DT_DIR) {
		unsigned aindex = index & ~(NUM_PAGETBL_PER_PAGE-1); /* aligned */
		TRACE(("missing page dir entry %d ai %d\n", index, aindex));
		tbl = mmu_get_next_page_tables();
		if (!tbl)
			return ENOMEM;
		// for each pgdir on the allocated page:
		for (i = 0; i < NUM_PAGETBL_PER_PAGE; i++) {
			page_directory_entry *apd = &pd[aindex + i];
			apd->addr = TA_TO_PDEA(tbl);
			apd->type = DT_DIR;
			// clear the table
			TRACE(("clearing table[%d]\n", i));
			pt = (page_table_entry *)tbl;
			for (int32 j = 0; j < NUM_PAGEENT_PER_TBL; j++)
				*(page_table_entry_scalar *)(&pt[j]) = DFL_PAGEENT_VAL;
			tbl += SIZ_PAGETBL;
		}
	}
#if 0
	pt = PDE_TO_TA(pd[index]);

	index = VADDR_TO_PTENT(virtualAddress);
	pt[index].addr = TA_TO_PTEA(0xdeadb00b);
	pt[index].supervisor = 1;
	pt[index].type = DT_PAGE;
#endif
	return B_OK;
}


static page_table_entry *
lookup_pte(addr_t virtualAddress)
{
	page_root_entry *pr = gPageRoot;
	page_directory_entry *pd;
	page_table_entry *pt;
	uint32 index;

	index = VADDR_TO_PRENT(virtualAddress);
	if (pr[index].type != DT_ROOT)
		panic("lookup_pte: invalid page root entry %d", index);
	pd = (page_directory_entry *)PRE_TO_TA(pr[index]);

	index = VADDR_TO_PDENT(virtualAddress);
	if (pd[index].type != DT_DIR)
		panic("lookup_pte: invalid page directory entry %d", index);
	pt = (page_table_entry *)PDE_TO_TA(pd[index]);
	
	index = VADDR_TO_PTENT(virtualAddress);
	if (pt[index].type != DT_PAGE)
		panic("lookup_pte: invalid page table entry %d", index);

	return (&pt[index]);
}


static void
unmap_page(addr_t virtualAddress)
{
	page_table_entry *pt;

	TRACE(("mmu->unmap_page(virtualAddress = %p)\n", (void *)virtualAddress));

	if (virtualAddress < KERNEL_BASE)
		panic("unmap_page: asked to unmap invalid page %p!\n", (void *)virtualAddress);

	// unmap the page from the correct page table
	pt = lookup_pte(virtualAddress);

	pt->addr = TA_TO_PTEA(0xdeadb00b);
	pt->type = DT_INVALID;

	asm volatile("pflush (%0)" : : "a" (virtualAddress));
}


/** insert the physical address into existing page table */
static void
map_page(addr_t virtualAddress, addr_t physicalAddress, uint32 flags)
{
	page_table_entry *pt;

	TRACE(("mmu->map_page: vaddr 0x%lx, paddr 0x%lx\n", virtualAddress, physicalAddress));


	physicalAddress &= ~(B_PAGE_SIZE - 1);

	// map the page to the correct page table

	pt = lookup_pte(virtualAddress);

	TRACE(("map_page: inserting pageTableEntry %p, physicalAddress %p\n", 
		pt, physicalAddress));


	pt->addr = TA_TO_PTEA(physicalAddress);
	pt->supervisor = 1;
	pt->type = DT_PAGE;
	// XXX: are flags needed ? ro ? global ?

	asm volatile("pflush (%0)" : : "a" (virtualAddress));
	TRACE(("mmu->map_page: done\n"));
}




const struct boot_mmu_ops k040MMUOps = {
	&initialize,
	&set_tt,
	&load_rp,
	&enable_paging,
	&add_page_table,
	&unmap_page,
	&map_page
};
