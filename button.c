#include "pico/stdlib.h"

#define LedPin1 16
#define LedPin2 17

#define ButtonPin1 18
#define ButtonPin2 19


int main(){
    stdio_init_all();
    gpio_init(LedPin1);
    gpio_set_dir(LedPin1, GPIO_OUT);
    gpio_init(LedPin2);
    gpio_set_dir(LedPin2, GPIO_OUT);

    gpio_init(ButtonPin1);
    gpio_set_dir(ButtonPin1, GPIO_IN);
    gpio_pull_down(ButtonPin1);
    gpio_init(ButtonPin2);
    gpio_set_dir(ButtonPin2, GPIO_IN);
    gpio_pull_down(ButtonPin2);
    
    while(true){
        if(gpio_get(ButtonPin1) == 0){
            gpio_put(LedPin1, 1);
        } else {
            gpio_put(LedPin1, 0);
        }
        if(gpio_get(ButtonPin2) == 0){
            gpio_put(LedPin2, 1);
        } else {
            gpio_put(LedPin2, 0);
        }
        sleep_ms(10);
    }
    return 0;
}