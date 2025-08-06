# Fingerprint Attendance System

A WiFi-enabled fingerprint attendance system using ESP32 and R307 sensor. Attendance is logged in real time to Google Sheets via a web endpoint.

## Features

- Enroll users with fingerprint, name, and ID
- Log attendance with timestamp
- WPA2-Enterprise WiFi support
- EEPROM-based persistent storage
- Buzzer feedback on success/failure

## Hardware

- ESP32 Dev Board  
- R307 Fingerprint Sensor (UART)  
- Buzzer (3.3V)  
- Jumper Wires  
- USB Cable / Power Supply  

## Setup

1. Upload the firmware using Arduino IDE  
2. Update WiFi and endpoint URL in code  
3. Open Serial Monitor (115200 baud)  

## Serial Commands

- `E` → Enroll new user  
- `P` → Print all users  
- `C` → Clear stored data  

## Example Sheet Layout

Name        | Comet ID     | Time                |
------------|--------------|---------------------|
Aditya Raj  | COMETFWC015  | 2025-07-30 16:05:23 |  

