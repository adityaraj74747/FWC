from machine import Pin
import time

# Input pins with pull-down resistors
a_pin = Pin(14, Pin.IN, Pin.PULL_DOWN)  # x
b_pin = Pin(15, Pin.IN, Pin.PULL_DOWN)  # y
c_pin = Pin(16, Pin.IN, Pin.PULL_DOWN)  # z

# Output pin for LED
f_pin = Pin(17, Pin.OUT)

while True:
    x = a_pin.value()
    y = b_pin.value()
    z = c_pin.value()

    x_not = 1 - x
    y_not = 1 - y

    # f = x'y' + y z
    part1 = x_not & y_not
    part2 = y & z
    f = part1 | part2

    f_pin.value(f)

    time.sleep(0.1)
