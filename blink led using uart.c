#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/uart.h"

#define UART_ID uart0
#define BAUD_RATE 115200

#define TX_PIN 16
#define RX_PIN 17
#define LED_PIN 18

int main()
{
    // Initialize UART
    stdio_init_all();
    uart_init(UART_ID, BAUD_RATE);

    gpio_set_function(TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(RX_PIN, GPIO_FUNC_UART);

    // Initialize LED
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    gpio_put(LED_PIN, 0);
    char value;
    sleep_ms(9000);
    printf("enter the value of A to turn on the LED: \n");
    scanf("%c", &value);
    // Send one character
    uart_putc(UART_ID, value);

    while (true)
    {
        
        if (uart_is_readable(UART_ID))
        {
            char ch = uart_getc(UART_ID);

            // If 'A' was received, turn LED ON
            if (ch == 'A')
            {
                sleep_ms(5000);
                gpio_put(LED_PIN, 1);
                printf("Received 'A', LED ON\n");
            }
        }

        tight_loop_contents();
    }

    return 0;
}
