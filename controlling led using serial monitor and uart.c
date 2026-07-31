#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "hardware/uart.h"

#define UART_ID uart0
#define BAUD_RATE 115200
#define TX_PIN 16
#define RX_PIN 17
#define LED_PIN 18

int main(){
    stdio_init_all();
    uart_init(UART_ID, BAUD_RATE);
    
    gpio_set_function(TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(RX_PIN, GPIO_FUNC_UART);

    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    gpio_put(LED_PIN, 0);


    while(1){
        char Rxbuffer[20];
        int index = 0;

        if(uart_is_readable(UART_ID)){
            while(1){
                char ch = uart_getc(UART_ID);
                printf("%c", ch); // Echo received character
                if(ch == '\r'){
                    continue; // Ignore carriage return
                }
                if(ch == '\n'){
                    Rxbuffer[index] = '\0';
                    if(strcmp(Rxbuffer, "led_on") == 0){
                        gpio_put(LED_PIN, 1);
                    }
                    else if(strcmp(Rxbuffer, "led_off") == 0){
                        gpio_put(LED_PIN, 0);
                    }   
                    break;
                }
                if(index < sizeof(Rxbuffer) - 1){
                    Rxbuffer[index++] = ch;
                }
            }
        }
    }
    return 0;

}
