#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"

#define I2C_PORT i2c0

#define SDA_PIN 4
#define SCL_PIN 5

void i2c_scan(void)
{
    printf("I2C scan:\n");

    for (int addr = 1; addr < 127; addr++)
    {
        uint8_t data = 0;

        int result = i2c_read_blocking(
            I2C_PORT,
            addr,
            &data,
            1,
            false
        );

        if (result >= 0)
        {
            printf("Device found at 0x%02X\n", addr);
        }
    }
}

int main()
{
    stdio_init_all();

    i2c_init(I2C_PORT, 100 * 1000);

    gpio_set_function(SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(SCL_PIN, GPIO_FUNC_I2C);

    gpio_pull_up(SDA_PIN);
    gpio_pull_up(SCL_PIN);

    sleep_ms(1000);

    i2c_scan();

    while (true)
    {
        sleep_ms(1000);
    }
}
