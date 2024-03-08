#include "fb.h"

#include "print.h"

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <sys/ioctl.h>

int fbfd;
char* fb_buffer;
struct fb_var_screeninfo fb_vinfo;
struct fb_fix_screeninfo fb_finfo;

void fb_init() {
    fbfd = open(FRAMEBUFFER_LOCATION, O_RDWR);
    if (fbfd == -1) {
        print("Framebuffer", "Error: cannot open framebuffer device (-1)!\r\n");
        exit(1);
    }
    print("Framebuffer", "Init!!!\r\n");

    // Get fixed screen information
    if (ioctl(fbfd, FBIOGET_FSCREENINFO, &fb_finfo) == -1) {
        print("Framebuffer", "Error reading fixed information\r\n");
        exit(2);
    }

    // Get variable screen information
    if (ioctl(fbfd, FBIOGET_VSCREENINFO, &fb_vinfo) == -1) {
        print("Framebuffer", "Error reading variable information\r\n");
        exit(3);
    }

    print("Framebuffer", "Display info: %dx%d, %dbpp\r\n", fb_vinfo.xres, fb_vinfo.yres, fb_vinfo.bits_per_pixel);
    
    fb_buffer = (char*) mmap(0, fb_vinfo.xres * fb_vinfo.yres * fb_vinfo.bits_per_pixel / 8, PROT_READ | PROT_WRITE, MAP_SHARED, fbfd, 0);
    if ((int)fb_buffer == -1) {
        print("Framebuffer", "Error: failed to map framebuffer device to memory\r\n");
        exit(4);
    }
    print("Framebuffer", "Successfully memory-mapped!\r\n");
}

void fb_setpx(uint16_t x, uint16_t y, uint32_t color) {
    uint32_t location = (x + fb_vinfo.xoffset) * (fb_vinfo.bits_per_pixel / 8) + (y + fb_vinfo.yoffset) * fb_finfo.line_length;
    if (fb_vinfo.bits_per_pixel == 32) {
        *(fb_buffer + location) = color & 0xff;
        *(fb_buffer + location + 1) = (color >> 8) & 0xff;
        *(fb_buffer + location + 2) = (color >> 16) & 0xff;
        *(fb_buffer + location + 3) = 0;
    } else {
        int b = color & 0xff;
        int g = (color >> 8) & 0xff;
        int r = (color >> 16) & 0xff;
        unsigned short int t = r << 11 | g << 5 | b;
        *((unsigned short int*)(fb_buffer + location)) = t;
    }
}