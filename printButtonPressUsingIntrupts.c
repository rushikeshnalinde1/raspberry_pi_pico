#include "pico\stdlib.h"
#include <stdio.h>

#define button 16

void gpio_callback(uint gpio, uint32_t events){
    static int count=0;
    count++;
    printf("Button pressed %d times\n", count);
}

int main(){
    stdio_init_all();
    gpio_init(button);
    gpio_set_dir(button, GPIO_IN);
    gpio_pull_down(button);
    gpio_set_irq_enabled_with_callback(button, GPIO_IRQ_EDGE_RISE, true, &gpio_callback);
    while(1){
        tight_loop_contents();
    }
}
