/*
 * Copyright 2005, Ingo Weinhold <bonefish@cs.tu-berlin.de>.
 * All rights reserved. Distributed under the terms of the MIT License.
 */

#include <new>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <OS.h>

#include <boot/net/Ethernet.h>
#include <boot/net/NetStack.h>
#include <platform/openfirmware/openfirmware.h>


//#define TRACE_NETWORK
#ifdef TRACE_NETWORK
#	define TRACE(x) dprintf x
#else
#	define TRACE(x) ;
#endif


#ifdef TRACE_NETWORK

static void
hex_dump(const void *_data, int length)
{
	uint8 *data = (uint8*)_data;
	for (int i = 0; i < length; i++) {
		if (i % 4 == 0) {
			if (i % 32 == 0) {
				if (i != 0)
					printf("\n");
				printf("%03x: ", i);
			} else
				printf(" ");
		}

		printf("%02x", data[i]);
	}
	printf("\n");
}

#else	// !TRACE_NETWORK

#define hex_dump(data, length)

#endif	// !TRACE_NETWORK


static int
parse_ip_address_component(const char *sz, int len)
{
	const int base = 10;
		// only decimal numbers for now
	int r = 0;
	for (int i = 0; i < len; i++) {
		int x = sz[i] - '0';
		for (int j = 1; j < len - i; j++)
			x *= base;
		r += x;
	}
	return r;
}


static ip_addr_t
parse_ip_address(const char *sz)
{
	ip_addr_t addr = 0;
	int i = 0;
	const char *psz = sz;
	// TODO: Handles only IPv4 addresses for now.
	char *p = strchr(psz, '.');
	while (p != NULL && i < 4) {
		int len = p - psz;
		addr |= parse_ip_address_component(psz, len) << ((4 - i - 1) * 8);
		p = strchr(psz = p + 1, '.');
		i++;
	}
	addr |= parse_ip_address_component(psz, sz + strlen(sz) - psz);
	return addr;
}


class OFEthernetInterface : public EthernetInterface {
public:
	OFEthernetInterface();
	virtual ~OFEthernetInterface();

	status_t Init(const char *device);

	virtual mac_addr_t MACAddress() const;

	virtual	void *AllocateSendReceiveBuffer(size_t size);
	virtual	void FreeSendReceiveBuffer(void *buffer);

	virtual ssize_t Send(const void *buffer, size_t size);
	virtual ssize_t Receive(void *buffer, size_t size);

private:
	int			fHandle;
	mac_addr_t	fMACAddress;
};

// constructor
OFEthernetInterface::OFEthernetInterface()
	: EthernetInterface(),
	  fHandle(OF_FAILED),
	  fMACAddress(kNoMACAddress)
{
}

// destructor
OFEthernetInterface::~OFEthernetInterface()
{
	if (fHandle != OF_FAILED)
		of_close(fHandle);
}

// Init
status_t
OFEthernetInterface::Init(const char *device)
{
	if (!device)
		return B_BAD_VALUE;

	// open device
	fHandle = of_open(device);
	if (fHandle == OF_FAILED) {
		printf("opening ethernet device failed\n");
		return B_ERROR;
	}

	int package = of_instance_to_package(fHandle);

	// get MAC address
	int bytesRead = of_getprop(package, "local-mac-address", &fMACAddress,
		sizeof(fMACAddress));
	if (bytesRead == OF_FAILED || bytesRead < (int)sizeof(fMACAddress)) {
		// Failed to get the MAC address of the network device. The system may
		// have a global standard MAC address.
		bytesRead = of_getprop(gChosen, "mac-address", &fMACAddress,
			sizeof(fMACAddress));
		if (bytesRead == OF_FAILED || bytesRead < (int)sizeof(fMACAddress)) {
			printf("Failed to get MAC address\n");
			return B_ERROR;
		}
	}

	// get IP address
	// Note: This is a non-standardized way. On my Mac mini the response of the
	// DHCP server is stored as property of /chosen. We try to get that it and
	// use the IP address we find in there.
	struct {
		uint8	irrelevant[16];
		uint32	ip_address;
		// ...
	} dhcpResponse;
	bytesRead = of_getprop(gChosen, "dhcp-response", &dhcpResponse,
		sizeof(dhcpResponse));
	if (bytesRead != OF_FAILED && bytesRead == (int)sizeof(dhcpResponse)) {
		SetIPAddress(ntohl(dhcpResponse.ip_address));
	} else {
		char saddr[16];
		package = of_finddevice("/options");
		bytesRead = of_getprop(package, "default-client-ip", saddr, sizeof(saddr));
		if (bytesRead != OF_FAILED) {
			saddr[bytesRead] = '\0';
			printf("default-client-ip: %s\n", saddr);
			ip_addr_t addr = parse_ip_address(saddr);
			printf("addr = %x\n", (unsigned int)addr);
			SetIPAddress(addr);
		}
	}

	return B_OK;
}

