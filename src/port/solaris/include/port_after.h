#ifndef	PORT_AFTER_H
#define	PORT_AFTER_H
#include "os_version.h"

#undef HAVE_SA_LEN
#define USE_POSIX
#define POSIX_SIGNALS
#define NETREAD_BROKEN
#define USE_WAITPID
#define HAVE_FCHMOD
#define NEED_PSELECT
#define SETGRENT_VOID
#define SETPWENT_VOID
#define SIOCGIFCONF_ADDR
#define IP_OPT_BUF_SIZE 40
#define HAVE_CHROOT
#define CAN_CHANGE_ID
#define POSIX_GETPWNAM_R
#define POSIX_GETPWUID_R
#define POSIX_GETGRGID_R
#define POSIX_GETGRNAM_R
#define NEED_SECURE_DIRECTORY

#define PORT_NONBLOCK	O_NONBLOCK
#define PORT_WOULDBLK	EWOULDBLOCK
#define WAIT_T		int
#define INADDR_NONE	0xffffffff

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/param.h>
#if (!defined(BSD)) || (BSD < 199306)
#include <sys/bitypes.h>
#endif
#include <sys/time.h>

#ifndef MIN
# define MIN(x, y)	((x > y) ?y :x)
#endif
#ifndef MAX
# define MAX(x, y)	((x > y) ?x :y)
#endif

/*
 * We need to know the IPv6 address family number even on IPv4-only systems.
 * Note that this is NOT a protocol constant, and that if the system has its
 * own AF_INET6, different from ours below, all of BIND's libraries and
 * executables will need to be recompiled after the system <sys/socket.h>
 * has had this type added.  The type number below is correct on most BSD-
 * derived systems for which AF_INET6 is defined.
 */
#ifndef AF_INET6
#define AF_INET6	24
#endif

#ifndef	PF_INET6
#define PF_INET6	AF_INET6
#endif
#include <port_ipv6.h>

#ifndef HAS_INET6_STRUCTS
/* Replace with structure from later rev of O/S if known. */
struct in6_addr {
	u_int8_t	s6_addr[16];
};

/* Replace with structure from later rev of O/S if known. */
struct sockaddr_in6 {
#ifdef	HAVE_SA_LEN
	u_int8_t	sin6_len;	/* length of this struct */
	u_int8_t	sin6_family;	/* AF_INET6 */
#else
	u_int16_t	sin6_family;	/* AF_INET6 */
#endif
	u_int16_t	sin6_port;	/* transport layer port # */
	u_int32_t	sin6_flowinfo;	/* IPv6 flow information */
	struct in6_addr	sin6_addr;	/* IPv6 address */
	u_int32_t	sin6_scope_id;	/* set of interfaces for a scope */
};

#ifndef IN6ADDR_ANY_INIT
#define	IN6ADDR_ANY_INIT	{{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}}
#endif
#ifndef IN6ADDR_LOOPBACK_INIT
#define	IN6ADDR_LOOPBACK_INIT	{{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1}}
#endif
#endif	/* HAS_INET6_STRUCTS */

#if defined(NEED_SOCKADDR_STORAGE) || !defined(HAS_INET6_STRUCTS)
#define __SS_MAXSIZE 128
#define __SS_ALLIGSIZE (sizeof (long))

struct sockaddr_storage {
#ifdef  HAVE_SA_LEN
        u_int8_t        ss_len;       /* address length */
        u_int8_t        ss_family;    /* address family */
        char            __ss_pad1[__SS_ALLIGSIZE - 2 * sizeof(u_int8_t)];
        long            __ss_align;
        char            __ss_pad2[__SS_MAXSIZE - 2 * __SS_ALLIGSIZE];
#else
        u_int16_t       ss_family;    /* address family */
        char            __ss_pad1[__SS_ALLIGSIZE - sizeof(u_int16_t)];
        long            __ss_align;
        char            __ss_pad2[__SS_MAXSIZE - 2 * __SS_ALLIGSIZE];
#endif
};
#endif


#if !defined(HAS_INET6_STRUCTS) || defined(NEED_IN6ADDR_ANY)
#define in6addr_any isc_in6addr_any
extern const struct in6_addr in6addr_any;
#endif

