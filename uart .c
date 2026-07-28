#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/uart.h"

#define UART_ID uart0
#define BAUD_RATE 115200

#define TX_PIN 16
#define RX_PIN 17

int main()
{
    stdio_init_all();

    // Initialize UART
    uart_init(UART_ID, BAUD_RATE);

    // Set GPIO0 and GPIO1 as UART pins
    gpio_set_function(TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(RX_PIN, GPIO_FUNC_UART);

    while (true)
    {
        // Send one character
        uart_putc(UART_ID, 'A');

        // Read the same character back
        char ch = uart_getc(UART_ID);

        // Print to USB Serial Monitor
        printf("Received: %c\n", ch);

        sleep_ms(1000);
    }

    return 0;
}
