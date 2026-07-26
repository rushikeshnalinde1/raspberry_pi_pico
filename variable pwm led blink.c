#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/adc.h"
#include "hardware/pwm.h"


int main()
{
    stdio_init_all();
    gpio_set_function(16, GPIO_FUNC_PWM);
    uint slice = pwm_gpio_to_slice_num(16);
    pwm_set_clkdiv(slice, 125.0f);
    pwm_set_wrap(slice, 999);
    pwm_set_enabled(slice, true);

    adc_init();
    adc_gpio_init(26);
    adc_select_input(0);

    while (true) {
        uint16_t value = adc_read();
        uint16_t brightness = value * 999 / 4095;
        pwm_set_gpio_level(16, brightness);
        printf("brightness = %d\n", brightness);
        sleep_ms(500);
    }
}
