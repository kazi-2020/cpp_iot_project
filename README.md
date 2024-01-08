# Smart Door Lock System

This Arduino code implements a smart door lock system using various sensors and components. The system includes a PIR (Passive Infrared) sensor for motion detection, a keypad for access code entry, an LCD display for status messages, a servo motor to control the door lock, a temperature sensor, and an ultrasonic distance sensor.

## Components

- **U1:** PCF8574-based 32x2 LCD (I2C)
- **U2:** Arduino Uno R3
- **PIRentry_sensor:** PIR Sensor
- **Utemp_sensor:** Temperature Sensor (TMP36)
- **KEYPAD1:** 4x4 Keypad
- **SERVO1:** Positional Micro Servo
- **PING1:** Ultrasonic Distance Sensor

## Connections

- **PIR Sensor (PIRentry_sensor):** Connected to digital pin 2
- **Temperature Sensor (Utemp_sensor):** Connected to analog pin A0
- **Keypad (KEYPAD1):** Connected to digital pins 4-11
- **Servo Motor (SERVO1):** Connected to digital pin 12
- **Ultrasonic Sensor (PING1):** Trigger and echo pins connected to pin 3

## Libraries Used

- **Servo.h:** Used for controlling the servo motor.
- **Wire.h:** Used for I2C communication with the LCD.
- **LiquidCrystal_I2C.h:** Used for interfacing with the I2C LCD.
- **Keypad.h:** Used for handling input from the keypad.

## Functionality

1. The system continuously monitors the PIR sensor to detect motion.
2. When motion is detected, it displays "Person Detected" on the LCD and prompts the user to enter an access code using the keypad.
3. If the correct access code (default: "1234") is entered, the system measures the temperature using the temperature sensor.
4. If the temperature is below a specified threshold, the door is unlocked, and the servo motor opens the door.
5. The ultrasonic sensor monitors the distance; when it exceeds a threshold, the door is closed, and the process repeats.

## Component Quantities

- U1: 1 (PCF8574-based, 32 LCD 16 x 2 - I2C)
- U2: 1 (Arduino Uno R3)
- PIRentry_sensor: 1 (PIR Sensor)
- Utemp_sensor: 1 (Temperature Sensor [TMP36])
- KEYPAD1: 1 (Keypad 4x4)
- SERVO1: 1 (Positional Micro Servo)
- PING1: 1 (Ultrasonic Distance Sensor)

## Usage

1. Connect the components according to the specified pin connections.
2. Upload the provided Arduino code to the Arduino Uno.
3. Power on the system.
4. The LCD will display the status messages, and the door will open when a person is detected with the correct access code and an acceptable temperature.
5. Adjust the access code and temperature thresholds as needed in the code.

This project was created and run on TINKERCAD website
