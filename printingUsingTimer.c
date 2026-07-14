#include "pico/stdlib.h"
#include <stdio.h>

bool print(struct repeating_timer *t)
{
    static int count = 1;
    printf("hello %d\n", count);
    count++;
    return true;
}

int main()
{
    stdio_init_all();
    sleep_ms(2000);
    struct repeating_timer timer;
    add_repeating_timer_ms(1000, print, NULL, &timer);
    while (true)
    {
        tight_loop_contents();
    }
}