// MACAddress
mac_addr_t
OFEthernetInterface::MACAddress() const
{
	return fMACAddress;
}

// AllocateSendReceiveBuffer
void *
OFEthernetInterface::AllocateSendReceiveBuffer(size_t size)
{
	void *dmaMemory;
	if (of_call_method(fHandle, "dma-alloc", 1, 1, size, &dmaMemory)
			== OF_FAILED) {
		return NULL;
	}
	return dmaMemory;
}

// FreeSendReceiveBuffer
void
OFEthernetInterface::FreeSendReceiveBuffer(void *buffer)
{
	if (buffer)
		of_call_method(fHandle, "dma-free", 1, 0, buffer);
}

// Send
ssize_t
OFEthernetInterface::Send(const void *buffer, size_t size)
{
	TRACE(("OFEthernetInterface::Send(%p, %lu)\n", buffer, size));

	if (!buffer)
		return B_BAD_VALUE;

	hex_dump(buffer, size);

	int result = of_write(fHandle, buffer, size);
	return (result == OF_FAILED ? B_ERROR : result);
}

// Receive
ssize_t
OFEthernetInterface::Receive(void *buffer, size_t size)
{
	if (!buffer)
		return B_BAD_VALUE;

	int result = of_read(fHandle, buffer, size);

	if (result != OF_FAILED && result >= 0) {
		TRACE(("OFEthernetInterface::Receive(%p, %lu): received %d bytes\n",
			buffer, size, result));
		hex_dump(buffer, result);
	}

	return (result == OF_FAILED ? B_ERROR : result);
}


// #pragma mark -

// platform_net_stack_init
status_t
platform_net_stack_init()
{
	// Note: At the moment we only do networking at all, if the boot device
	// is a network device. If it isn't, we simply fail here. For serious
	// support we would want to iterate through the device tree and add all
	// network devices.

	// get boot path
	char bootPath[192];
	int length = of_getprop(gChosen, "bootpath", bootPath, sizeof(bootPath));
	if (length <= 1)
		return B_ERROR;

	// we chop off parameters; otherwise opening the network device might have
	// side effects
	char *lastComponent = strrchr(bootPath, '/');
	char *parameters = strchr((lastComponent ? lastComponent : bootPath), ':');
	if (parameters)
		*parameters = '\0';

	// get device node
	int node = of_finddevice(bootPath);
	if (node == OF_FAILED)
		return B_ERROR;

	// get device type
	char type[16];
	if (of_getprop(node, "device_type", type, sizeof(type)) == OF_FAILED
		|| strcmp("network", type) != 0) {
		return B_ERROR;
	}

	// create an EthernetInterface object for the device
	OFEthernetInterface *interface = new(nothrow) OFEthernetInterface;
	if (!interface)
		return B_NO_MEMORY;

	status_t error = interface->Init(bootPath);
	if (error != B_OK) {
		delete interface;
		return error;
	}

	// add it to the net stack
	error = NetStack::Default()->AddEthernetInterface(interface);
	if (error != B_OK) {
		delete interface;
		return error;
	}

	return B_OK;
}
