#define WANT_IRS_NIS
#undef WANT_IRS_PW
#undef WANT_IRS_GR
#define SIG_FN void
#define ISC_SOCKLEN_T unsigned long

#if defined(HAS_PTHREADS) && defined(_REENTRANT)
#define DO_PTHREADS
#endif

#include <limits.h>	/* _POSIX_PATH_MAX */
#include <sys/select.h>	/* fdset */
#include <sys/timers.h>	/* struct timespec */
#include <sys/machine.h>/* endianness */

#define GETGROUPLIST_ARGS const char *name, gid_t basegid, gid_t *groups, \
		      int *ngroups
#ifdef __GNUC__
#define ISC_FORMAT_PRINTF(fmt, args) \
	__attribute__((__format__(__printf__, fmt, args)))
#else
#define ISC_FORMAT_PRINTF(fmt, args)
#endif
