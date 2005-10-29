/******************************************************************************
/
/	File:			Errors.h
/
/	Description:	Error code constants.
/
/	Copyright 1993-98, Be Incorporated
/
******************************************************************************/


#ifndef _ERRORS_H
#define _ERRORS_H

#include <errno.h>
#include <limits.h>

/*-------------------------------------------------------------*/
/*----- Error baselines ---------------------------------------*/

#define B_GENERAL_ERROR_BASE		LONG_MIN
#define B_OS_ERROR_BASE				B_GENERAL_ERROR_BASE + 0x1000
#define B_APP_ERROR_BASE			B_GENERAL_ERROR_BASE + 0x2000
#define B_INTERFACE_ERROR_BASE		B_GENERAL_ERROR_BASE + 0x3000
#define B_MEDIA_ERROR_BASE			B_GENERAL_ERROR_BASE + 0x4000 /* - 0x41ff */
#define B_TRANSLATION_ERROR_BASE	B_GENERAL_ERROR_BASE + 0x4800 /* - 0x48ff */
#define B_MIDI_ERROR_BASE			B_GENERAL_ERROR_BASE + 0x5000
#define B_STORAGE_ERROR_BASE		B_GENERAL_ERROR_BASE + 0x6000
#define B_POSIX_ERROR_BASE			B_GENERAL_ERROR_BASE + 0x7000
#define B_MAIL_ERROR_BASE			B_GENERAL_ERROR_BASE + 0x8000
#define B_PRINT_ERROR_BASE			B_GENERAL_ERROR_BASE + 0x9000
#define B_DEVICE_ERROR_BASE			B_GENERAL_ERROR_BASE + 0xa000

/*--- Developer-defined errors start at (B_ERRORS_END+1)----*/

#define B_ERRORS_END		(B_GENERAL_ERROR_BASE + 0xffff)


/*-------------------------------------------------------------*/
/*----- General Errors ----------------------------------------*/
enum {
	B_NO_MEMORY = B_GENERAL_ERROR_BASE,
	B_IO_ERROR,
	B_PERMISSION_DENIED,
	B_BAD_INDEX,
	B_BAD_TYPE,
	B_BAD_VALUE,
	B_MISMATCHED_VALUES,
	B_NAME_NOT_FOUND,
	B_NAME_IN_USE,
	B_TIMED_OUT,
    B_INTERRUPTED,
	B_WOULD_BLOCK,
    B_CANCELED,
	B_NO_INIT,
	B_BUSY,
	B_NOT_ALLOWED,
	B_BAD_DATA,

	B_ERROR = -1,
	B_OK = 0,
	B_NO_ERROR = 0
};

/*-------------------------------------------------------------*/
/*----- Kernel Kit Errors -------------------------------------*/
enum {
	B_BAD_SEM_ID = B_OS_ERROR_BASE,
	B_NO_MORE_SEMS,

	B_BAD_THREAD_ID = B_OS_ERROR_BASE + 0x100,
	B_NO_MORE_THREADS,
	B_BAD_THREAD_STATE,
	B_BAD_TEAM_ID,
	B_NO_MORE_TEAMS,

	B_BAD_PORT_ID = B_OS_ERROR_BASE + 0x200,
	B_NO_MORE_PORTS,

	B_BAD_IMAGE_ID = B_OS_ERROR_BASE + 0x300,
	B_BAD_ADDRESS,
	B_NOT_AN_EXECUTABLE,
	B_MISSING_LIBRARY,
	B_MISSING_SYMBOL,

	B_DEBUGGER_ALREADY_INSTALLED = B_OS_ERROR_BASE + 0x400
};


