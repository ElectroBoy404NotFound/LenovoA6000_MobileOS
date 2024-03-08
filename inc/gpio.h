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

void gpio_init();
void gpio_pinmode(uint8_t gpiopin, bool input);