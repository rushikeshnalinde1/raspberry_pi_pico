#include "pico\stdlib.h"
#include <stdio.h>
#define start 16
#define stop 17

bool clock(struct repeating_timer *t){
    //pass
    static  int second = 0;
    static int min = 0;
    static int hour = 0;
    printf("%02d : %02d : %02d  \n", hour, min, second);
    second += 1;
    if(second >= 60){
        min += 1;
        second = 0;
    }
    if(min>=60){
        hour += 1;
        min = 0;
    }
    return true;
}

int main(){
    stdio_init_all();
    sleep_ms(2000);
    gpio_init(start);
    gpio_init(stop);

    gpio_set_dir(start, GPIO_IN);
    gpio_set_dir(stop, GPIO_IN);

    gpio_pull_down(start);
    gpio_pull_down(stop);

    struct repeating_timer timer;
    int start_count = 0;
    int stop_count = 0;

    while(true){

        if(gpio_get(start) && (start_count==0)){
            if(add_repeating_timer_ms(1000, clock, NULL, &timer)){
                start_count = 1;
                stop_count = 0;
            }
            while (gpio_get(start)) {
                tight_loop_contents();
            }
            sleep_ms(20);
        }
        if(gpio_get(stop) && (stop_count==0)){
            if(cancel_repeating_timer(&timer)){
                start_count = 0;
                stop_count = 1;
            }
            while (gpio_get(stop)) {
                tight_loop_contents();
            }
            sleep_ms(20);
        }

    }
    return 0;
}
