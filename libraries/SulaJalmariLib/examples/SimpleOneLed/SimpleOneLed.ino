/*
** LED_BUILTIN = D0 = LED 1
** D0 = LED 1
** D1 = LED 2
** D2 = LED 3
** D3 = LED 4
** D4 = LED 5
** D5 = LED 6
** D6 = LED 7
** D7 = LED 8
**
** D8 = NeoPixel EYE LEDs
**
** D9 = BUTTON 1
** D10 = BUTTON 2
**
** D11 = VIBRATION MOTOR
** D12 = BUZZER
** D13 = BATTERY VOLTAGE DIVIDER ENABLE
**
** A0 = D14 = BATTERY VOLTAGE DIVIDER
** A7 = D21 = IMU INTERRUPT
**
** D22 = IMU SDA
** D23 = IMU SCL
*/


#define LED_PIN D0

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_PIN as an output.
  pinMode(LED_PIN, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(LED_PIN, HIGH);      // turn the LED on (HIGH is the voltage level)
  delay(1000);                      // wait for a second
  digitalWrite(LED_PIN, LOW);       // turn the LED off by making the voltage LOW
  delay(1000);                      // wait for a second
}