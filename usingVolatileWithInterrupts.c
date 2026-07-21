#include "pico/stdlib.h"
#include <stdio.h>
#define button 16
#define led 17
absolute_time_t last;

volatile bool ledToggle = false;

void toggle(uint gpio, uint32_t event){
    absolute_time_t now = get_absolute_time();
    if (absolute_time_diff_us(last, now) > 100000) { // 100ms debounce
        ledToggle = true;
        last = now;
    }
}

int main(){
    stdio_init_all();
    gpio_init(button);
    gpio_init(led);
    gpio_set_dir(button, GPIO_IN);
    gpio_set_dir(led, GPIO_OUT);
    gpio_pull_down(button);
    bool ledState = false;
    last = get_absolute_time();


    gpio_set_irq_enabled_with_callback(
        button,
        GPIO_IRQ_EDGE_RISE,
        true,
        &toggle
    );

    while(true){
        if(ledToggle){
            ledState = !ledState;
            gpio_put(led, ledState);
            ledToggle = false;
            
        }
        tight_loop_contents();
    }
    return 0;
}
