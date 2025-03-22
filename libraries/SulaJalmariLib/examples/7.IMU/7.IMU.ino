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
** This program communicates with the ICM-20602 IMU sensor using I2C.
** It reads acceleration, gyroscope, and temperature data, then prints 
** the values to the Serial Monitor.
*/


#include <Wire.h>

#define ICM20602_ADDR  0x69  // I2C address of the ICM-20602 sensor

// Register Addresses
#define ACCEL_XOUT_H  0x3B  // Accelerometer X-axis high byte
#define TEMP_OUT_H    0x41  // Temperature sensor high byte
#define GYRO_XOUT_H   0x43  // Gyroscope X-axis high byte

void setup() {
    Serial.begin(115200);  // Start serial communication
    Wire.begin();  // Initialize I2C communication
    
    // Wake up sensor by disabling sleep mode
    writeRegister(0x6B, 0x00);
}

void loop() {
    int16_t accelX, accelY, accelZ, gyroX, gyroY, gyroZ, temp;

    // Read acceleration data (X, Y, Z)
    accelX = read16Bit(ACCEL_XOUT_H);
    accelY = read16Bit(ACCEL_XOUT_H + 2);
    accelZ = read16Bit(ACCEL_XOUT_H + 4);

    // Read temperature data
    temp = read16Bit(TEMP_OUT_H);

    // Read gyroscope data (X, Y, Z)
    gyroX = read16Bit(GYRO_XOUT_H);
    gyroY = read16Bit(GYRO_XOUT_H + 2);
    gyroZ = read16Bit(GYRO_XOUT_H + 4);

    // Convert raw temperature data to Celsius
    float tempC = (temp / 326.8) + 25.0;

    // Print accelerometer data in milli-g (mg)
    Serial.print("Accel (mg): X="); Serial.print(accelX / 16.384);
    Serial.print(" Y="); Serial.print(accelY / 16.384);
    Serial.print(" Z="); Serial.println(accelZ / 16.384);

    // Print gyroscope data in degrees per second (dps)
    Serial.print("Gyro (dps): X="); Serial.print(gyroX / 131.0);
    Serial.print(" Y="); Serial.print(gyroY / 131.0);
    Serial.print(" Z="); Serial.println(gyroZ / 131.0);

    // Print temperature in Celsius
    Serial.print("Temperature: "); Serial.print(tempC); Serial.println(" °C");

    delay(500);  // Wait 500ms before the next reading
}

// Function to read 16-bit data from two consecutive registers
int16_t read16Bit(uint8_t reg) {
    Wire.beginTransmission(ICM20602_ADDR);
    Wire.write(reg);  // Request register
    Wire.endTransmission();
    
    Wire.requestFrom(ICM20602_ADDR, 2);  // Request 2 bytes
    if (Wire.available() == 2) {
        int16_t high = Wire.read();  // Read high byte
        int16_t low = Wire.read();   // Read low byte
        return (high << 8) | low;  // Combine bytes into a 16-bit value
    }
    return 0;  // Return 0 if no data is available
}

// Function to write a value to a register
void writeRegister(uint8_t reg, uint8_t value) {
    Wire.beginTransmission(ICM20602_ADDR);
    Wire.write(reg);  // Select register
    Wire.write(value);  // Write value
    Wire.endTransmission();
}