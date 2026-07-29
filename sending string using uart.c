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

    // Set GPIO pins for UART
    gpio_set_function(TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(RX_PIN, GPIO_FUNC_UART);

    int count = 1;

    while (true)
    {
        char txBuffer[30];
        char rxBuffer[30];
        int index = 0;

        // Create the string to send
        sprintf(txBuffer, "Counter = %d\n", count);

        // Send the string
        uart_puts(UART_ID, txBuffer);

        // Receive characters one by one
        while (1)
        {
            char ch = uart_getc(UART_ID);

            rxBuffer[index++] = ch;

            // Stop when newline is received
            if (ch == '\n')
            {
                rxBuffer[index] = '\0';
                break;
            }
        }

        // Print the received string
        printf("Received: %s", rxBuffer);

        count++;

        sleep_ms(1000);
    }

    return 0;
}
