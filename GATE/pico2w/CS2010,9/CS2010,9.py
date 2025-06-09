from machine import Pin
import time

# Input pins with pull-down resistors
r_pin = Pin(14, Pin.IN, Pin.PULL_DOWN)
p_pin = Pin(15, Pin.IN, Pin.PULL_DOWN)
q_pin = Pin(16, Pin.IN, Pin.PULL_DOWN)

# Output pin for LED
f_pin = Pin(17, Pin.OUT)

while True:
    r = r_pin.value()
    p = p_pin.value()
    q = q_pin.value()

    # XOR operation
    f = r ^ p ^ q

    f_pin.value(f)

    time.sleep(0.1)
