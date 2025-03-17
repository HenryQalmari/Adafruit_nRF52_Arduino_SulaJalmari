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
** This program makes an LED blink on and off continuously.
**
** - The LED turns ON for 1 second.
** - Then, it turns OFF for 1 second.
** - This repeats forever.
*/


#define LED_PIN 0  // The pin where the LED is connected

// The setup function runs once when the board is powered on or reset.
void setup() {
  pinMode(LED_PIN, OUTPUT);  // Set the LED pin as an output (so we can turn it on/off)
}

// The loop function runs continuously after setup finishes.
void loop() {
  digitalWrite(LED_PIN, HIGH);  // Turn the LED ON (apply voltage)
  delay(1000);                  // Wait for 1 second (1000 milliseconds)

  digitalWrite(LED_PIN, LOW);   // Turn the LED OFF (remove voltage)
  delay(1000);                  // Wait for 1 second
}