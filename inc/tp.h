#pragma once

#include "defines.h"
#include "print.h"

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <stdint.h>
#include <stdlib.h>
#include <linux/gpio.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <linux/input.h>

struct touch_info {
    bool isTouched;
    uint16_t x;
    uint16_t y;
};

void tp_init();
struct touch_info tp_get();