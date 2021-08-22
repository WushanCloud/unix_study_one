/*================================================================
*   Copyright (C) 2021 Sangfor Ltd. All rights reserved.
*   
*   文件名称：unp.h
*   创 建 者：wushan
*   创建日期：2021年08月20日
*   描    述：unix编程中通用的头文件
*
================================================================*/


#ifndef __unp_h 
#define __unp_h

#include "./config.h"

#include <sys/types.h>      /* 基础系统数据类型 */
#include <sys/socket.h>     /* 基础socket定义 */
#include <sys/time.h>       /* 超时时间等时间定义 */
#include <time.h>
#include <netinet/in.h>     /* sockaddr_in 和其他网络定义 */
#include <arpa/inet.h>      /* inet(3) 方法 */
#include <errno.h>          
#include <fcntl.h>          /* for nonblocking */
#include <netdb.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/uio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/un.h>

#ifdef  HAVE_SYS_SELECT_H
#include <sys/select.h>
#endif  // HAVE_SYS_SELECT_H 

#ifdef  HAVE_POLL_H
#include <poll.h>
#endif  // HAVE_POLL_H 

#ifdef HAVE_STRINGS_H
#include <strings.h>
#endif  // HAVE_STRINGS_H 

/* 下面三个头文件是一般情况下需要的socket文件：
 * <sys/ioctl.h> <sys/filio.h> <sys/sockio.h>
 */
#ifdef HAVE_SYS_IOCTL_H
#include <sys/ioctl.h>
#endif  // HAVE_SYS_IOCTL_H 

#ifdef HAVE_SYS_FILIO_H
#include <sys/filio.h>
#endif  // HAVE_SYS_FILIO_H 

#ifdef HAVE_SYS_SOCKIO_H
#include <sys/sockio.h>
#endif  // HAVE_SYS_SOCKIO_H 

#ifdef HAVE_PTHREAD_H
#include <pthread.h>
#endif  // HAVE_PTHREAD_H 

/* 一些方法宏定义 */

#ifdef __osf__
#undef recv
#undef send 
#define recv(a, b, c, d)  recvfrom(a, b, c, d, 0, 0)
#define send(a, b, c, d)  sendto(a, b, c, d, 0, 0)
#endif  // __osf__

#ifndef INADDR_NONE
#define INADDR_NONE 0xffffffff  /* should have been in <netinet/in.h> */
#endif  // INADDR_NONE 

#ifndef SHUT_RD
#define SHUT_RD   0
#define SHUT_WR   1
#define SHUT_RDWR 2
#endif 

#ifndef INET_ADDRSTRLEN
#define INET_ADDRSTRLEN 16      /* ddd.ddd.ddd.ddd\0 */
#endif  // INET_ADDRSTRLEN 

#ifndef INET6_ADDRSTRLEN
#define INET6_ADDRSTRLEN 46     /* max size of IPV6 address string :
                                  "xxxx:xxxx:xxxx:xxxx:xxxx:xxxx:xxxx:xxxx" or 
                                  "xxxx:xxxx:xxxx:xxxx:xxxx:xxxx:ddd.ddd.ddd.ddd\0"
                                */
#endif  // INET6_ADDRSTRLEN 

/* Define bzreo() as a macro if it's not in standard C library */
#ifndef HAVE_BZERO
#define bzreo(ptr, n)     memset(ptr, 0, n)
#endif  // HAVE_BZERO 

#ifndef HAVE_GETHOSTBYNAME2
#define gethostbyname2(host, family)  gethostbyname((host))
#endif 

/* 重复包含 netinet.h中有in_pktinfo的定义，且不一样
 * The structure returned by recvfrom_flags() *
struct in_pktinfo{
    struct in_addr  ipi_addr;       * dst ipv4 address * 
    int             ipi_ifindex;    * received interface index *
};
*/

#ifndef CMSG_LEN
#define CMSG_LEN(size)    (sizeof(struct cmsghdr) + (size))
#endif // CMSG_LEN


#ifndef CMSG_SPACE
#define CMSG_SPACE(size)  (sizeof(struct cmsghdr) + (size))
#endif // CMSG_SPACE

#ifndef SUN_LEN 
#define SUN_LEN(su) \
  (sizeof(*(su)) - sizeof((su)->sun_path) + strlen((su)->sun_path))
#endif // SUN_LEN 

#ifndef AF_LOCAL
#define AF_LOCAL      AF_UNIX
#endif 
#ifndef PH_LOCAL
#define PH_LOCAL      PH_UNIX
#endif 


#ifndef INFTIM
#define INFTIM    (-1)
#ifdef HAVE_POLL_H 
#define INFTIM_UNPH
#endif
#endif

#define LISTENQ       1024

#define MAXLINE       4096
#define MAXSOCKADDR   128
#define BUFFSIZE      8192          /* reads and writes */

#define SERV_PORT     9877
#define SERV_PORT_STR "9877"
#define UNIXSTR_PATH  "/tmp/unix.str"
#define UNIXDG_PATH   "/tmp/unix.dg"

#define SA struct sockaddr 
#define FILE_MODE     (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)
#define DIR_MODE      (FILE_MODE | S_IXUSR | S_IXGRP | S_IXOTH)

typedef void Sigfunc (int); /* for signal handlers */
#define min(a, b)   ((a) < (b) ? (a) : (b))
#define max(a, b)   ((a) > (b) ? (a) : (b))

#ifndef HAVE_ADDRINFO_STRUCT
#include "../lib/addrinfo.h"
#endif 

#ifndef HAVE_IF_NAMEINDEX_STRUCT
struct if_nameindex {
    unsigned int  if_index;
    char        * if_name;
};
#endif

/* 重复包含：time.h中有timespec的定义
#ifndef HAVE_TIMESPEC_STRUCT
struct timespec {
  time_t  tv_sec;
  long    tv_nsec;
};
#endif
*/
#endif // __unp_h
