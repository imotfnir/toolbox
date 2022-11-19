#include "debug_lib.h"

void debug(__uint8_t debug_level, char *format, ...) {
    va_list marker;

    va_start(marker, format);
    if(debug_level >= DEBUG_LEVEL) {
        vprintf(format, marker);
    }
    va_end(marker);
}