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
** This program gradually increases and decreases the brightness of an LED
** using Pulse Width Modulation (PWM). The LED fades in and out smoothly.
**
** - The LED slowly brightens from off (0) to full brightness (255).
** - Then, it slowly dims back down to off (0).
** - This cycle repeats continuously.
*/

#define LED_PIN 0  // The pin connected to the LED

// The setup function runs once when the board is powered on or reset.
void setup() {
  pinMode(LED_PIN, OUTPUT);  // Set the LED pin as an output (so it can send power to the LED)
}

// The loop function runs continuously after setup finishes.
void loop() {
  // Gradually increase brightness from 0 (off) to 255 (full brightness)
  for (int i = 0; i < 256; i++) {
    analogWrite(LED_PIN, i);  // Set LED brightness
    delay(30);  // Wait 30 milliseconds before changing brightness again
  }

  // Gradually decrease brightness from 255 (full brightness) to 0 (off)
  for (int i = 255; i >= 0; i--) {
    analogWrite(LED_PIN, i);  // Set LED brightness
    delay(30);  // Wait 30 milliseconds before changing brightness again
  }
}