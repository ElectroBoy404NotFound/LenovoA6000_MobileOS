#include "str_utils.h"

#include <stdarg.h>
#include <stdio.h>

// char termPrintBuf[4096];
// int formatStr(const char* format, ...) {
//     va_list args;
//     va_start(args, format);
//     int cnt = vsnprintf(termPrintBuf, sizeof(termPrintBuf), format, args);
//     va_end(args);
//     return cnt;
// }

struct formatted_str format_string(const char* format, ...) {
    struct formatted_str str;
    va_list args;
    va_start(args, format);
    str.char_cnt = vsnprintf(str.buf, sizeof(str.buf), format, args);
    va_end(args);
    return str;
}