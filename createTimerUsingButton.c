#include "pico/stdlib.h"
#include <stdio.h>

#define LED 16
#define BUTTON 18

bool blink(struct repeating_timer *t)
{
    static bool state = false;
    state = !state;
    gpio_put(LED, state);
    return true;
}

int main()
{
    stdio_init_all();

    gpio_init(LED);
    gpio_set_dir(LED, GPIO_OUT);

    gpio_init(BUTTON);
    gpio_set_dir(BUTTON, GPIO_IN);
    gpio_pull_down(BUTTON);

    struct repeating_timer timer;
    bool timer_started = false;

    while (true)
    {
        if (gpio_get(BUTTON) && !timer_started)
        {
            add_repeating_timer_ms(500, blink, NULL, &timer);
            timer_started = true;
            printf("Timer Started\n");
        }

        sleep_ms(20);   // Simple debounce
    }
}
