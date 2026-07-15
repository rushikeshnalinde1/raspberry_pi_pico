#include "pico/stdlib.h"
#include <stdio.h>
#define led 16

bool blink(struct repeating_timer *t){
    static bool ledState = false;
    gpio_put(led, ledState);
    ledState = !ledState;
    printf("%d ", ledState); 
    return true;
} 

int main(){
    stdio_init_all();
    gpio_init(16);
    gpio_set_dir(led, GPIO_OUT);
    struct repeating_timer timer;
    add_repeating_timer_ms(1000, blink, NULL, &timer);

    while(true){
        tight_loop_contents();
    }
}
