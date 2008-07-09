/*
 * Copyright 2004-2008, Axel Dörfler, axeld@pinc-software.de.
 * Distributed under the terms of the MIT License.
 */


#include <fs_query.h>

#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>

#include <dirent_private.h>
#include <syscalls.h>


static DIR *
open_query_etc(dev_t device, const char *query,
	uint32 flags, port_id port, int32 token)
{
	if (device < 0 || query == NULL || query[0] == '\0') {
		errno = B_BAD_VALUE;
		return NULL;
	}

	// open
	int fd = _kern_open_query(device, query, strlen(query), flags, port, token);
	if (fd < 0) {
		errno = fd;
		return NULL;
	}

	// allocate a DIR
	DIR *dir = (DIR *)malloc(DIR_BUFFER_SIZE);
	if (!dir) {
		_kern_close(fd);
		errno = B_NO_MEMORY;
		return NULL;
	}

	dir->fd = fd;
	dir->entries_left = 0;

	return dir;
}


DIR *
fs_open_query(dev_t device, const char *query, uint32 flags)
{
	return open_query_etc(device, query, flags, -1, -1);
}


DIR *
fs_open_live_query(dev_t device, const char *query,
	uint32 flags, port_id port, int32 token)
{
	// check parameters
	if (port < 0) {
		errno = B_BAD_VALUE;
		return NULL;
	}

	return open_query_etc(device, query, flags | B_LIVE_QUERY, port, token);
}


int
fs_close_query(DIR *dir)
{
	if (dir == NULL) {
		errno = B_BAD_VALUE;
		return -1;
	}

	int fd = dir->fd;
	free(dir);
	return _kern_close(fd);
}


struct dirent *
fs_read_query(DIR *dir)
{
	return readdir(dir);
}


status_t
get_path_for_dirent(struct dirent *dent, char *buffer, size_t length)
{
	if (dent == NULL || buffer == NULL)
		return B_BAD_VALUE;

	return _kern_entry_ref_to_path(dent->d_pdev, dent->d_pino, dent->d_name,
		buffer, length);
}

