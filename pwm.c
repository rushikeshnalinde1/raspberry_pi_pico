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
    pwm_set_gpio_level(LED, 100);

    // Start PWM
    pwm_set_enabled(slice, true);

    while (true)
    {
        tight_loop_contents();
    }
}
