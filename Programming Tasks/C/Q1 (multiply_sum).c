#include <stdio.h>

void f(int a, int b) {
    int s = a + b;  // sum
    int m = a * b;  // multiplication
    printf("Sum: %d\n", s);
    printf("Mul: %d\n", m);
}

int main() {
    f(4, 5);
    return 0;
}
