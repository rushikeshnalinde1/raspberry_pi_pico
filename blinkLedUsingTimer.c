#include "pico/stdlib.h"

#define ledPin 16

bool blink_callback(struct repeating_timer *t)
{
    static bool led_state = false;
    led_state = !led_state;
    gpio_put(ledPin, led_state);
    return true;
}

int main(){
    gpio_init(ledPin);
    gpio_set_dir(ledPin, GPIO_OUT);
    struct repeating_timer timer;
    add_repeating_timer_ms(500, blink_callback, NULL, &timer);

    while(true){
        tight_loop_contents();
    }
    return 0;
}
