#ifndef _COMMON_H_
#define _COMMON_H_

#endif

#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>   /* basic socket definition */
#include<sys/types.h>
#include<signal.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>  /* for inet_pton and the like */
#include<stdarg.h>   /* for variable argument function , like err_n_die */
#include<errno.h>
#include<fcntl.h>
#include<sys/time.h>
#include<sys/ioctl.h>
#include<netdb.h>
#include <stdarg.h>

// Useful constants
#define SERVER_PORT 18001

#define MAXLINE 4096
#define SA struct sockaddr

void err_n_die(const char *fmt, ...);
char *bin2hex(const unsigned char *input, size_t len);
