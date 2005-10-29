#ifndef BOOT_BLOCK_DATA_H
#define BOOT_BLOCK_DATA_H

// Note: the boot block here is taken directly from my main BFS disk.
// There is no Haiku replacement for that code yet!

static uint8 sBootBlockData1[512] = {
	0xb8, 0x00, 0x90, 0x8e, 0xd0, 0x89, 0xc4, 0xfc, 0x68, 0xc0, 0x07, 0x1f, 0x1e, 0x07, 0x80, 0xfa, 
	0x02, 0x72, 0x0c, 0x80, 0xfa, 0x80, 0x72, 0x05, 0x80, 0xfa, 0x90, 0x72, 0x02, 0xb2, 0x80, 0x66, 
	0x31, 0xc0, 0x40, 0xbb, 0x00, 0x02, 0xe8, 0x7e, 0x00, 0x81, 0x7f, 0x20, 0x31, 0x53, 0x75, 0x75, 
	0x80, 0xbf, 0xff, 0x01, 0x20, 0x75, 0x6e, 0xbe, 0x74, 0x02, 0xe8, 0x82, 0x01, 0xe8, 0xa3, 0x02, 
	0xbf, 0x07, 0x03, 0xbb, 0x00, 0x06, 0x57, 0xe8, 0xf5, 0x00, 0x72, 0x59, 0x5f, 0x53, 0xbb, 0x00, 
	0x02, 0x59, 0x51, 0x81, 0xc3, 0x00, 0x04, 0x39, 0xcb, 0x73, 0xe8, 0x66, 0xff, 0x47, 0x10, 0x75, 
	0xf0, 0x66, 0xff, 0x47, 0x14, 0x75, 0xea, 0xb0, 0x2f, 0x89, 0xd9, 0x57, 0xf2, 0xae, 0x75, 0x35, 
	0x29, 0xd9, 0xf7, 0xd1, 0x5f, 0x60, 0xe8, 0x2b, 0x02, 0x61, 0x72, 0xd5, 0x8c, 0xd5, 0x01, 0xcf, 
	0x47, 0x38, 0x05, 0x75, 0xbe, 0xb8, 0x00, 0x10, 0x8e, 0xc0, 0x31, 0xdb, 0xc1, 0xeb, 0x04, 0x8c, 
	0xc0, 0x01, 0xd8, 0x8e, 0xc0, 0x31, 0xdb, 0xe8, 0xa5, 0x00, 0x73, 0xf0, 0x66, 0xa1, 0xab, 0x00, 
	0xea, 0x00, 0x02, 0x00, 0x10, 0xeb, 0x7f, 0x66, 0x60, 0x66, 0x05, 0x5b, 0x63, 0x40, 0x01, 0x06, 
	0x53, 0x52, 0x66, 0x50, 0x66, 0x31, 0xf6, 0x66, 0xc7, 0x04, 0x10, 0x00, 0x01, 0x00, 0x89, 0x5c, 
	0x04, 0x8c, 0x44, 0x06, 0x66, 0x89, 0x44, 0x08, 0x66, 0x89, 0x74, 0x0c, 0xb4, 0x08, 0xcd, 0x13, 
	0x88, 0xc8, 0x86, 0xe9, 0xc0, 0xc5, 0x02, 0x80, 0xe5, 0x03, 0x89, 0xcd, 0x25, 0x3f, 0x00, 0x89, 
	0xc3, 0xb2, 0x00, 0x86, 0xd6, 0x42, 0xf7, 0xe2, 0x91, 0x58, 0x5a, 0xe3, 0x39, 0x39, 0xca, 0x73, 
	0x2a, 0xf7, 0xf1, 0x39, 0xc5, 0x76, 0x24, 0x91, 0x92, 0xf6, 0xf3, 0x86, 0xcd, 0xc0, 0xc9, 0x02, 
	0x08, 0xe1, 0x41, 0x5a, 0x88, 0xc6, 0x5b, 0x07, 0xbf, 0x05, 0x00, 0xb8, 0x01, 0x02, 0xcd, 0x13, 
	0x73, 0x27, 0x31, 0xc0, 0xcd, 0x13, 0x4f, 0x75, 0xf2, 0xeb, 0x03, 0x5a, 0x5b, 0x07, 0x31, 0xf6, 
	0xb4, 0x42, 0xcd, 0x13, 0x73, 0x13, 0xbe, 0xd4, 0x01, 0x31, 0xdb, 0xb4, 0x0e, 0xac, 0xcd, 0x10, 
	0x3c, 0x2e, 0x75, 0xf9, 0x93, 0xcd, 0x16, 0xcd, 0x19, 0x66, 0x61, 0xc3, 0x01, 0x46, 0x00, 0x8b, 
	0x76, 0x00, 0xe8, 0x7a, 0x00, 0x83, 0x3c, 0x00, 0x75, 0x27, 0xb8, 0x08, 0x00, 0x01, 0x46, 0x00, 
	0xff, 0x4e, 0x02, 0x74, 0x08, 0x83, 0x4c, 0x08, 0x00, 0x75, 0xe4, 0xf9, 0xc3, 0xff, 0x46, 0x02, 
	0xfe, 0x0e, 0x10, 0x00, 0x7c, 0xf5, 0x81, 0xfd, 0x00, 0x90, 0x74, 0xd0, 0x83, 0xed, 0x04, 0xeb, 
	0xce, 0xff, 0x44, 0xfe, 0xff, 0x0c, 0x80, 0x3e, 0x10, 0x00, 0x02, 0x74, 0x24, 0x06, 0x53, 0x1e, 
	0x07, 0x8d, 0x5e, 0x08, 0xc1, 0xe3, 0x0b, 0xe8, 0x17, 0x00, 0x93, 0x5b, 0x07, 0x83, 0xc5, 0x04, 
	0x89, 0x7e, 0x00, 0x29, 0xf8, 0xc1, 0xe8, 0x03, 0x89, 0x46, 0x02, 0xfe, 0x06, 0x10, 0x00, 0xeb, 
	0x9e, 0xbe, 0x00, 0x02, 0x89, 0xdf, 0x8a, 0x4c, 0x2c, 0x80, 0xe9, 0x09, 0x66, 0xd3, 0xe0, 0x8b, 
	0x4c, 0x28, 0xc1, 0xe9, 0x09, 0xe8, 0xef, 0xfe, 0x01, 0xf3, 0x66, 0x40, 0xe2, 0xf7, 0xc3, 0x51, 
	0x66, 0xad, 0x8a, 0x0e, 0x4c, 0x02, 0x66, 0xd3, 0xe0, 0x66, 0x91, 0x66, 0x31, 0xc0, 0xad, 0x66, 
	0x01, 0xc8, 0x59, 0xc3, 0x45, 0x72, 0x72, 0x6f, 0x72, 0x20, 0x6c, 0x6f, 0x61, 0x64, 0x69, 0x6e, 
	0x67, 0x20, 0x4f, 0x53, 0x3b, 0x20, 0x70, 0x72, 0x65, 0x73, 0x73, 0x20, 0x61, 0x6e, 0x79, 0x20, 
	0x6b, 0x65, 0x79, 0x20, 0x74, 0x6f, 0x20, 0x72, 0x65, 0x62, 0x6f, 0x6f, 0x74, 0x2e, 0x55, 0xaa,
};

