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
** This program controls two NeoPixel LEDs using the Adafruit NeoPixel library.
** The LEDs smoothly transition through different colors in a loop.
*/


#include <Adafruit_NeoPixel.h>  // Include the library needed for NeoPixel control

#define PIN        8   // The digital pin that controls the NeoPixel LEDs
#define NUMPIXELS  2   // The number of NeoPixel LEDs in the strip
#define BRIGHTNESS 0.1 // Brightness factor (reduces LED intensity)

// Create a NeoPixel object to control the LED strip
// The parameters are: number of LEDs, control pin, and color format
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  pixels.begin(); // Initialize the NeoPixel library
  pixels.clear(); // Ensure all LEDs start in an OFF state
}

void loop() {
  // First transition: Gradually change color from Red to Blue
  for (int i = 0; i < 256; i++) {  
    // Set the first LED (Red decreases, Blue increases)
    pixels.setPixelColor(0, pixels.Color(i * BRIGHTNESS, 0, (255 - i) * BRIGHTNESS));
    // Set the second LED (Same effect for uniform color transition)
    pixels.setPixelColor(1, pixels.Color(i * BRIGHTNESS, 0, (255 - i) * BRIGHTNESS));
    
    pixels.show();  // Update the LED colors to apply the changes
    delay(5);  // Small delay to make the transition smooth
  }

  // Second transition: Gradually change color from Blue to Green
  for (int i = 0; i < 256; i++) {
    // Set the first LED (Blue decreases, Green increases)
    pixels.setPixelColor(0, pixels.Color((255 - i) * BRIGHTNESS, i * BRIGHTNESS, 0));
    // Set the second LED (Same effect)
    pixels.setPixelColor(1, pixels.Color((255 - i) * BRIGHTNESS, i * BRIGHTNESS, 0));

    pixels.show();  // Apply changes to the LEDs
    delay(5);
  }

  // Third transition: Gradually change color from Green to Red
  for (int i = 0; i < 256; i++) {
    // Set the first LED (Green decreases, Red increases)
    pixels.setPixelColor(0, pixels.Color(0, (255 - i) * BRIGHTNESS, i * BRIGHTNESS));
    // Set the second LED (Same effect)
    pixels.setPixelColor(1, pixels.Color(0, (255 - i) * BRIGHTNESS, i * BRIGHTNESS));

    pixels.show();  // Apply changes to the LEDs
    delay(5);
  }
}
