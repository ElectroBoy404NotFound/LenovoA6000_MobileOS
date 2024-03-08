#include "print.h"

#include <fcntl.h>
#include <errno.h>
#include <termios.h>
#include <unistd.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#include "str_utils.h"

const char* termPrintBuf;
int tty_port;
void print_init() {
    tty_port = open(TTY_LOCATION, O_RDWR);
    while(tty_port < 0) tty_port = open(TTY_LOCATION, O_RDWR);
    termPrintBuf = malloc(4096 * sizeof(char));
    write(tty_port, "[Print] Init!!\r\n", sizeof("[Print] Init!!\r\n"));
}

void print(const char* lib, const char *format, ...) {
    va_list args;
    va_start(args, format);
    
    int cnt = vsnprintf(termPrintBuf, 4096, format, args);
    char gvfmt[cnt + 1];
    memcpy(gvfmt, termPrintBuf, cnt);
    gvfmt[cnt] = 0;

    va_end(args);

    struct formatted_str str = format_string("[%s] %s", lib, gvfmt);
    write(tty_port, str.buf, str.char_cnt);
}