#include "pico/stdlib.h"
#include "hardware/pwm.h"

#define LED 16

int main()
{
    // Set GPIO16 to PWM mode
    gpio_set_function(LED, GPIO_FUNC_PWM);

    // Find the PWM slice for GPIO16
    uint slice = pwm_gpio_to_slice_num(LED);

    // System Clock = 125 MHz
    // Divide by 125 -> Timer Clock = 1 MHz
    pwm_set_clkdiv(slice, 125.0f);

    // Counter counts from 0 to 999
    // PWM Frequency = 1 MHz / 1000 = 1 kHz
    pwm_set_wrap(slice, 999);

    // Duty Cycle = 50%
    // HIGH for 500 counts

    // Start PWM
    pwm_set_enabled(slice, true);
    int direction = 1;
    int i = 0;

    while (true)
    {
    
        if(direction == 1){
            pwm_set_gpio_level(LED, i);
            i++;
            sleep_ms(10);
            if(i >= 999){
                direction = 0;
            }
        }
        else{
            pwm_set_gpio_level(LED, i);
            i--;
            sleep_ms(10);
            if(i<=0){
                direction = 1;
            }
        }
        tight_loop_contents();
    }
}