/*-------------------------------------------------------------*/
/*----- Application Kit Errors --------------------------------*/
enum
{
	B_BAD_REPLY = B_APP_ERROR_BASE,
	B_DUPLICATE_REPLY,
	B_MESSAGE_TO_SELF,
	B_BAD_HANDLER,
	B_ALREADY_RUNNING,
	B_LAUNCH_FAILED,
	B_AMBIGUOUS_APP_LAUNCH,
	B_UNKNOWN_MIME_TYPE,
	B_BAD_SCRIPT_SYNTAX,
	B_LAUNCH_FAILED_NO_RESOLVE_LINK,
	B_LAUNCH_FAILED_EXECUTABLE,
	B_LAUNCH_FAILED_APP_NOT_FOUND,
	B_LAUNCH_FAILED_APP_IN_TRASH,
	B_LAUNCH_FAILED_NO_PREFERRED_APP,
	B_LAUNCH_FAILED_FILES_APP_NOT_FOUND,
	B_BAD_MIME_SNIFFER_RULE,
	B_NOT_A_MESSAGE,
	B_SHUTDOWN_CANCELLED,
	B_SHUTTING_DOWN
};


/*-------------------------------------------------------------*/
/*----- Storage Kit/File System Errors ------------------------*/
enum {
	B_FILE_ERROR = B_STORAGE_ERROR_BASE,
	B_FILE_NOT_FOUND,	/* discouraged; use B_ENTRY_NOT_FOUND in new code*/
	B_FILE_EXISTS,
	B_ENTRY_NOT_FOUND,
	B_NAME_TOO_LONG,
	B_NOT_A_DIRECTORY,
	B_DIRECTORY_NOT_EMPTY,
	B_DEVICE_FULL,
	B_READ_ONLY_DEVICE,
	B_IS_A_DIRECTORY,
	B_NO_MORE_FDS,
	B_CROSS_DEVICE_LINK,
	B_LINK_LIMIT,
	B_BUSTED_PIPE,
	B_UNSUPPORTED,
	B_PARTITION_TOO_SMALL
};


