
#ifdef BUILDING_FS_SHELL
#	include "compat.h"
#	define B_OK			0
#	define B_BAD_VALUE	EINVAL
#	define B_FILE_ERROR	EBADF
#else
#	include <HaikuBuildCompatibility.h>
#	include <syscalls.h>
#endif

#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

#include <string>

#include <fs_attr.h>

#include "fs_attr_impl.h"

using namespace std;
using namespace BPrivate;

static const char *sAttributeDirBasePath = HAIKU_BUILD_ATTRIBUTES_DIR;

// init_attribute_dir_base_dir
static status_t
init_attribute_dir_base_dir()
{
	static bool initialized = false;
	static status_t initError;

	if (initialized)
		return initError;
	
	// stat the dir
	struct stat st;
	initError = B_OK;
	if (lstat(sAttributeDirBasePath, &st) == 0) {
		if (!S_ISDIR(st.st_mode)) {
			// the attribute dir base dir is no directory
			fprintf(stderr, "init_attribute_dir_base_dir(): The Attribute "
				"directory base directory exists, but is no directory!\n");
			initError = B_FILE_ERROR;
		}
	
	} else {
		// doesn't exist yet: create it
		if (mkdir(sAttributeDirBasePath, S_IRWXU | S_IRWXG | S_IRWXO) < 0)
			initError = errno;
	}

	initialized = true;
	return initError;
}

// escape_attr_name
static string
escape_attr_name(const char *name)
{
	string escapedName("_");
	while (*name != '\0') {
		// we replace '/' with "_s" and '_' with "__"
		if (*name == '/')
			escapedName += "_s";
		else if (*name == '_')
			escapedName += "__";
		else
			escapedName += *name;
	
		name++;
	}

	return escapedName;
}

// deescape_attr_name
static string
deescape_attr_name(const char *name)
{
	if (name[0] != '_') {
		debugger("deescape_attr_name(): name doesn't start with '_'!\n");
		return "___";
	}
	name++;
	
	string deescapedName;
	while (*name != '\0') {
		if (*name == '_') {
			name++;
			if (*name == 's') {
				deescapedName += '/';
			} else if (*name == '_') {
				deescapedName += '_';
			} else {
				debugger("deescape_attr_name(): name contains invalid escaped "
					"sequence!\n");
				name--;
			}
		} else
			deescapedName += *name;
		
		name++;
	}

	return deescapedName;	
}

// get_attribute_dir_path
static string
get_attribute_dir_path(NodeRef ref)
{
	string attrDirPath(sAttributeDirBasePath);
	char buffer[32];
	sprintf(buffer, "/%lld", (int64)ref.node);
	attrDirPath += buffer;
	return attrDirPath;
}

// ensure_attribute_dir_exists
static status_t
ensure_attribute_dir_exists(NodeRef ref)
{
	// init the base directory here
	status_t error = init_attribute_dir_base_dir();
	if (error != B_OK)
		return error;

	// stat the dir
	string attrDirPath(get_attribute_dir_path(ref));
	struct stat st;
	if (lstat(attrDirPath.c_str(), &st) == 0) {
		if (!S_ISDIR(st.st_mode)) {
			// the attribute dir is no directory
			fprintf(stderr, "ensure_attribute_dir_exists(): Attribute "
				"directory for node %lld exists, but is no directory!\n");
			return B_FILE_ERROR;
		}
	
		return B_OK;
	}

	// doesn't exist yet: create it
	if (mkdir(attrDirPath.c_str(), S_IRWXU | S_IRWXG | S_IRWXO) < 0)
		return errno;
	return B_OK;
}

// open_attr_dir
DIR *
BPrivate::open_attr_dir(NodeRef ref)
{
	// make sure the directory exists
	status_t error = ensure_attribute_dir_exists(ref);
	if (error != B_OK) {
		errno = error;
		return NULL;
	}

	// open it
	string dirPath(get_attribute_dir_path(ref));
	return opendir(dirPath.c_str());
}

// get_attribute_path
status_t
BPrivate::get_attribute_path(NodeRef ref, const char *attribute,
	string &attrPath, string &typePath)
{
	if (!attribute || strlen(attribute) == 0)
		return B_BAD_VALUE;

	// make sure the attribute dir for the node exits
	status_t error = ensure_attribute_dir_exists(ref);
	if (error != B_OK) {
		errno = error;
		return -1;
	}
	
	// construct the attribute path
	attrPath = get_attribute_dir_path(ref) + '/';
	string attrName(escape_attr_name(attribute));
	typePath = attrPath + "t" + attrName;
	attrPath += attrName;

	return B_OK;
}

// get_attribute_path
static status_t
get_attribute_path(int fd, const char *attribute, string &attrPath,
	string &typePath)
{
	// stat the file to get a NodeRef
	struct stat st;
	if (fstat(fd, &st) < 0)
		return errno;
	NodeRef ref(st);

	return get_attribute_path(ref, attribute, attrPath, typePath);
}

// fs_open_attr_dir
DIR *
fs_open_attr_dir(const char *path)
{
	struct stat st;
	if (lstat(path, &st))
		return NULL;

	return open_attr_dir(NodeRef(st));
}

// fs_fopen_attr_dir
DIR *
fs_fopen_attr_dir(int fd)
{
	struct stat st;

#ifdef BUILDING_FS_SHELL

	if (fstat(fd, &st) < 0)
		return NULL;

#else

	status_t error = _kern_read_stat(fd, NULL, false, &st,
		sizeof(struct stat));
	if (error != B_OK) {
		errno = error;
		return NULL;
	}

#endif

	return open_attr_dir(NodeRef(st));
}

