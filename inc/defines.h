#pragma once

#include <stdint.h>
#include <stdbool.h>

// Device file locations
#define TTY_LOCATION         "/dev/tty0"
#define FRAMEBUFFER_LOCATION "/dev/fb0"
#define GPIO_DEV_LOCATION    "/dev/gpiochip0"

// Touch screen
#define TOUCH_LOCATION "/dev/input/event2"
#define TOUCH_IRQ_GPIO 13