/*-------------------------------------------------------------*/
/*----- POSIX Errors ------------------------------------------*/
#define HAIKU_E2BIG			(B_POSIX_ERROR_BASE + 1)
#define HAIKU_ECHILD			(B_POSIX_ERROR_BASE + 2)
#define HAIKU_EDEADLK			(B_POSIX_ERROR_BASE + 3)
#define HAIKU_EFBIG			(B_POSIX_ERROR_BASE + 4)
#define HAIKU_EMLINK			(B_POSIX_ERROR_BASE + 5)
#define HAIKU_ENFILE			(B_POSIX_ERROR_BASE + 6)
#define HAIKU_ENODEV			(B_POSIX_ERROR_BASE + 7)
#define HAIKU_ENOLCK			(B_POSIX_ERROR_BASE + 8)
#define HAIKU_ENOSYS			(B_POSIX_ERROR_BASE + 9)
#define HAIKU_ENOTTY			(B_POSIX_ERROR_BASE + 10)
#define HAIKU_ENXIO			(B_POSIX_ERROR_BASE + 11)
#define HAIKU_ESPIPE			(B_POSIX_ERROR_BASE + 12)
#define HAIKU_ESRCH			(B_POSIX_ERROR_BASE + 13)
#define HAIKU_EFPOS			(B_POSIX_ERROR_BASE + 14)
#define HAIKU_ESIGPARM		(B_POSIX_ERROR_BASE + 15)
#define HAIKU_EDOM			(B_POSIX_ERROR_BASE + 16)
#define HAIKU_ERANGE			(B_POSIX_ERROR_BASE + 17)
#define HAIKU_EPROTOTYPE		(B_POSIX_ERROR_BASE + 18)
#define HAIKU_EPROTONOSUPPORT	(B_POSIX_ERROR_BASE + 19)
#define HAIKU_EPFNOSUPPORT	(B_POSIX_ERROR_BASE + 20)
#define HAIKU_EAFNOSUPPORT	(B_POSIX_ERROR_BASE + 21)
#define HAIKU_EADDRINUSE		(B_POSIX_ERROR_BASE + 22)
#define HAIKU_EADDRNOTAVAIL	(B_POSIX_ERROR_BASE + 23)
#define HAIKU_ENETDOWN		(B_POSIX_ERROR_BASE + 24)
#define HAIKU_ENETUNREACH		(B_POSIX_ERROR_BASE + 25)
#define HAIKU_ENETRESET		(B_POSIX_ERROR_BASE + 26)
#define HAIKU_ECONNABORTED	(B_POSIX_ERROR_BASE + 27)
#define HAIKU_ECONNRESET		(B_POSIX_ERROR_BASE + 28)
#define HAIKU_EISCONN			(B_POSIX_ERROR_BASE + 29)
#define HAIKU_ENOTCONN		(B_POSIX_ERROR_BASE + 30)
#define HAIKU_ESHUTDOWN		(B_POSIX_ERROR_BASE + 31)
#define HAIKU_ECONNREFUSED	(B_POSIX_ERROR_BASE + 32)
#define HAIKU_EHOSTUNREACH	(B_POSIX_ERROR_BASE + 33)
#define HAIKU_ENOPROTOOPT		(B_POSIX_ERROR_BASE + 34)
#define HAIKU_ENOBUFS			(B_POSIX_ERROR_BASE + 35)
#define HAIKU_EINPROGRESS		(B_POSIX_ERROR_BASE + 36)
#define HAIKU_EALREADY		(B_POSIX_ERROR_BASE + 37)
#define HAIKU_EILSEQ          (B_POSIX_ERROR_BASE + 38)
#define HAIKU_ENOMSG          (B_POSIX_ERROR_BASE + 39)
#define HAIKU_ESTALE          (B_POSIX_ERROR_BASE + 40)
#define HAIKU_EOVERFLOW       (B_POSIX_ERROR_BASE + 41)
#define HAIKU_EMSGSIZE        (B_POSIX_ERROR_BASE + 42)
#define HAIKU_EOPNOTSUPP      (B_POSIX_ERROR_BASE + 43)                       
#define HAIKU_ENOTSOCK		(B_POSIX_ERROR_BASE + 44)
#define HAIKU_EHOSTDOWN		(B_POSIX_ERROR_BASE + 45)
#define HAIKU_EBADMSG			(B_POSIX_ERROR_BASE + 46)
#define HAIKU_ECANCELED		(B_POSIX_ERROR_BASE + 47)
#define HAIKU_EDESTADDRREQ	(B_POSIX_ERROR_BASE + 48)
#define HAIKU_EDQUOT			(B_POSIX_ERROR_BASE + 49)
#define HAIKU_EIDRM			(B_POSIX_ERROR_BASE + 50)
#define HAIKU_EMULTIHOP		(B_POSIX_ERROR_BASE + 51)
#define HAIKU_ENODATA			(B_POSIX_ERROR_BASE + 52)
#define HAIKU_ENOLINK			(B_POSIX_ERROR_BASE + 53)
#define HAIKU_ENOSR			(B_POSIX_ERROR_BASE + 54)
#define HAIKU_ENOSTR			(B_POSIX_ERROR_BASE + 55)
#define HAIKU_ENOTSUP			(B_POSIX_ERROR_BASE + 56)
#define HAIKU_EPROTO			(B_POSIX_ERROR_BASE + 57)
#define HAIKU_ETIME			(B_POSIX_ERROR_BASE + 58)
#define HAIKU_ETXTBSY			(B_POSIX_ERROR_BASE + 59)


