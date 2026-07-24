//Button-controlled brightness
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"

#define LED 16
#define button 17

int main()
{
    stdio_init_all();
    gpio_init(button);
    gpio_set_dir(button, GPIO_IN);
    gpio_pull_down(button);
    gpio_set_function(LED, GPIO_FUNC_PWM);
    uint slice = pwm_gpio_to_slice_num(LED);
    pwm_set_clkdiv(slice, 125.0f);
    pwm_set_wrap(slice, 999);
    pwm_set_enabled(slice, true);
    
    int i = 0;


    while (true)
    {   
        if(gpio_get(button) == 1){
            i++;
            printf("%d\n", i);
            while(gpio_get(button)==1){
                sleep_ms(10);
            }
        }

        if(i==0){
            pwm_set_gpio_level(LED, 0);
        }
        else if(i==1){
            pwm_set_gpio_level(LED, 200);
        }
        else if(i==2){
            pwm_set_gpio_level(LED, 400);
        }
        else if(i==3){
            pwm_set_gpio_level(LED, 600);
        }
        else if(i==4){
            pwm_set_gpio_level(LED, 800);
        }
        else if(i==5){
            pwm_set_gpio_level(LED, 999);
        }
        else{
            i=0;
        }

        tight_loop_contents();
    }
}