#ifndef IN6_ARE_ADDR_EQUAL
#define IN6_ARE_ADDR_EQUAL(a,b) \
   (memcmp(&(a)->s6_addr[0], &(b)->s6_addr[0], sizeof(struct in6_addr)) == 0)
#endif

#ifndef IN6_IS_ADDR_UNSPECIFIED
#define IN6_IS_ADDR_UNSPECIFIED(a)      \
	IN6_ARE_ADDR_EQUAL(a, &in6addr_any)
#endif

#ifndef IN6_IS_ADDR_SITELOCAL
#define IN6_IS_ADDR_SITELOCAL(a)        \
	(((a)->s6_addr[0] == 0xfe) && (((a)->s6_addr[1] & 0xc0) == 0xc0))
#endif

#ifndef IN6_IS_ADDR_MULTICAST
#define IN6_IS_ADDR_MULTICAST(a)        ((a)->s6_addr[0] == 0xff)
#endif

#ifndef __IPV6_ADDR_MC_SCOPE
#define __IPV6_ADDR_MC_SCOPE(a)         ((a)->s6_addr[1] & 0x0f)
#endif

#ifndef __IPV6_ADDR_SCOPE_SITELOCAL
#define __IPV6_ADDR_SCOPE_SITELOCAL 0x05
#endif

#ifndef __IPV6_ADDR_SCOPE_ORGLOCAL
#define __IPV6_ADDR_SCOPE_ORGLOCAL  0x08
#endif

#ifndef IN6_IS_ADDR_MC_SITELOCAL
#define IN6_IS_ADDR_MC_SITELOCAL(a)     \
	(IN6_IS_ADDR_MULTICAST(a) &&    \
	 (__IPV6_ADDR_MC_SCOPE(a) == __IPV6_ADDR_SCOPE_SITELOCAL))
#endif

#ifndef IN6_IS_ADDR_MC_ORGLOCAL
#define IN6_IS_ADDR_MC_ORGLOCAL(a)      \
	(IN6_IS_ADDR_MULTICAST(a) &&    \
	 (__IPV6_ADDR_MC_SCOPE(a) == __IPV6_ADDR_SCOPE_ORGLOCAL))
#endif

#ifndef INET6_ADDRSTRLEN
#define INET6_ADDRSTRLEN 46
#endif

/*
 * Prior to 2.6, Solaris needs a prototype for gethostname().
 */
#if (OS_MAJOR == 5 && OS_MINOR < 6)
extern int gethostname(char *, size_t);
#endif
/*
 * gethostid() was not available until 2.5
 * setsockopt(SO_REUSEADDR) fails on unix domain sockets before 2.5
 * use ioctl(FIONBIO) rather than fcntl() calls to set/clear non-blocking i/o.
 */
#if (OS_MAJOR == 5 && OS_MINOR < 5)
#define GET_HOST_ID_MISSING
#define NO_UNIX_REUSEADDR
#define USE_FIONBIO_IOCTL
#endif

#define NEED_STRSEP
extern char *strsep(char **, const char *);

#define NEED_DAEMON
int daemon(int nochdir, int noclose);

/*
 * Solaris defines this in <netdb.h> instead of in <sys/param.h>.  We don't
 * define it in our <netdb.h>, so we define it here.
 */
#ifndef MAXHOSTNAMELEN
#define MAXHOSTNAMELEN 256
#endif

/*
 * Solaris 2.5 and later have getrlimit(), setrlimit() and getrusage().
 */
#if (OS_MAJOR > 5 || (OS_MAJOR == 5 && OS_MINOR >= 5))
#include <sys/resource.h>
#define HAVE_GETRUSAGE
#define RLIMIT_TYPE rlim_t
#define RLIMIT_FILE_INFINITY
#endif

/*
 * Solaris's strerror() returns NULL if errnum is out of range.  We need a
 * strerror() that always returns a non NULL.
 */
#define NEED_STRERROR
const char *isc_strerror(int errnum);
#define strerror isc_strerror

#ifndef ISC_FACILITY
#define ISC_FACILITY LOG_DAEMON
#endif

int isc__gettimeofday(struct timeval *, struct timezone *);
#define gettimeofday isc__gettimeofday

#define UNUSED(x) (x) = (x)
#define DE_CONST(konst, var) \
	do { \
		union { const void *k; void *v; } _u; \
		_u.k = konst; \
		var = _u.v; \
	} while (0) 
#endif /* ! PORT_AFTER_H */