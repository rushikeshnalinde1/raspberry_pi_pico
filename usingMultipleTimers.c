#include "pico/stdlib.h"
#include <stdio.h>
#define led1 16
#define led2 17

bool blink1(struct repeating_timer *t)
{
    static bool ledState = false;
    gpio_put(led1, ledState);
    ledState = !ledState;
    return true;
}

bool blink2(struct repeating_timer *t)
{
    static bool ledState = false;
    gpio_put(led2, ledState);
    ledState = !ledState;
    return true;
}

int main()
{
    gpio_init(led1);
    gpio_init(led2);

    gpio_set_dir(led1, GPIO_OUT);
    gpio_set_dir(led2, GPIO_OUT);

    struct repeating_timer timer1;
    struct repeating_timer timer2;

    add_repeating_timer_ms(200, blink1, NULL, &timer1);
    add_repeating_timer_ms(500, blink2, NULL, &timer2);

    while (true)
    {
        tight_loop_contents();
    }
    return 0;
}
