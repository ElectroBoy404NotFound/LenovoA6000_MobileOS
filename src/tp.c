#include "tp.h"

int tp_fd;
void tp_init() {
    tp_fd = open(TOUCH_LOCATION, O_RDONLY | O_NONBLOCK);
    if(tp_fd == -1) {
        print("Touch", "Error: Unable to open %s!\r\n", TOUCH_LOCATION);
        exit(-1);
    }
    print("Touch", "Init!!");
    
    char name[256] = "Unknown";
    ioctl(tp_fd, EVIOCGNAME(sizeof(name)), name);
    print("Touch", "Touch Device name: %s\r\n", name);
}

struct touch_info ti;
struct touch_info tp_get() {
    ti.isTouched = !(gpio_read(TOUCH_IRQ_GPIO));
    if(!ti.isTouched) return ti;

    struct input_event ev;
    if(!(read(tp_fd, &ev, sizeof(struct input_event)) < sizeof(struct input_event))) {
        if(ev.type == EV_ABS && (ev.code == ABS_X || ev.code == ABS_Y)) {
            // print("Touch", "%s = %d\r\n", ev.code == ABS_X ? "X" : "Y", ev.value);
            if(ev.code == ABS_X) ti.x = ev.value;
            if(ev.code == ABS_Y) ti.y = ev.value;
        }
    } else {
        print("Touch", "Unknown error!!\r\n");
    }
    return ti;
}