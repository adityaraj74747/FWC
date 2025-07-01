#include "pico/stdlib.h"
#include <stdio.h>

#define PIN_A 14
#define PIN_B 15
#define PIN_C 16
#define PIN_D 18
#define PIN_F 17

int mux_4to1(int a, int b, int c, int d) {
    int i0 = c;
    int i1 = d;
    int i2 = !c;
    int i3 = (!c) & (!d);

    if (a == 0 && b == 0) return i0;
    else if (a == 0 && b == 1) return i1;
    else if (a == 1 && b == 0) return i2;
    else return i3;
}

int main() {
    stdio_init_all();

    gpio_init(PIN_A);
    gpio_set_dir(PIN_A, GPIO_IN);
    gpio_pull_down(PIN_A);

    gpio_init(PIN_B);
    gpio_set_dir(PIN_B, GPIO_IN);
    gpio_pull_down(PIN_B);

    gpio_init(PIN_C);
    gpio_set_dir(PIN_C, GPIO_IN);
    gpio_pull_down(PIN_C);

    gpio_init(PIN_D);
    gpio_set_dir(PIN_D, GPIO_IN);
    gpio_pull_down(PIN_D);

    gpio_init(PIN_F);
    gpio_set_dir(PIN_F, GPIO_OUT);

    int prev_a = 0, prev_b = 0, prev_c = 0, prev_d = 0;

    while (1) {
        int a = gpio_get(PIN_A);
        int b = gpio_get(PIN_B);
        int c = gpio_get(PIN_C);
        int d = gpio_get(PIN_D);

        int f = mux_4to1(a, b, c, d);

        gpio_put(PIN_F, f);

        // Rising edge detection
        if (a == 1 && prev_a == 0) {
            printf("a=%d, b=%d, c=%d, d=%d, f=%d\n", a, b, c, d, f);
        }
        if (b == 1 && prev_b == 0) {
            printf("a=%d, b=%d, c=%d, d=%d, f=%d\n", a, b, c, d, f);
        }
        if (c == 1 && prev_c == 0) {
            printf("a=%d, b=%d, c=%d, d=%d, f=%d\n", a, b, c, d, f);
        }
        if (d == 1 && prev_d == 0) {
            printf("a=%d, b=%d, c=%d, d=%d, f=%d\n", a, b, c, d, f);
        }

        prev_a = a;
        prev_b = b;
        prev_c = c;
        prev_d = d;

        sleep_ms(100);
    }

    return 0;
}

