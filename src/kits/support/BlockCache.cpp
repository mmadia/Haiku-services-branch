/*
 * Copyright (c) 2003 Marcus Overhagen
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a 
 * copy of this software and associated documentation files (the "Software"), 
 * to deal in the Software without restriction, including without limitation 
 * the rights to use, copy, modify, merge, publish, distribute, sublicense, 
 * and/or sell copies of the Software, and to permit persons to whom the 
 * Software is furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in 
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING 
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER 
 * DEALINGS IN THE SOFTWARE.
 */

#include <BlockCache.h>
#include <Debug.h>
#include <string.h>
#include <malloc.h>
#include <new>

#define MAGIC1		0x9183f4d9
#define MAGIC2		0xa6b3c87d

// The requirements set by the BeBook's description of the destructor,
// as well as Get() function, allowing the caller to dispose of the
// memory, do not allow to allocate one large block to be used as pool.
// Thus we need to create multiple small ones.
// We maintain a list of free blocks. If more blocks with a size of blockSize
// are allocated than available, the variable fExcessBlocks is used to avoid
// growing the pool of free buffers

// XXX the BeBook describes the first parameter of the constructor as
// XXX "size_t count", while the original BeOS header uses "size_t cache_size"
// XXX this are very different meanings

BBlockCache::BBlockCache(size_t cacheSize,
						 size_t blockSize,
						 uint32 allocationType)
 :	fFreeList(0),
 	fBlockSize(blockSize),
 	fExcessBlocks(0),
	fLocker(),
	fAlloc(0),
	fFree(0) 
{
	if (cacheSize < blockSize)
		debugger("Error, you can't create a BBlockCache with cacheSize < blockSize\n");

	switch (allocationType) {
		case B_OBJECT_CACHE:
			fAlloc = &operator new[];
			fFree = &operator delete[];
			break;
		case B_MALLOC_CACHE:
			fAlloc = &malloc;
			fFree = &free;
			break;
		default:
			debugger("Error, you can't create a BBlockCache with undefined allocationType\n");
	}

	// To properly maintain a list of free buffers, a buffer must be
	// large enough to contain the _FreeBlock struct that is used.
	if (blockSize < sizeof(_FreeBlock))
		blockSize = sizeof(_FreeBlock);
		
	// create blocks and put them into the free list
	int count = cacheSize / blockSize;
	for (int i = 0; i < count; i++) {
		_FreeBlock *block = reinterpret_cast<_FreeBlock *>(fAlloc(blockSize));
		if (!block)
			break;
		block->next = fFreeList;
		fFreeList = block;
		DEBUG_ONLY(block->magic1 = MAGIC1);
		DEBUG_ONLY(block->magic2 = MAGIC2 + (uint32)block->next);
	}
}

BBlockCache::~BBlockCache()
{
	// walk the free list and deallocate all blocks
	fLocker.Lock();
	while (fFreeList) {
		ASSERT(fFreeList->magic1 == MAGIC1);
		ASSERT(fFreeList->magic2 == MAGIC2 + (uint32)fFreeList->next);
		void *pointer = fFreeList;
		fFreeList = fFreeList->next;
		DEBUG_ONLY(memset(pointer, 0xCC, sizeof(_FreeBlock)));
		fFree(pointer);
	}
	fLocker.Unlock();
}

void *
BBlockCache::Get(size_t blockSize)
{
	if (!fLocker.Lock())
		return 0;
	void *pointer;
	if (blockSize == fBlockSize && fFreeList != 0) {
		// we can take a block from the list
		ASSERT(fFreeList->magic1 == MAGIC1);
		ASSERT(fFreeList->magic2 == MAGIC2 + (uint32)fFreeList->next);
		pointer = fFreeList;
		fFreeList = fFreeList->next;
		DEBUG_ONLY(memset(pointer, 0xCC, sizeof(_FreeBlock)));
	} else {
		// we need to allocate a new block
		if (blockSize == fBlockSize) {
			// we now have one more block than wanted
			fExcessBlocks++;
		}
		if (blockSize < sizeof(_FreeBlock))
			blockSize = sizeof(_FreeBlock);
		pointer = fAlloc(blockSize);
		DEBUG_ONLY(if (pointer) memset(pointer, 0xCC, sizeof(_FreeBlock)));
	}
	fLocker.Unlock();
	return pointer;
}

void
BBlockCache::Save(void *pointer, size_t blockSize)
{
	if (!fLocker.Lock())
		return;
	if (blockSize == fBlockSize && fExcessBlocks <= 0) {
		// the block needs to be returned to the cache
		_FreeBlock *block = reinterpret_cast<_FreeBlock *>(pointer);
		block->next = fFreeList;
		fFreeList = block;
		DEBUG_ONLY(block->magic1 = MAGIC1);
		DEBUG_ONLY(block->magic2 = MAGIC2 + (uint32)block->next);
	} else {
		// the block needs to be deallocated
		if (blockSize == fBlockSize) {
			fExcessBlocks--;
			ASSERT(fExcessBlocks >= 0);
		}
		DEBUG_ONLY(memset(pointer, 0xCC, sizeof(_FreeBlock)));
		fFree(pointer);
	}
	fLocker.Unlock();
}
