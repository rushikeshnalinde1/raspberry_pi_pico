
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"

#define LED 16
#define LED2 17
#define LED3 20

int main()
{
    stdio_init_all();
    gpio_set_function(LED, GPIO_FUNC_PWM);
    gpio_set_function(LED2, GPIO_FUNC_PWM);
    gpio_set_function(LED3, GPIO_FUNC_PWM);

    uint slice = pwm_gpio_to_slice_num(LED);
    uint slice2 = pwm_gpio_to_slice_num(LED2);
    uint slice3 = pwm_gpio_to_slice_num(LED3);
    
    pwm_set_clkdiv(slice, 125.0f);
    pwm_set_clkdiv(slice2, 125.0f);
    pwm_set_clkdiv(slice3, 125.0f);

    pwm_set_wrap(slice, 999);
    pwm_set_wrap(slice2, 999);
    pwm_set_wrap(slice3, 999);

    pwm_set_enabled(slice, true);
    pwm_set_enabled(slice2, true);
    pwm_set_enabled(slice3, true);
    int i=0;
    int j=0;
    int k=0;

    while (true)
    {   
        pwm_set_gpio_level(LED, i);
        pwm_set_gpio_level(LED2, j);
        pwm_set_gpio_level(LED3, k);
        i = i+4;
        j = j+2;
        k = k+3;

        if(i>999)
            i=0;
        if(j>999)
            j=0;
        if(k>999)
            k=0;
        sleep_ms(10);
        tight_loop_contents();
    }
}