static const size_t kBootBlockData2Offset = 676;
static uint8 sBootBlockData2[348] = {
	0x52, 0x8d, 0x77, 0x18, 0xad, 0x92, 0x52, 0xad, 0x89, 0xf3, 0x89, 0xf5, 0x01, 0xc6, 0x83, 0xc6,
	0x07, 0x81, 0xe6, 0xf8, 0xff, 0xad, 0x01, 0xe8, 0x29, 0xd8, 0x39, 0xc8, 0x75, 0x08, 0x60, 0x89,
	0xde, 0xf3, 0xa6, 0x61, 0x74, 0x09, 0x01, 0xc3, 0x4a, 0x75, 0xea, 0x58, 0x5a, 0xf9, 0xc3, 0x58,
	0x29, 0xd0, 0xc1, 0xe0, 0x03, 0x01, 0xc6, 0x4a, 0x01, 0xd6, 0x01, 0xd6, 0x5a, 0x66, 0xad, 0x8c,
	0xd5, 0xbb, 0x00, 0x04, 0xe8, 0xb6, 0xfe, 0x66, 0x81, 0x3d, 0xd9, 0x0a, 0xbe, 0x3b, 0x75, 0x10,
	0xc6, 0x06, 0x10, 0x00, 0x02, 0xc7, 0x46, 0x00, 0x48, 0x04, 0xc7, 0x46, 0x02, 0x0c, 0x00, 0xc3,
	0xe9, 0x1f, 0xfe, 0x62, 0x65, 0x6f, 0x73, 0x2f, 0x73, 0x79, 0x73, 0x74, 0x65, 0x6d, 0x2f, 0x7a,
	0x62, 0x65, 0x6f, 0x73, 0x2f, 0x2f, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 
};

static const size_t kBootBlockData1Size = sizeof(sBootBlockData1);
static const size_t kBootBlockData2Size = sizeof(sBootBlockData2);

static const size_t kBIOSDriveOffset = 0x1e;
static const size_t kPartitionDataOffset = 0xab;

#endif	/* BOOT_BLOCK_DATA_H */
