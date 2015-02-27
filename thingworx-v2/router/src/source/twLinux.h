/*
 *  Copyright (C) 2014 ThingWorx Inc.
 *
 *  Wrappers for OS Specific functionality
 */

#ifndef TW_LINUX_H
#define TW_LINUX_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <dirent.h>
#include <stdio.h>

/********************************/
/*      Which TLS Library?      */
/********************************/
/* 
Define which pluggable TLS library is used.  Default is AxTLS.  The NO_TLS option
turns off encryption altogether.  This is useful for debugging but IS NOT RECOMMENDED 
FOR PRODUCTION ENVIRONMENTS.  Refer to the documentation on how to add another TLS
library.
*/
/*#define TW_TLS_INCLUDE "twAxTls.h" */
/*#define TW_TLS_INCLUDE "twOpenSSL.h" */

#define TW_TLS_INCLUDE "twNoTls.h" 
#define NO_TLS 1

/* Logging */
#ifdef DEBUG
#ifndef DBG_LOGGING
#define DBG_LOGGING
#endif
#endif

#ifdef DBG_LOGGING
#define TW_LOGGER_BUF_SIZE 4096 /* Max size of log buffer */
#define TW_LOG(level, fmt, ...)  twLog(level, fmt, ##__VA_ARGS__)
#define TW_LOG_HEX(msg, preamble, length)   twLogHexString(msg, preamble, length)
#define TW_LOG_MSG(msg, preamble)   twLogMessage(msg, preamble)
#else
#define TW_LOGGER_BUF_SIZE 128
#define TW_LOG(level, fmt, ...)
#define TW_LOG_HEX(msg, preamble, length)
#define TW_LOG_MSG(msg, preamble) 
#endif

/* Time */
typedef uint64_t DATETIME;

/* Mutex */
#define TW_MUTEX pthread_mutex_t *

/* Sockets */
#define IPV4 AF_INET
#define IPV6 AF_INET6
#define TW_SOCKET_TYPE int
#define TW_ADDR_INFO struct addrinfo

/* Tasks */
#define TICKS_PER_MSEC 1

/* Memory */
#define TW_MALLOC(a) malloc(a) 
#define TW_CALLOC(a, b) calloc(a,b)
#define TW_REALLOC(a, b) realloc(a, b)
#define TW_FREE(a) free(a)

/* File Transfer */
#define TW_FOPEN(a,b) fopen(a,b)
#define TW_FCLOSE(a) fclose(a)
#define TW_FREAD(a,b,c,d) fread(a,b,c,d)
#define TW_FWRITE(a,b,c,d) fwrite(a,b,c,d)
#define TW_FSEEK(a,b,c) fseeko(a,b,c)
#define TW_FERROR(a) ferror(a)

#define TW_FILE_HANDLE FILE*
#define TW_FILE_DELIM '/'
#define TW_FILE_DELIM_STR "/"
#define TW_FILE_CASE_SENSITVE TRUE
#define TW_DIR DIR *
#define ERROR_NO_MORE_FILES 0

/* Misc */
#define INLINE 

#ifndef OS_IOS
/* getch */
char getch();
#endif

#endif