/*---- POSIX errors that can be mapped to BeOS error codes ----*/
#define HAIKU_ENOMEM			B_NO_MEMORY
#define HAIKU_EACCES			B_PERMISSION_DENIED
#define HAIKU_EINTR			B_INTERRUPTED
#define HAIKU_EIO				B_IO_ERROR
#define HAIKU_EBUSY			B_BUSY
#define HAIKU_EFAULT			B_BAD_ADDRESS
#define HAIKU_ETIMEDOUT		B_TIMED_OUT
#define HAIKU_EAGAIN 			B_WOULD_BLOCK	/* SysV compatibility */
#define HAIKU_EWOULDBLOCK 	B_WOULD_BLOCK	/* BSD compatibility */
#define HAIKU_EBADF			B_FILE_ERROR
#define HAIKU_EEXIST			B_FILE_EXISTS
#define HAIKU_EINVAL			B_BAD_VALUE
#define HAIKU_ENAMETOOLONG	B_NAME_TOO_LONG
#define HAIKU_ENOENT			B_ENTRY_NOT_FOUND
#define HAIKU_EPERM			B_NOT_ALLOWED
#define HAIKU_ENOTDIR			B_NOT_A_DIRECTORY
#define HAIKU_EISDIR			B_IS_A_DIRECTORY
#define HAIKU_ENOTEMPTY		B_DIRECTORY_NOT_EMPTY
#define HAIKU_ENOSPC			B_DEVICE_FULL
#define HAIKU_EROFS			B_READ_ONLY_DEVICE
#define HAIKU_EMFILE			B_NO_MORE_FDS
#define HAIKU_EXDEV			B_CROSS_DEVICE_LINK
#define HAIKU_ELOOP			B_LINK_LIMIT
#define HAIKU_ENOEXEC			B_NOT_AN_EXECUTABLE
#define HAIKU_EPIPE			B_BUSTED_PIPE

