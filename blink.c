#include "pico/stdlib.h"

#define LED_DELAY_MS 250

int main() {
    // Initialize the onboard LED pin
    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);

    while (true) {
        gpio_put(PICO_DEFAULT_LED_PIN, true);   // LED ON
        sleep_ms(LED_DELAY_MS);

        gpio_put(PICO_DEFAULT_LED_PIN, false);  // LED OFF
        sleep_ms(LED_DELAY_MS);
    }
}