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
** This program communicates with an ALS21C ambient light sensor using I2C.
** It reads ambient light levels and prints the values to the Serial Monitor.
*/


#include <Wire.h>

#define ALS21C_I2C_ADDRESS 0x38  // I2C address of the ALS21C sensor

// Register Addresses
#define SYS_CTRL        0x00  // System control register
#define ALS_GAIN        0x04  // Gain setting register
#define ALS_TIME        0x05  // Integration time register
#define DATA_STATUS     0x17  // Data status register
#define ALS_DATA_L      0x1E  // Ambient light data (low byte)
#define ALS_DATA_H      0x1F  // Ambient light data (high byte)

void setup() {
  Serial.begin(115200);  // Start serial communication
  Wire.begin();  // Initialize I2C communication

  // Reset sensor (optional but recommended)
  Wire.beginTransmission(ALS21C_I2C_ADDRESS);
  Wire.write(SYS_CTRL);
  Wire.write(0b00000001);  // Send reset command
  Wire.endTransmission();

  // Set gain for ambient light sensing
  Wire.beginTransmission(ALS21C_I2C_ADDRESS);
  Wire.write(ALS_GAIN); // Set gain value (adjustable for sensitivity)
                        // 0x01: x1 (Default)
                        // 0x02: x4
                        // 0x04: x16
                        // 0x08: x64
                        // 0x10: x256
  Wire.write(0x08);  
  Wire.endTransmission();
  
  delay(100);  // Allow sensor to stabilize after configuration
}

void loop() {
  uint16_t ambientLight = readAmbientLight();  // Get light level
  Serial.print("Ambient Light: ");
  Serial.println(ambientLight);  // Print light value to Serial Monitor
  delay(1000);  // Wait 1 second before next reading
}

// Function to read ambient light data from the sensor
uint16_t readAmbientLight() {
  uint16_t lightLevel = 0;

  // Request ambient light data (low byte first)
  Wire.beginTransmission(ALS21C_I2C_ADDRESS);
  Wire.write(ALS_DATA_L);
  Wire.endTransmission();
  delay(1);  // Short delay to allow sensor to respond

  // Read 2 bytes from the sensor (low byte + high byte)
  Wire.requestFrom(ALS21C_I2C_ADDRESS, 2);
  if (Wire.available() == 2) {
    uint8_t lsb = Wire.read();  // Read low byte
    uint8_t msb = Wire.read();  // Read high byte
    lightLevel = (msb << 8) | lsb;  // Combine bytes into a 16-bit value
  }

  return lightLevel;  // Return the ambient light level
}