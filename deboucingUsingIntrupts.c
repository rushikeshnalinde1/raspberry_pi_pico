#include "pico\stdlib.h"
#include <stdio.h>
absolute_time_t last_press;

#define button 16

void gpio_callback(uint gpio, uint32_t events){
    absolute_time_t now = get_absolute_time();
    if(absolute_time_diff_us(last_press, now) < 200000) {
        return; // Ignore if pressed within 20ms
    }
    last_press = now;
    static int count=0;
    count++;
    printf("Button pressed %d times\n", count);
}

int main(){
    stdio_init_all();
    gpio_init(button);
    gpio_set_dir(button, GPIO_IN);
    gpio_pull_down(button);
    last_press = get_absolute_time();
    gpio_set_irq_enabled_with_callback(button, GPIO_IRQ_EDGE_RISE, true, &gpio_callback);
    while(1){
        tight_loop_contents();
    }
}