#ifndef BUILDING_HAIKU_ERROR_MAPPER
	#undef E2BIG
	#undef ECHILD
	#undef EDEADLK
	#undef EFBIG
	#undef EMLINK
	#undef ENFILE
	#undef ENODEV
	#undef ENOLCK
	#undef ENOSYS
	#undef ENOTTY
	#undef ENXIO
	#undef ESPIPE
	#undef ESRCH
	#undef EFPOS
	#undef ESIGPARM
	#undef EDOM
	#undef ERANGE
	#undef EPROTOTYPE
	#undef EPROTONOSUPPORT
	#undef EPFNOSUPPORT
	#undef EAFNOSUPPORT
	#undef EADDRINUSE
	#undef EADDRNOTAVAIL
	#undef ENETDOWN
	#undef ENETUNREACH
	#undef ENETRESET
	#undef ECONNABORTED
	#undef ECONNRESET
	#undef EISCONN
	#undef ENOTCONN
	#undef ESHUTDOWN
	#undef ECONNREFUSED
	#undef EHOSTUNREACH
	#undef ENOPROTOOPT
	#undef ENOBUFS
	#undef EINPROGRESS
	#undef EALREADY
	#undef EILSEQ
	#undef ENOMSG
	#undef ESTALE
	#undef EOVERFLOW
	#undef EMSGSIZE
	#undef EOPNOTSUPP
	#undef ENOTSOCK
	#undef EHOSTDOWN
	#undef EBADMSG
	#undef ECANCELED
	#undef EDESTADDRREQ
	#undef EDQUOT
	#undef EIDRM
	#undef EMULTIHOP
	#undef ENODATA
	#undef ENOLINK
	#undef ENOSR
	#undef ENOSTR
	#undef ENOTSUP
	#undef EPROTO
	#undef ETIME
	#undef ETXTBSY
	#undef ENOMEM
	#undef EACCES
	#undef EINTR
	#undef EIO
	#undef EBUSY
	#undef EFAULT
	#undef ETIMEDOUT
	#undef EAGAIN
	#undef EWOULDBLOCK
	#undef EBADF
	#undef EEXIST
	#undef EINVAL
	#undef ENAMETOOLONG
	#undef ENOENT
	#undef EPERM
	#undef ENOTDIR
	#undef EISDIR
	#undef ENOTEMPTY
	#undef ENOSPC
	#undef EROFS
	#undef EMFILE
	#undef EXDEV
	#undef ELOOP
	#undef ENOEXEC
	#undef EPIPE
	
	#define E2BIG HAIKU_E2BIG
	#define ECHILD HAIKU_ECHILD
	#define EDEADLK HAIKU_EDEADLK
	#define EFBIG HAIKU_EFBIG
	#define EMLINK HAIKU_EMLINK
	#define ENFILE HAIKU_ENFILE
	#define ENODEV HAIKU_ENODEV
	#define ENOLCK HAIKU_ENOLCK
	#define ENOSYS HAIKU_ENOSYS
	#define ENOTTY HAIKU_ENOTTY
	#define ENXIO HAIKU_ENXIO
	#define ESPIPE HAIKU_ESPIPE
	#define ESRCH HAIKU_ESRCH
	#define EFPOS HAIKU_EFPOS
	#define ESIGPARM HAIKU_ESIGPARM
	#define EDOM HAIKU_EDOM
	#define ERANGE HAIKU_ERANGE
	#define EPROTOTYPE HAIKU_EPROTOTYPE
	#define EPROTONOSUPPORT HAIKU_EPROTONOSUPPORT
	#define EPFNOSUPPORT HAIKU_EPFNOSUPPORT
	#define EAFNOSUPPORT HAIKU_EAFNOSUPPORT
	#define EADDRINUSE HAIKU_EADDRINUSE
	#define EADDRNOTAVAIL HAIKU_EADDRNOTAVAIL
	#define ENETDOWN HAIKU_ENETDOWN
	#define ENETUNREACH HAIKU_ENETUNREACH
	#define ENETRESET HAIKU_ENETRESET
	#define ECONNABORTED HAIKU_ECONNABORTED
	#define ECONNRESET HAIKU_ECONNRESET
	#define EISCONN HAIKU_EISCONN
	#define ENOTCONN HAIKU_ENOTCONN
	#define ESHUTDOWN HAIKU_ESHUTDOWN
	#define ECONNREFUSED HAIKU_ECONNREFUSED
	#define EHOSTUNREACH HAIKU_EHOSTUNREACH
	#define ENOPROTOOPT HAIKU_ENOPROTOOPT
	#define ENOBUFS HAIKU_ENOBUFS
	#define EINPROGRESS HAIKU_EINPROGRESS
	#define EALREADY HAIKU_EALREADY
	#define EILSEQ HAIKU_EILSEQ
	#define ENOMSG HAIKU_ENOMSG
	#define ESTALE HAIKU_ESTALE
	#define EOVERFLOW HAIKU_EOVERFLOW
	#define EMSGSIZE HAIKU_EMSGSIZE
	#define EOPNOTSUPP HAIKU_EOPNOTSUPP
	#define ENOTSOCK HAIKU_ENOTSOCK
	#define EHOSTDOWN HAIKU_EHOSTDOWN
	#define	EBADMSG HAIKU_EBADMSG
	#define ECANCELED HAIKU_ECANCELED
	#define EDESTADDRREQ HAIKU_EDESTADDRREQ
	#define EDQUOT HAIKU_EDQUOT
	#define EIDRM HAIKU_EIDRM
	#define EMULTIHOP HAIKU_EMULTIHOP
	#define ENODATA HAIKU_ENODATA
	#define ENOLINK HAIKU_ENOLINK
	#define ENOSR HAIKU_ENOSR
	#define ENOSTR HAIKU_ENOSTR
	#define ENOTSUP HAIKU_ENOTSUP
	#define EPROTO HAIKU_EPROTO
	#define ETIME HAIKU_ETIME
	#define ETXTBSY HAIKU_ETXTBSY
	#define ENOMEM HAIKU_ENOMEM
	#define EACCES HAIKU_EACCES
	#define EINTR HAIKU_EINTR
	#define EIO HAIKU_EIO
	#define EBUSY HAIKU_EBUSY
	#define EFAULT HAIKU_EFAULT
	#define ETIMEDOUT HAIKU_ETIMEDOUT
	#define EAGAIN HAIKU_EAGAIN
	#define EWOULDBLOCK HAIKU_EWOULDBLOCK
	#define EBADF HAIKU_EBADF
	#define EEXIST HAIKU_EEXIST
	#define EINVAL HAIKU_EINVAL
	#define ENAMETOOLONG HAIKU_ENAMETOOLONG
	#define ENOENT HAIKU_ENOENT
	#define EPERM HAIKU_EPERM
	#define ENOTDIR HAIKU_ENOTDIR
	#define EISDIR HAIKU_EISDIR
	#define ENOTEMPTY HAIKU_ENOTEMPTY
	#define ENOSPC HAIKU_ENOSPC
	#define EROFS HAIKU_EROFS
	#define EMFILE HAIKU_EMFILE
	#define EXDEV HAIKU_EXDEV
	#define ELOOP HAIKU_ELOOP
	#define ENOEXEC HAIKU_ENOEXEC
	#define EPIPE HAIKU_EPIPE

	#undef errno
	#define errno (*_haiku_build_errno())

