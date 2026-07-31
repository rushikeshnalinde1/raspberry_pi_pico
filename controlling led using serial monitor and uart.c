#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/uart.h"
#include <string.h>

#define UART_ID uart0
#define BAUD_RATE 115200
#define TX_PIN 16
#define RX_PIN 17
#define LED_PIN 18 

int main()
{
    stdio_init_all();
    uart_init(UART_ID, BAUD_RATE);
    
    gpio_set_function(TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(RX_PIN, GPIO_FUNC_UART);

    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    gpio_put(LED_PIN, 0);

    char buffer[50];
    int index = 0;

    char Rxbuffer[20];
    int Rxindex = 0;

    while (1)
    {
        

        int ch = getchar_timeout_us(0);

        if (ch != PICO_ERROR_TIMEOUT)
        {
            if (ch == '\r' || ch == '\n')
            {
                buffer[index] = '\0';     // End the string

                printf("Message sent: %s\n", buffer);
                uart_puts(UART_ID, buffer);
                uart_puts(UART_ID, "\r\n");
                index = 0;
                sleep_ms(50);                // Ready for next message
            }
            else if (index < sizeof(buffer) - 1)
            {
                buffer[index++] = ch;
            }

        }

        if(uart_is_readable(UART_ID)){
            char received = uart_getc(UART_ID);
            if(received == '\r' || received == '\n') {
                Rxbuffer[Rxindex] = '\0'; // End the string
                printf("Received message: %s\n", Rxbuffer);

                if(strcmp(Rxbuffer,"led_on") == 0){
                    gpio_put(LED_PIN, 1); // Turn on LED
                }
                else if(strcmp(Rxbuffer,"led_off") == 0){
                    gpio_put(LED_PIN, 0); // Turn off LED
                }
                Rxindex = 0; // Ready for next message
                sleep_ms(50); // Optional delay for processing
            } else
            if(Rxindex < sizeof(Rxbuffer) - 1) {
                Rxbuffer[Rxindex++] = received;
            }
        }
    }
}