// fs_close_attr_dir
int
fs_close_attr_dir(DIR *dir)
{
	return closedir(dir);
}

// fs_read_attr_dir
struct dirent *
fs_read_attr_dir(DIR *dir)
{
	struct dirent *entry = NULL;
	while (true) {
		// read the next entry
		entry = readdir(dir);
		if (!entry)
			return NULL;
	
		// ignore administrative entries; the 
		if (entry->d_name[0] == '_') {
			string attrName = deescape_attr_name(entry->d_name);
			strcpy(entry->d_name, attrName.c_str());
			return entry;
		}
	}
}

// fs_rewind_attr_dir
void
fs_rewind_attr_dir(DIR *dir)
{
	rewinddir(dir);
}

// fs_open_attr
int
fs_open_attr(int fd, const char *attribute, uint32 type, int openMode)
{
	if (!attribute) {
		errno = B_BAD_VALUE;
		return -1;
	}
	
	// get the attribute path
	string attrPath;
	string typePath;
	status_t error = get_attribute_path(fd, attribute, attrPath, typePath);
	if (error != B_OK) {
		errno = error;
		return -1;
	}

	// check, if the attribute already exists
	struct stat st;
	bool exists = (lstat(attrPath.c_str(), &st) == 0);

	// open the attribute
	int attrFD = open(attrPath.c_str(), openMode, S_IRWXU | S_IRWXG | S_IRWXO);
	if (attrFD < 0)
		return -1;

	// set the type, if the attribute didn't exist yet
	if (!exists) {
		// create a file prefixed "t"
		int typeFD = creat(typePath.c_str(), S_IRWXU | S_IRWXG | S_IRWXO);
		if (typeFD >= 0) {
			// write the type into the file
			if (write(typeFD, &type, sizeof(type)) < 0)
				error = errno;
			
			close(typeFD);

		} else
			error = errno;

		// remove type and attribute file, if something went wrong
		if (error != B_OK) {
			if (typeFD > 0) {
				unlink(typePath.c_str());
			}
		
			close(attrFD);
			unlink(attrPath.c_str());
		
			errno = error;
			return -1;
		}
	}

	return attrFD;
}

// fs_close_attr
int
fs_close_attr(int fd)
{
	return close(fd);
}

// fs_read_attr
ssize_t
fs_read_attr(int fd, const char *attribute, uint32 type, off_t pos,
	void *buffer, size_t readBytes)
{
	// open the attribute
	int attrFD = fs_open_attr(fd, attribute, type, O_RDONLY);
	if (attrFD < 0)
		return attrFD;

	// read
	ssize_t bytesRead = read_pos(attrFD, pos, buffer, readBytes);
	status_t error = errno;

	// close the attribute
	fs_close_attr(attrFD);

	if (bytesRead < 0) {
		errno = error;
		return -1;
	}
	
	return bytesRead;
}

// fs_write_attr
ssize_t
fs_write_attr(int fd, const char *attribute, uint32 type, off_t pos,
	const void *buffer, size_t readBytes)
{
	// open the attribute
	int attrFD = fs_open_attr(fd, attribute, type,
		O_WRONLY | O_CREAT | O_TRUNC);
	if (attrFD < 0)
		return attrFD;

	// read
	ssize_t bytesWritten = write_pos(attrFD, pos, buffer, readBytes);
	status_t error = errno;

	// close the attribute
	fs_close_attr(attrFD);

	if (bytesWritten < 0) {
		errno = error;
		return -1;
	}
	
	return bytesWritten;
}

// fs_remove_attr
int
fs_remove_attr(int fd, const char *attribute)
{
	if (!attribute) {
		errno = B_BAD_VALUE;
		return -1;
	}
	
	// get the attribute path
	string attrPath;
	string typePath;
	status_t error = get_attribute_path(fd, attribute, attrPath, typePath);
	if (error != B_OK) {
		errno = error;
		return -1;
	}

	// remove the attribute
	if (unlink(attrPath.c_str()) < 0)
		return -1;
	
	unlink(typePath.c_str());
	
	return B_OK;
}

// fs_stat_attr
int
fs_stat_attr(int fd, const char *attribute, struct attr_info *attrInfo)
{
	if (!attribute || !attrInfo) {
		errno = B_BAD_VALUE;
		return -1;
	}

	// get the attribute path
	string attrPath;
	string typePath;
	status_t error = get_attribute_path(fd, attribute, attrPath, typePath);
	if (error != B_OK) {
		errno = error;
		return -1;
	}

	// stat the attribute file to get the size of the attribute
	struct stat st;
	if (lstat(attrPath.c_str(), &st) < 0)
		return -1;
		
	attrInfo->size = st.st_size;

	// now open the attribute type file and read the attribute's type
	int typeFD = open(typePath.c_str(), O_RDONLY);
	if (typeFD < 0)
		return -1;

	ssize_t bytesRead = read(typeFD, &attrInfo->type, sizeof(attrInfo->type));
	if (bytesRead < 0)
		error = errno;
	else if (bytesRead < (ssize_t)sizeof(attrInfo->type))
		error = B_FILE_ERROR;

	close(typeFD);

	// fail on error
	if (error != B_OK) {
		errno = error;
		return -1;
	}

	return 0;					
}

