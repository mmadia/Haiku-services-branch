//----------------------------------------------------------------------
//  This software is part of the OpenBeOS distribution and is covered 
//  by the OpenBeOS license.
//---------------------------------------------------------------------

#ifndef _DISK_DEVICE_DEFS_H
#define _DISK_DEVICE_DEFS_H

#include <SupportDefs.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef int32 partition_id;
typedef int32 disk_system_id;
typedef int32 disk_job_id;

// partition flags
enum {
	B_PARTITION_IS_DEVICE			= 0x01,
	B_PARTITION_FILE_SYSTEM			= 0x02,
	B_PARTITION_PARTITIONING_SYSTEM	= 0x04,
	B_PARTITION_READ_ONLY			= 0x08,
	B_PARTITION_MOUNTED				= 0x10,	// needed?
	B_PARTITION_BUSY				= 0x20,
	B_PARTITION_DESCENDANT_BUSY		= 0x40,
};

// partition statuses
enum {
	B_PARTITION_VALID,
	B_PARTITION_CORRUPT,
	B_PARTITION_UNRECOGNIZED,
};

// disk device flags
enum {
	B_DISK_DEVICE_REMOVABLE		= 0x01,
	B_DISK_DEVICE_HAS_MEDIA		= 0x02,
	B_DISK_DEVICE_READ_ONLY		= 0x04,
	B_DISK_DEVICE_WRITE_ONCE	= 0x08,
};

// disk system flags
enum {
	B_DISK_SYSTEM_IS_FILE_SYSTEM								= 0x0001,

	// flags common for both file and partitioning systems
	B_DISK_SYSTEM_SUPPORTS_CHECKING								= 0x0002,
	B_DISK_SYSTEM_SUPPORTS_REPAIRING							= 0x0004,
	B_DISK_SYSTEM_SUPPORTS_RESIZING								= 0x0008,
	B_DISK_SYSTEM_SUPPORTS_MOVING								= 0x0010,
	B_DISK_SYSTEM_SUPPORTS_SETTING_CONTENT_NAME					= 0x0020,
	B_DISK_SYSTEM_SUPPORTS_SETTING_CONTENT_PARAMETERS			= 0x0040,

	// file system specific flags
	B_DISK_SYSTEM_SUPPORTS_DEFRAGMENTING						= 0x0100,
	B_DISK_SYSTEM_SUPPORTS_DEFRAGMENTING_WHILE_MOUNTED			= 0x0200,
	B_DISK_SYSTEM_SUPPORTS_CHECKING_WHILE_MOUNTED				= 0x0400,
	B_DISK_SYSTEM_SUPPORTS_REPAIRING_WHILE_MOUNTED				= 0x0800,
	B_DISK_SYSTEM_SUPPORTS_RESIZING_WHILE_MOUNTED				= 0x1000,
	B_DISK_SYSTEM_SUPPORTS_MOVING_WHILE_MOUNTED					= 0x2000,
	B_DISK_SYSTEM_SUPPORTS_SETTING_CONTENT_NAME_WHILE_MOUNTED	= 0x4000,
	B_DISK_SYSTEM_SUPPORTS_SETTING_CONTENT_PARAMETERS_WHILE_MOUNTED	= 0x8000,

	// partitioning system specific flags
	B_DISK_SYSTEM_SUPPORTS_RESIZING_CHILD						= 0x0100,
	B_DISK_SYSTEM_SUPPORTS_MOVING_CHILD							= 0x0200,
	B_DISK_SYSTEM_SUPPORTS_SETTING_NAME							= 0x0400,
	B_DISK_SYSTEM_SUPPORTS_SETTING_TYPE							= 0x0800,
	B_DISK_SYSTEM_SUPPORTS_SETTING_PARAMETERS					= 0x1000,
	B_DISK_SYSTEM_SUPPORTS_CREATING_CHILD						= 0x2000,
	B_DISK_SYSTEM_SUPPORTS_DELETING_CHILD						= 0x4000,
	B_DISK_SYSTEM_SUPPORTS_INITIALIZING							= 0x8000,
};

#ifdef __cplusplus
}
#endif

#endif	// _DISK_DEVICE_DEFS_H
