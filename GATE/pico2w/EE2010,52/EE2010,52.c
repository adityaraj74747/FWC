#include "pico/stdlib.h"

#define PIN_X 14  // a_pin
#define PIN_Y 15  // b_pin
#define PIN_Z 16  // c_pin
#define PIN_F 17  // Output pin

int main() {
    stdio_init_all();

    // Configure inputs with pull-down resistors
    gpio_init(PIN_X);
    gpio_set_dir(PIN_X, GPIO_IN);
    gpio_pull_down(PIN_X);

    gpio_init(PIN_Y);
    gpio_set_dir(PIN_Y, GPIO_IN);
    gpio_pull_down(PIN_Y);

    gpio_init(PIN_Z);
    gpio_set_dir(PIN_Z, GPIO_IN);
    gpio_pull_down(PIN_Z);

    // Configure output pin
    gpio_init(PIN_F);
    gpio_set_dir(PIN_F, GPIO_OUT);

    while (1) {
        int x = gpio_get(PIN_X);
        int y = gpio_get(PIN_Y);
        int z = gpio_get(PIN_Z);

        int x_not = !x;
        int y_not = !y;

        int part1 = x_not & y_not;
        int part2 = y & z;
        int f = part1 | part2;

        gpio_put(PIN_F, f);

        sleep_ms(100);
    }

    return 0;
}

