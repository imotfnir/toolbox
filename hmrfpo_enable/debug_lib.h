#ifndef _DEBUG_LIB_H_
#define _DEBUG_LIB_H_

#include <stdio.h>
#include <stdarg.h>
#include <sys/types.h>

#define DEBUG_FATAL 1
#define DEBUG_ERROR 2
#define DEBUG_WARN  3
#define DEBUG_INFO  4
#define DEBUG_DEBUG 5
#define DEBUG_TRACE 6

void debug(__uint8_t debug_level, char *format, ...);

#endif // _DEBUG_LIB_H_