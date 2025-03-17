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
** This program controls two NeoPixel LEDs and adjusts their brightness 
** based on ambient light levels measured by an ALS21C light sensor.
**
** - The LEDs transition smoothly through different colors.
** - The brightness of the LEDs is automatically adjusted depending on the light level.
** - The ambient light is read from the ALS21C sensor using the I2C protocol.
*/

#include <Adafruit_NeoPixel.h>  // Library for controlling NeoPixel LEDs
#include <Wire.h>               // Library for I2C communication

// ALS21C Light Sensor I2C Address
#define ALS21C_I2C_ADDRESS 0x38  

// Light Sensor Limits
#define LIGHT_MIN       0     // Minimum light level
#define LIGHT_BRIGHT    500   // Light level where brightness adjustment is maxed
#define LIGHT_MAX       65535 // Maximum possible sensor value (not used here)

// ALS21C Sensor Register Addresses
#define SYS_CTRL        0x00  // System control register
#define ALS_GAIN        0x04  // Gain control register
#define ALS_TIME        0x05  // Integration time register (not used here)
#define DATA_STATUS     0x17  // Data status register (not used here)
#define ALS_DATA_L      0x1E  // Low byte of light sensor data
#define ALS_DATA_H      0x1F  // High byte of light sensor data

// NeoPixel LED Settings
#define LED_PIN         8     // Digital pin for NeoPixel control
#define NUMPIXELS       2     // Number of LEDs in the strip
#define BRIGHTNESS      0.1   // Default brightness factor (scaled dynamically)

// Initialize the NeoPixel object
Adafruit_NeoPixel pixels(NUMPIXELS, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  pixels.begin(); // Initialize NeoPixel strip
  pixels.clear(); // Turn off all LEDs initially

  Wire.begin(); // Initialize I2C communication

  // Reset the ALS21C sensor (optional, ensures fresh startup)
  Wire.beginTransmission(ALS21C_I2C_ADDRESS);
  Wire.write(SYS_CTRL);
  Wire.write(0b00000001);  // Reset command
  Wire.endTransmission();

  // Set light sensor gain to a specific level (higher gain = more sensitivity)
  Wire.beginTransmission(ALS21C_I2C_ADDRESS);
  Wire.write(ALS_GAIN); // Set gain value (adjustable for sensitivity)
                        // 0x01: x1 (Default)
                        // 0x02: x4
                        // 0x04: x16
                        // 0x08: x64
                        // 0x10: x256
  Wire.write(0x04);
  Wire.endTransmission();
  
  delay(100); // Small delay to allow sensor to stabilize
}

void loop() {
  // Cycle through different color transitions
  for (int i = 0; i < 256; i++) {
    float brightness = get_brightness(); // Adjust brightness based on light level
    pixels.setPixelColor(0, pixels.Color(i * brightness, 0, (255 - i) * brightness));
    pixels.setPixelColor(1, pixels.Color(i * brightness, 0, (255 - i) * brightness));
    pixels.show(); // Update the LEDs
    delay(10);
  }

  for (int i = 0; i < 256; i++) {
    float brightness = get_brightness();
    pixels.setPixelColor(0, pixels.Color((255 - i) * brightness, i * brightness, 0));
    pixels.setPixelColor(1, pixels.Color((255 - i) * brightness, i * brightness, 0));
    pixels.show();
    delay(10);
  }

  for (int i = 0; i < 256; i++) {
    float brightness = get_brightness();
    pixels.setPixelColor(0, pixels.Color(0, (255 - i) * brightness, i * brightness));
    pixels.setPixelColor(1, pixels.Color(0, (255 - i) * brightness, i * brightness));
    pixels.show();
    delay(10);
  }
}

/*
  Reads the ambient light level and returns a brightness factor between 0.05 and 1.0
  - If it's dark, the brightness is at a minimum.
  - If it's bright, the LEDs will be at full brightness.
*/
float get_brightness() {
  uint16_t ambient_light = constrain(readAmbientLight(), LIGHT_MIN, LIGHT_BRIGHT);
  uint16_t light_mapped = map(ambient_light, LIGHT_MIN, LIGHT_BRIGHT, 5, 100); // Scale light to 5-100
  return light_mapped / 100.0; // Convert to a 0.05 - 1.0 scale
}

/*
  Reads the ambient light level from the ALS21C sensor over I2C.
  - The sensor returns a 16-bit value (0 - 65535) representing brightness.
*/
uint16_t readAmbientLight() {
  uint16_t lightLevel = 0;

  // Request the low byte of the light data
  Wire.beginTransmission(ALS21C_I2C_ADDRESS);
  Wire.write(ALS_DATA_L);  // Select the LSB register
  Wire.endTransmission();

  // Request 2 bytes from the sensor (LSB + MSB)
  Wire.requestFrom(ALS21C_I2C_ADDRESS, 2);
  if (Wire.available() == 2) { // Ensure 2 bytes are received
    uint8_t lsb = Wire.read();  // Read lower 8 bits
    uint8_t msb = Wire.read();  // Read upper 8 bits
    lightLevel = (msb << 8) | lsb; // Combine MSB and LSB into a 16-bit value
  }

  return lightLevel; // Return the ambient light level
}