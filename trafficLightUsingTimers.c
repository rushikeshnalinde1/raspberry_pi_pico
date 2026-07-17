#include "pico/stdlib.h"
#include <stdio.h>
#define red 16
#define yellow 17
#define green 18
static int state = red;

bool traficLight(struct repeating_timer *t)
{
    static int count = 0;
    if (count < 5)
        state = red;
    else if (count < 7)
        state = yellow;
    else if (count < 12)
        state = green;
    else if (count < 14)
        state = yellow;
    else
        count = 0;

    switch (state)
    {
    case red:
        gpio_put(red, 1);
        gpio_put(yellow, 0);
        gpio_put(green, 0);
        break;
    case yellow:
        gpio_put(red, 0);
        gpio_put(yellow, 1);
        gpio_put(green, 0);
        break;
    case green:
        gpio_put(red, 0);
        gpio_put(yellow, 0);
        gpio_put(green, 1);
        break;
    default:
        gpio_put(red, 0);
        gpio_put(yellow, 0);
        gpio_put(green, 0);
        break;
    }
    count++;
    return true;
}

void main()
{
    stdio_init_all();
    gpio_init(red);
    gpio_init(yellow);
    gpio_init(green);

    gpio_set_dir(red, GPIO_OUT);
    gpio_set_dir(yellow, GPIO_OUT);
    gpio_set_dir(green, GPIO_OUT);

    struct repeating_timer timer;
    add_repeating_timer_ms(1000, traficLight, NULL, &timer);

    while (true)
    {
        tight_loop_contents();
    }
}

