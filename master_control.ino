#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>

// PIR Sensor Setup
const int pir_sensor = 2;
int pir_state = 0;

// Keypad Setup
const byte ROWS = 4; // four rows
const byte COLS = 4; // four columns
char hexaKeys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},A
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {11, 10, 9, 8}; // connect to the row pinouts of the keypad
byte colPins[COLS] = {7, 6, 5, 4}; // connect to the column pinouts of the keypad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

// LCD Setup
LiquidCrystal_I2C lcd(32, 16, 2);

// Servo Setup
Servo servo_motor;

// Temperature Sensor Setup
int celsius = 0;
int fahrenheit = 0;

// Ultrasonic Sensor Setup
int cm = 0;

long readUltrasonicDistance(int triggerPin, int echoPin) {
    pinMode(triggerPin, OUTPUT);  // Clear the trigger
    digitalWrite(triggerPin, LOW);
    delayMicroseconds(2);
    // Sets the trigger pin to HIGH state for 10 microseconds
    digitalWrite(triggerPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(triggerPin, LOW);
    pinMode(echoPin, INPUT);
    // Reads the echo pin, and returns the sound wave travel time in microseconds
    return pulseIn(echoPin, HIGH);
}

void setup() {
    Serial.begin(9600);

    pinMode(pir_sensor, INPUT);

    pinMode(A0, INPUT); // temperature sensor

    servo_motor.attach(12);
    servo_motor.write(92);

    lcd.init();
    lcd.backlight();
    lcd.setCursor(0, 0);
    lcd.print("Door Closed");
    lcd.setCursor(0, 1);
    lcd.print("Scanning....");
}

void loop() {
    while (1) {
        displayMessage("Door Closed", "Scanning....");
        delay(2000);

        pir_state = digitalRead(pir_sensor);

        if (pir_state == HIGH) {
            displayMessage("Person Detected", "");
            delay(2000);

            if (!inputAccessCode()) {
                continue;  // Incorrect access code, restart loop
            }

            measureTemperature();

            if (fahrenheit > 100) {
                displayMessage("Temp too high", "Door Locked");
                delay(5000);
                continue;
            } else {
                displayMessage("Temp Accepted", "Door Unlocked");
                servo_motor.write(2);
                delay(2000);

                while (1) {
                    displayMessage("Door Open", "");
                    delay(2000);

                    cm = 0.01723 * readUltrasonicDistance(3, 3);

                    if (cm > 200) {
                        displayMessage("Door Closing", "");
                        servo_motor.write(92);
                        delay(2000);
                        break;
                    }
                }
            }
        }
    }
}

bool inputAccessCode() {
    char enteredCode[5] = ""; // 4 digits + null terminator
    int codeIndex = 0;

    displayMessage("Enter Code:", enteredCode);

    while (1) {
        char key = customKeypad.getKey();

        if (key) {
            if (key == '#') {
                enteredCode[codeIndex] = '\0'; // Null terminate the string
                break; // Exit the loop on #
            } else if (codeIndex < 4) {
                enteredCode[codeIndex++] = key;
            }

            // Display the entered code on the LCD
            displayMessage("Enter Code:", enteredCode);
        }
    }

    return strcmp(enteredCode, "1234") == 0;
}

void measureTemperature() {
    displayMessage("Measuring Temp", "Place Hand");
    delay(2000);

    celsius = map(((analogRead(A0) - 20) * 3.04), 0, 1023, 35, 41);
    fahrenheit = (celsius * 9) / 5 + 32;

    displayMessage("Temp: ", "");
    lcd.print(fahrenheit);
    lcd.print("F");
    delay(2000);
}

void displayMessage(const char* line1, const char* line2) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(line1);
    lcd.setCursor(0, 1);
    lcd.print(line2);
}
