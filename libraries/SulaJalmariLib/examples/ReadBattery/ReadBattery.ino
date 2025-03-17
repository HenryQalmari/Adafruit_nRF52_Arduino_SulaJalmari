/*
** LED_BUILTIN = 0 = LED 1
** 0 = LED 1
** 1 = LED 2
** 2 = LED 3
** 3 = LED 4
** 4 = LED 5
** 5 = LED 6
** 6 = LED 7
** 7 = LED 8
**
** 8 = NeoPixel EYE LEDs
**
** 9 = BUTTON 1
** 10 = BUTTON 2
**
** 11 = VIBRATION MOTOR
** 12 = BUZZER
** 13 = BATTERY VOLTAGE DIVIDER ENABLE
**
** A0 = 14 = BATTERY VOLTAGE DIVIDER
** A7 = 21 = IMU INTERRUPT
**
** 22 = IMU SDA
** 23 = IMU SCL
**
** This program reads an analog voltage from a sensor, converts it to a readable 
** voltage value, and uses it to control an LED's brightness. A lower voltage 
** dims the LED, while a higher voltage makes it brighter. The values are printed 
** to the Serial Monitor.
*/


#include <Wire.h> // Needed for Serial

const int sensor_pin = A0;  // Sensor input pin
const int sensor_ena = 13;  // Pin to enable/disable sensor
const int led_pin = 0;      // LED output pin

const float voltage_multiplier = (3600.0 / 4095.0);  // Converts raw sensor data to voltage (3.6V is the reference voltage for ADC)

// Expected voltage range from the sensor (in millivolts)
const int voltage_ranges[2] = {3700, 4200};

// Function to read sensor value multiple times and return an average
int read_sensor(int n = 10) {  
  digitalWrite(sensor_ena, LOW);  // Enable the sensor
  delay(10);  // Short delay for sensor stabilization

  int total = 0;
  for (int i = 0; i < n; i++) {
    total += analogRead(sensor_pin);  // Read sensor value
    delay(5);  // Short delay between readings for accuracy
  }

  digitalWrite(sensor_ena, HIGH);  // Disable the sensor to save power
  return total / n;  // Return the average reading
}

void setup() {
  Serial.begin(115200);  // Start serial communication

  pinMode(sensor_pin, INPUT);  // Set sensor pin as input
  analogReadResolution(12);  // Set resolution to 12 bits (0-4095)

  pinMode(sensor_ena, OUTPUT);  // Set sensor enable pin as output
  pinMode(led_pin, OUTPUT);  // Set LED pin as output
  digitalWrite(sensor_ena, HIGH);  // Keep sensor disabled when not in use
  digitalWrite(led_pin, HIGH);  // Initially turn LED on
}

void loop() {
  // Read sensor value, convert to voltage, and multiply by 2 (for proper scaling)
  float sensor_value = read_sensor() * voltage_multiplier * 2;
  
  // Print voltage value to Serial Monitor
  Serial.print("Value: ");
  Serial.print(sensor_value);
  Serial.println("V");

  // Convert voltage to a brightness level (0-255) for the LED
  int level = map(constrain(sensor_value, voltage_ranges[0], voltage_ranges[1]), 
                  voltage_ranges[0], voltage_ranges[1], 0, 255);
  
  analogWrite(led_pin, 255 - level);  // Adjust LED brightness (lower voltage = dimmer LED) (the LEDs are ACTIVE LOW)

  delay(1000);  // Wait 1 second before the next reading
}
