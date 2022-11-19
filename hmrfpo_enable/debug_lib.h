#ifndef _DEBUG_LIB_H_
#define _DEBUG_LIB_H_

#include <stdio.h>
#include <stdarg.h>
#include <sys/types.h>

void debug(__uint8_t debug_level, char *format, ...);

#endif // _DEBUG_LIB_H_