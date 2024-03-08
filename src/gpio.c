#include "gpio.h"

int gpio_chip_fd;
struct gpiochip_info gpio_info;
// struct gpioline_info gpio_line_info;

void gpio_init() {
    gpio_chip_fd = open(GPIO_DEV_LOCATION, O_WRONLY);
    if (gpio_chip_fd == -1) {
        print("GPIO",  "Unable to open GPIO chip!!");
        exit(1);
    }
    print("GPIO", "Init!!\r\n");

    if(ioctl(gpio_chip_fd, GPIO_GET_CHIPINFO_IOCTL, &gpio_info) == -1) {
        print("GPIO", "Unable to get GPIO info!");
        exit(1);
    }
    print("GPIO", "GPIO Info:\r\n");
    print("GPIO", "Chip name: %s\r\n", gpio_info.name);
    print("GPIO", "Chip label: %s\r\n", gpio_info.label);
    print("GPIO", "Chip lines: %d\r\n", gpio_info.lines);
}

void gpio_pinmode(uint8_t gpiopin, bool input) {
    struct gpiohandle_request rq;
    rq.lineoffsets[0] = gpiopin;
    rq.lines = 1;
    rq.flags = input ? GPIOHANDLE_REQUEST_INPUT : GPIOHANDLE_REQUEST_OUTPUT;

    if (ioctl(gpio_chip_fd, GPIO_GET_LINEHANDLE_IOCTL, &rq) == -1) {
        print("GPIO", "Unable to set pinmode!");
        return;
    }

    close(rq.fd);
}

bool gpio_read(uint8_t gpiopin) {
    struct gpiohandle_request rq;
    struct gpiohandle_data data;
    
    rq.lineoffsets[0] = gpiopin;
    rq.flags = GPIOHANDLE_REQUEST_INPUT;
    rq.lines = 1;
    
    if (ioctl(gpio_chip_fd, GPIO_GET_LINEHANDLE_IOCTL, &rq) == -1) {
        print("GPIO", "Unable to get line handle from ioctl : %%s", strerror(errno));
        return;
    }
    
    if (ioctl(rq.fd, GPIOHANDLE_GET_LINE_VALUES_IOCTL, &data) == -1) {
        print("GPIO", "Unable to get line value using ioctl : %%s", strerror(errno));
    } 

    close(rq.fd);
    return data.values[0] == true;
}

void gpio_write(uint8_t gpiopin, bool value) {
    struct gpiohandle_request rq;
    struct gpiohandle_data data;
    
    rq.lineoffsets[0] = gpiopin;
    rq.flags = GPIOHANDLE_REQUEST_OUTPUT;
    rq.lines = 1;
    
    if (ioctl(gpio_chip_fd, GPIO_GET_LINEHANDLE_IOCTL, &rq) == -1) {
        print("GPIO", "Unable to get line handle from ioctl : %%s", strerror(errno));
        return;
    }

    data.values[0] = value;
    if (ioctl(rq.fd, GPIOHANDLE_SET_LINE_VALUES_IOCTL, &data) == -1) {
        print("GPIO", "Unable to set line value using ioctl : %%s", strerror(errno));
    }

    close(rq.fd);
}