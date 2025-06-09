from machine import Pin
import time

# Input pins with pull-down resistors
p_pin = Pin(15, Pin.IN, Pin.PULL_DOWN)
q_pin = Pin(16, Pin.IN, Pin.PULL_DOWN)
r_pin = Pin(14, Pin.IN, Pin.PULL_DOWN)

# Output pin
f_pin = Pin(17, Pin.OUT)

while True:
    p = p_pin.value()
    q = q_pin.value()
    r = r_pin.value()

    # Logic: f = pq + q r' + p r'
    f = (p and q) or (q and not r) or (p and not r)

    f_pin.value(f)

    time.sleep(0.1)
