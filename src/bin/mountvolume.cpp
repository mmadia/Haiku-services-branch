/*
 * Copyright 2005-2007, Ingo Weinhold, bonefish@users.sf.net. All rights reserved.
 * Distributed under the terms of the MIT License.
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <set>
#include <string>

#include <DiskDevice.h>
#include <DiskDevicePrivate.h>
#include <DiskDeviceRoster.h>
#include <DiskDeviceTypes.h>
#include <DiskDeviceList.h>
#include <Partition.h>

#include <Path.h>
#include <fs_volume.h>

using std::set;
using std::string;

extern const char *__progname;


typedef set<string> StringSet;

// usage
static const char *kUsage =
	"%s <options> [ <volume name> ... ]\n"
	"Mounts the volume with name <volume name>, if given. Lists info about\n"
	"mounted and mountable volumes and mounts/unmounts volumes.\n"
	"\n"
	"The terminology is actually not quite correct: By volumes only partitions\n"
	"living on disk devices are meant.\n"
	"\n"
	"Options:\n"
	"[general]\n"
	"  -s                 - silent; don't print info about (un)mounting\n"
	"  -h, --help         - print this info text\n"
	"\n"
	"[mounting]\n"
	"  -all               - mount all mountable volumes\n"
	"  -allbfs            - mount all mountable BFS volumes\n"
	"  -allhfs            - mount all mountable HFS volumes\n"
	"  -alldos            - mount all mountable DOS volumes\n"
	"  -ro                - mount volumes read-only\n"
	"  -unmount <volume>  - unmount the volume with the name <volume>\n"
	"\n"
	"[info]\n"
	"  -p, -l             - list all mounted and mountable volumes\n"
	"  -lh                - list all existing volumes (incl. not-mountable ones)\n"
	"  -dd                - list all disk existing devices\n"
	"\n"
	"[obsolete]\n"
	"  -r                 - ignored\n"
	"  -publishall        - ignored\n"
	"  -publishbfs        - ignored\n"
	"  -publishhfs        - ignored\n"
	"  -publishdos        - ignored\n";

// application name
const char *kAppName = __progname;


// print_usage
static
void
print_usage(bool error)
{
	fprintf(error ? stderr : stdout, kUsage, kAppName);
}

// print_usage_and_exit
static
void
print_usage_and_exit(bool error)
{
	print_usage(error);
	exit(error ? 0 : 1);
}

static const char *
size_string(int64 size)
{
	double blocks = size;
	static char string[64];

	if (size < 1024)
		sprintf(string, "%Ld", size);
	else {
		char *units[] = {"K", "M", "G", NULL};
		int32 i = -1;

		do {
			blocks /= 1024.0;
			i++;
		} while (blocks >= 1024 && units[i + 1]);

		snprintf(string, sizeof(string), "%.1f%s", blocks, units[i]);
	}

	return string;
}


//	#pragma mark -


struct MountVisitor : public BDiskDeviceVisitor {
	MountVisitor()
		: silent(false),
		  mountAll(false),
		  mountBFS(false),
		  mountHFS(false),
		  mountDOS(false),
		  readOnly(false)
	{
	}

	virtual bool Visit(BDiskDevice *device)
	{
		return Visit(device, 0);
	}

	virtual bool Visit(BPartition *partition, int32 level)
	{
		// get name and type
		const char *name = partition->ContentName();
		if (!name)
			name = partition->Name();
		const char *type = partition->ContentType();

		// check whether to mount
		bool mount = false;
		if (name && toMount.find(name) != toMount.end()) {
			toMount.erase(name);
			if (!partition->IsMounted())
				mount = true;
			else if (!silent)
				fprintf(stderr, "Volume `%s' already mounted.\n", name);
		} else if (mountAll) {
			mount = true;
		} else if (mountBFS && type != NULL
			&& strcmp(type, kPartitionTypeBFS) == 0) {
			mount = true;
		} else if (mountHFS && type != NULL
			&& strcmp(type, kPartitionTypeHFS) == 0) {
			mount = true;
		} else if (mountDOS && type != NULL
			&& (strcmp(type, kPartitionTypeFAT12) == 0
				|| strcmp(type, kPartitionTypeFAT32) == 0)) {
			mount = true;
		}

		// don't try to mount a partition twice
		if (partition->IsMounted())
			mount = false;

		// check whether to unmount
		bool unmount = false;
		if (name && toUnmount.find(name) != toUnmount.end()) {
			toUnmount.erase(name);
			if (!partition->IsMounted()) {
				unmount = true;
				mount = false;
			} else if (!silent)
				fprintf(stderr, "Volume `%s' not mounted.\n", name);
		}

		// mount/unmount
		if (mount) {
			status_t error = partition->Mount(NULL,
				(readOnly ? B_MOUNT_READ_ONLY : 0));
			if (!silent) {
				if (error >= B_OK) {
					BPath mountPoint;
					partition->GetMountPoint(&mountPoint);
					printf("Volume `%s' mounted successfully at '%s'.\n", name, mountPoint.Path());
				} else {
					fprintf(stderr, "Failed to mount volume `%s': %s\n",
						name, strerror(error));
				}
			}
		} else if (unmount) {
			status_t error = partition->Unmount();
			if (!silent) {
				if (error == B_OK) {
					printf("Volume `%s' unmounted successfully.\n", name);
				} else {
					fprintf(stderr, "Failed to unmount volume `%s': %s\n",
						name, strerror(error));
				}
			}
		}

		return false;
	}

	bool		silent;
	StringSet	toMount;
	StringSet	toUnmount;
	bool		mountAll;
	bool		mountBFS;
	bool		mountHFS;
	bool		mountDOS;
	bool		readOnly;
};

// PrintPartitionsVisitor
struct PrintPartitionsVisitor : public BDiskDeviceVisitor {
	PrintPartitionsVisitor()
		: listMountablePartitions(false),
		  listAllPartitions(false)
	{
	}

	bool IsUsed()
	{
		return listMountablePartitions || listAllPartitions;
	}

	virtual bool Visit(BDiskDevice *device)
	{
		return Visit(device, 0);
	}

	virtual bool Visit(BPartition *partition, int32 level)
	{
		// get name and type
		const char *name = partition->ContentName();
		if (name == NULL || name[0] == '\0') {
			name = partition->Name();
			if (name == NULL || name[0] == '\0') {
				if (partition->ContainsFileSystem())
					name = "<unnamed>";
				else
					name = "";
			}
		}
		const char *type = partition->ContentType();
		if (type == NULL)
			type = "<unknown>";

		// shorten known types for display
		if (!strcmp(type, kPartitionTypeMultisession))
			type = "Multisession";
		else if (!strcmp(type, kPartitionTypeIntelExtended))
			type = "Intel Extended";

		BPath path;
		partition->GetPath(&path);

		// cut off beginning of the device path (if /dev/disk/)
		int32 skip = strlen("/dev/disk/");
		if (strncmp(path.Path(), "/dev/disk/", skip))
			skip = 0;

		BPath mountPoint;
		if (partition->IsMounted())
			partition->GetMountPoint(&mountPoint);

		printf("%-14s %-20s %8s %s  (%s)\n",
			name, type, size_string(partition->Size()),
			partition->IsMounted() ? mountPoint.Path() : "",
			path.Path() + skip);
		return false;
	}

	bool listMountablePartitions;
	bool listAllPartitions;
};


//	#pragma mark -


int
main(int argc, char **argv)
{
	if (argc < 2)
		print_usage_and_exit(true);

	MountVisitor mountVisitor;
	PrintPartitionsVisitor printPartitionsVisitor;
	bool listAllDevices = false;

	// parse arguments

	for (int argi = 1; argi < argc; argi++) {
		const char *arg = argv[argi];

		if (arg[0] != '\0' && arg[0] != '-') {
			mountVisitor.toMount.insert(arg);
		} else if (strcmp(arg, "-s") == 0) {
			mountVisitor.silent = true;
		} else if (strcmp(arg, "-h") == 0 || strcmp(arg, "--help") == 0) {
			print_usage_and_exit(false);
		} else if (strcmp(arg, "-all") == 0) {
			mountVisitor.mountAll = true;
		} else if (strcmp(arg, "-allbfs") == 0) {
			mountVisitor.mountBFS = true;
		} else if (strcmp(arg, "-allhfs") == 0) {
			mountVisitor.mountHFS = true;
		} else if (strcmp(arg, "-alldos") == 0) {
			mountVisitor.mountDOS = true;
		} else if (strcmp(arg, "-ro") == 0) {
			mountVisitor.readOnly = true;
		} else if (strcmp(arg, "-unmount") == 0) {
			argi++;
			if (argi >= argc)
				print_usage_and_exit(true);
			mountVisitor.toUnmount.insert(argv[argi]);
		} else if (strcmp(arg, "-p") == 0 || strcmp(arg, "-l") == 0) {
			printPartitionsVisitor.listMountablePartitions = true;
		} else if (strcmp(arg, "-lh") == 0) {
			printPartitionsVisitor.listAllPartitions = true;
		} else if (strcmp(arg, "-dd") == 0) {
			listAllDevices = true;
		} else if (strcmp(arg, "-r") == 0 || strcmp(arg, "-publishall") == 0
			|| strcmp(arg, "-publishbfs") == 0
			|| strcmp(arg, "-publishhfs") == 0
			|| strcmp(arg, "-publishdos") == 0) {
			// obsolete: ignore
		} else
			print_usage_and_exit(true);
	}

	// get a disk device list
	BDiskDeviceList deviceList;
	status_t error = deviceList.Fetch();
	if (error != B_OK) {
		fprintf(stderr, "Failed to get the list of disk devices: %s",
			strerror(error));
		exit(1);
	}

	// mount/unmount volumes
	deviceList.VisitEachMountablePartition(&mountVisitor);

	BDiskDeviceRoster roster;

	// try mount file images
	for (StringSet::iterator iterator = mountVisitor.toMount.begin();
			iterator != mountVisitor.toMount.end();) {
		const char* name = (*iterator).c_str();
		iterator++;

		BEntry entry(name, true);
		if (!entry.Exists())
			continue;

		// TODO: improve error messages
		BPath path;
		if (entry.GetPath(&path) != B_OK)
			continue;

		// a file with this name exists, so try to mount it
		partition_id id = roster.RegisterFileDevice(path.Path());
		if (id < B_OK)
			continue;

		BDiskDevice device;
		BPartition* partition;
		if (roster.GetPartitionWithID(id, &device, &partition) != B_OK) {
			roster.UnregisterFileDevice(id);
			continue;
		}

		status_t status = partition->Mount(NULL,
			mountVisitor.readOnly ? B_MOUNT_READ_ONLY : 0);
		if (!mountVisitor.silent) {
			if (status >= B_OK) {
				BPath mountPoint;
				partition->GetMountPoint(&mountPoint);
				printf("Image \"%s\" mounted successfully at \"%s\".\n", name,
					mountPoint.Path());
			}
		}
		if (status >= B_OK) {
			// remove from list
			mountVisitor.toMount.erase(name);
		} else
			roster.UnregisterFileDevice(id);
	}

	// TODO: support unmounting images by path!

	// print errors for the volumes to mount/unmount, that weren't found
	if (!mountVisitor.silent) {
		for (StringSet::iterator it = mountVisitor.toMount.begin();
				it != mountVisitor.toMount.end(); it++) {
			fprintf(stderr, "Failed to mount volume `%s': Volume not found.\n",
				(*it).c_str());
		}
		for (StringSet::iterator it = mountVisitor.toUnmount.begin();
				it != mountVisitor.toUnmount.end(); it++) {
			fprintf(stderr, "Failed to unmount volume `%s': Volume not found.\n",
				(*it).c_str());
		}
	}

	// update the disk device list
	error = deviceList.Fetch();
	if (error != B_OK) {
		fprintf(stderr, "Failed to update the list of disk devices: %s",
			strerror(error));
		exit(1);
	}

	// print information

	if (listAllDevices) {
		// TODO
	}

	if (printPartitionsVisitor.IsUsed()) {
		puts("Volume         File System              Size Mounted At (Device)");
		puts("---------------------------------------------------------------------");

		if (printPartitionsVisitor.listAllPartitions)
			deviceList.VisitEachPartition(&printPartitionsVisitor);
		else
			deviceList.VisitEachMountablePartition(&printPartitionsVisitor);
	}

	return 0;
}
