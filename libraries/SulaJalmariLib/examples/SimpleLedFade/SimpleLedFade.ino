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

#define LED_PIN D0         // the PWM pin the LED is attached to

// the setup routine runs once when you press reset:
void setup() {
  // declare LED_PIN to be an output:
  pinMode(LED_PIN, OUTPUT);
}

// the loop routine runs over and over again forever:
void loop() {

  // Loop the number(i) from 0 to 255. (i++ increments the number after every loop)
  for (int i = 0; i < 256; i++) {
    analogWrite(LED_PIN, i);
    delay(30);
  }

  // Loop the number(i) from 255 to 0.
  for (int i = 255; i >= 0; i--) {
    analogWrite(LED_PIN, i);
    delay(30);
  }
}