#include "pico/stdlib.h"
#include <stdio.h>

int main()
{
    stdio_init_all();

    // Give the USB serial time to connect
    sleep_ms(2000);

    printf("Starting timer...\n");

    // Record the start time
    absolute_time_t start = get_absolute_time();

    // Code whose execution time we want to measure
    sleep_ms(500);

    // Record the end time
    absolute_time_t end = get_absolute_time();

    // Calculate elapsed time in microseconds
    int64_t elapsed_us = absolute_time_diff_us(start, end);

    printf("Elapsed time = %lld us\n", elapsed_us);
    printf("Elapsed time = %.3f ms\n", elapsed_us / 1000.0);

    while (true)
    {
        tight_loop_contents();
    }

    return 0;
}
