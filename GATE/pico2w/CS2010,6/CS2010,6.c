#include "pico/stdlib.h"

#define PIN_P 15
#define PIN_Q 16
#define PIN_R 14
#define PIN_F 17

int main() {
    // Initialize stdio
    stdio_init_all();

    // Set up input pins with pull-downs
    gpio_init(PIN_P);
    gpio_set_dir(PIN_P, GPIO_IN);
    gpio_pull_down(PIN_P);

    gpio_init(PIN_Q);
    gpio_set_dir(PIN_Q, GPIO_IN);
    gpio_pull_down(PIN_Q);

    gpio_init(PIN_R);
    gpio_set_dir(PIN_R, GPIO_IN);
    gpio_pull_down(PIN_R);

    // Set up output pin
    gpio_init(PIN_F);
    gpio_set_dir(PIN_F, GPIO_OUT);

    while (1) {
        bool p = gpio_get(PIN_P);
        bool q = gpio_get(PIN_Q);
        bool r = gpio_get(PIN_R);

        // f = (p AND q) OR (q AND NOT r) OR (p AND NOT r)
        bool f = (p && q) || (q && !r) || (p && !r);

        gpio_put(PIN_F, f);

        sleep_ms(100);
    }

    return 0;
}

