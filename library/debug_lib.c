#include <debug_lib.h>

#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

void debug_print(uint8_t debug_level, char *format, ...) {
    va_list marker;

    va_start(marker, format);
    if(DEBUG_LEVEL <= debug_level) {
        return;
    }
    if(debug_level <= DEBUG_WARN) { /*if error, output to stderr*/
        vfprintf(stderr, format, marker);
        return;
    }
    vprintf(format, marker);
    va_end(marker);
}
