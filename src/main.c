#include <fcntl.h>
#include <errno.h>
#include <termios.h>
#include <unistd.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <linux/fb.h>
#include "print.h"
#include "fb.h"
#include "gpio.h"
#include "tp.h"

int main() {
    print_init();
    gpio_init();
    tp_init();
    fb_init();

    print("Main", "Hello, World! %d\r\n", 100);

    for(int y = 0; y < 10; y++)
        for(int x = 0; x < 100; x++)
            fb_setpx(400 + x, 500 + y, 0xff0000);
    for(int y = 0; y < 10; y++)
        for(int x = 0; x < 100; x++)
            fb_setpx(500 + x, 510 + y, 0x00ff00);
    for(int y = 0; y < 10; y++)
        for(int x = 0; x < 100; x++)
            fb_setpx(600 + x, 520 + y, 0x0000ff);

    print("Nothing", "Meow!! %d Meow!!!\r\n", 200);

    // gpio_pinmode(12, false);
    gpio_pinmode(13, true);

    // gpio_write(12, false);
    // gpio_write(12, true);

    sleep(1);

    while(1) { 
        struct touch_info ti = tp_get(); 
        if(ti.isTouched) fb_setpx(ti.x, ti.y, 0xffffff);
    }
}