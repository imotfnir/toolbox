#ifndef _DEBUG_LIB_H_
#define _DEBUG_LIB_H_

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Marco Variable
#define DEBUG_FATAL 1
#define DEBUG_ERROR 2
#define DEBUG_WARN 3
#define DEBUG_INFO 4
#define DEBUG_DEBUG 5
#define DEBUG_TRACE 6

// Marco Function
#define FATAL                                                                                                 \
    do {                                                                                                      \
        fprintf(stderr, "Error at line %d, file %s (%d) [%s]\n", __LINE__, __FILE__, errno, strerror(errno)); \
        exit(1);                                                                                              \
    } while(0)

void debug(__uint8_t debug_level, char *format, ...);

#endif //_DEBUG_LIB_H_