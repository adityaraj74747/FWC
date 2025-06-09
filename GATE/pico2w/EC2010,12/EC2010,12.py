from machine import Pin
import time

# Input pins with pull-down resistors
a_pin = Pin(14, Pin.IN, Pin.PULL_DOWN)
b_pin = Pin(15, Pin.IN, Pin.PULL_DOWN)
c_pin = Pin(16, Pin.IN, Pin.PULL_DOWN)

# Output pin for LED
f_pin = Pin(17, Pin.OUT)

def xor(x, y):
    return x ^ y

def xnor(x, y):
    return 1 - (x ^ y)

def three_input_xnor(x, y, z):
    return 1 - (x ^ y ^ z)

# Track previous input states to detect changes
prev_a = 0
prev_b = 0
prev_c = 0

while True:
    a = a_pin.value()
    b = b_pin.value()
    c = c_pin.value()

    X = xor(a, b)
    Y = xnor(a, b)
    f = three_input_xnor(X, Y, c)

    f_pin.value(f)

    # Print only when button is pressed (value=1) AND it was previously 0
    if a == 1 and prev_a == 0:
        print(f"a={a}, b={b}, c={c} f={f}")
    if b == 1 and prev_b == 0:
        print(f"a={a}, b={b}, c={c} f={f}")
    if c == 1 and prev_c == 0:
        print(f"a={a}, b={b}, c={c} f={f}")

    prev_a, prev_b, prev_c = a, b, c

    time.sleep(0.1)