#endif	// ! BUILDING_HAIKU_ERROR_MAPPER

#ifdef __cplusplus
extern "C" {
#endif

extern int *_haiku_build_errno();

#ifdef __cplusplus
}
#endif


/*---- new error codes that can be mapped to POSIX errors ----*/
#define	B_BUFFER_OVERFLOW	HAIKU_EOVERFLOW
#define B_TOO_MANY_ARGS		HAIKU_E2BIG
#define	B_FILE_TOO_LARGE	HAIKU_EFBIG
#define B_RESULT_NOT_REPRESENTABLE	HAIKU_ERANGE
#define	B_DEVICE_NOT_FOUND	HAIKU_ENODEV
#define B_NOT_SUPPORTED		HAIKU_EOPNOTSUPP

/*-------------------------------------------------------------*/
/*----- Media Kit Errors --------------------------------------*/
enum {
  B_STREAM_NOT_FOUND = B_MEDIA_ERROR_BASE,
  B_SERVER_NOT_FOUND,
  B_RESOURCE_NOT_FOUND,
  B_RESOURCE_UNAVAILABLE,
  B_BAD_SUBSCRIBER,
  B_SUBSCRIBER_NOT_ENTERED,
  B_BUFFER_NOT_AVAILABLE,
  B_LAST_BUFFER_ERROR
};

/*-------------------------------------------------------------*/
/*----- Mail Kit Errors ---------------------------------------*/
enum
{
	B_MAIL_NO_DAEMON = B_MAIL_ERROR_BASE,
	B_MAIL_UNKNOWN_USER,
	B_MAIL_WRONG_PASSWORD,
	B_MAIL_UNKNOWN_HOST,
	B_MAIL_ACCESS_ERROR,
	B_MAIL_UNKNOWN_FIELD,
	B_MAIL_NO_RECIPIENT,
	B_MAIL_INVALID_MAIL
};

/*-------------------------------------------------------------*/
/*----- Printing Errors --------------------------------------*/
enum
{
	B_NO_PRINT_SERVER = B_PRINT_ERROR_BASE
};

/*-------------------------------------------------------------*/
/*----- Device Kit Errors -------------------------------------*/
enum
{
	B_DEV_INVALID_IOCTL = B_DEVICE_ERROR_BASE,
	B_DEV_NO_MEMORY,
	B_DEV_BAD_DRIVE_NUM,
	B_DEV_NO_MEDIA,
	B_DEV_UNREADABLE,
	B_DEV_FORMAT_ERROR,
	B_DEV_TIMEOUT,
	B_DEV_RECALIBRATE_ERROR,
	B_DEV_SEEK_ERROR,
	B_DEV_ID_ERROR,
	B_DEV_READ_ERROR,
	B_DEV_WRITE_ERROR,
	B_DEV_NOT_READY,
	B_DEV_MEDIA_CHANGED,
	B_DEV_MEDIA_CHANGE_REQUESTED,
	B_DEV_RESOURCE_CONFLICT,
	B_DEV_CONFIGURATION_ERROR,
	B_DEV_DISABLED_BY_USER,
	B_DEV_DOOR_OPEN,

	B_DEV_INVALID_PIPE,
	B_DEV_CRC_ERROR,
	B_DEV_STALLED,
	B_DEV_BAD_PID,
	B_DEV_UNEXPECTED_PID,
	B_DEV_DATA_OVERRUN,
	B_DEV_DATA_UNDERRUN,
	B_DEV_FIFO_OVERRUN,
	B_DEV_FIFO_UNDERRUN,
	B_DEV_PENDING,
	B_DEV_MULTIPLE_ERRORS,
	B_DEV_TOO_LATE,
};

#endif /* _ERRORS_H */
