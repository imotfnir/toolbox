#ifndef _DEBUG_LIB_H_
#define _DEBUG_LIB_H_

#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Marco Variable
// Debug Level
#define DEBUG_FATAL     1
#define DEBUG_ERROR     2
#define DEBUG_WARN      3
#define DEBUG_INFO      4
#define DEBUG_DEBUG     5
#define DEBUG_TRACE     6
#define DEBUG_FUNC_CALL 7

// Marco Function
#define STR_VALUE(arg) #arg

#define FATAL                                                                                                 \
    do {                                                                                                      \
        fprintf(stderr, "Error at line %d, file %s (%d) [%s]\n", __LINE__, __FILE__, errno, strerror(errno)); \
        exit(1);                                                                                              \
    } while(0)

#define ERROR                                                                                                 \
    do {                                                                                                      \
        fprintf(stderr, "Error at line %d, file %s (%d) [%s]\n", __LINE__, __FILE__, errno, strerror(errno)); \
    } while(0)

#define TRACE_PRINT(format, ...)                                                                                        \
    do {                                                                                                                \
        if(IS_TRACE) {                                                                                                  \
            debug_print(DEBUG_TRACE, format, __VA_ARGS__);                                                              \
            debug_print(DEBUG_TRACE, "\t# Trace at func (%s), line (%d) in file (%s), \n", __func__, __LINE__, __FILE__); \
        }                                                                                                               \
    } while(0)

// Function declaration
void debug_print(uint8_t debug_level, char *format, ...);

#endif //_DEBUG_LIB_H_
