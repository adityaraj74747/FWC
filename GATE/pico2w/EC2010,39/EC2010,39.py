from machine import Pin
import time

# Existing input pins with pull-down resistors
a_pin = Pin(14, Pin.IN, Pin.PULL_DOWN)
b_pin = Pin(15, Pin.IN, Pin.PULL_DOWN)
c_pin = Pin(16, Pin.IN, Pin.PULL_DOWN)
d_pin = Pin(18, Pin.IN, Pin.PULL_DOWN)

# Output pin for LED
f_pin = Pin(17, Pin.OUT)

def mux_4to1(a, b, c, d):
    i0 = c
    i1 = d
    i2 = 1 - c
    i3 = (1 - c) & (1 - d)

    if a == 0 and b == 0:
        return i0
    elif a == 0 and b == 1:
        return i1
    elif a == 1 and b == 0:
        return i2
    else:
        return i3

# Track previous input states to detect changes for printing
prev_a, prev_b, prev_c, prev_d = 0, 0, 0, 0

while True:
    a = a_pin.value()
    b = b_pin.value()
    c = c_pin.value()
    d = d_pin.value()

    f = mux_4to1(a, b, c, d)

    f_pin.value(f)

    # Print only when any button is pressed (rising edge)
    if a == 1 and prev_a == 0:
        print(f"a={a}, b={b}, c={c}, d={d} f={f}")
    if b == 1 and prev_b == 0:
        print(f"a={a}, b={b}, c={c}, d={d} f={f}")
    if c == 1 and prev_c == 0:
        print(f"a={a}, b={b}, c={c}, d={d} f={f}")
    if d == 1 and prev_d == 0:
        print(f"a={a}, b={b}, c={c}, d={d} f={f}")

    prev_a, prev_b, prev_c, prev_d = a, b, c, d

    time.sleep(0.1)
