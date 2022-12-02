#include <debug_lib.h>

void debug(__uint8_t debug_level, char *format, ...) {
    va_list marker;

    va_start(marker, format);
    if(DEBUG_LEVEL >= debug_level) {
        vprintf(format, marker);
    }
    va_end(marker);
}