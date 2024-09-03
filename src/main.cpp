#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>

#include "bme280_helper.h"
#include "icm20948_helper.h"

#define DEFAULT_DELAY 1000

/* OBJECT INIT */
Adafruit_BME280   bme;
Adafruit_ICM20948 icm;

/* GLOBAL VARIABLES INIT */
sensors_event_t accel;
sensors_event_t gyro;
sensors_event_t mag;
sensors_event_t temp;

void setup() {
  /* SERIAL INIT */
  Serial.begin(115200);
  while (!Serial);  // time to get serial running

  /* BME280 INIT */
  unsigned status;
  status = bme.begin(0x76);
  if (!status) {
    Serial.println(
        "Could not find a valid BME280 sensor, check wiring, address, sensor "
        "ID!");
  }

  /* ICM 20948 INIT */
  status = icm.begin_I2C(0x68);
  if (!status) {
    Serial.println("Failed to find ICM20948");
  }

  getAndPrintICMSpecs();

  Serial.print("\n===========================================\n");
}

void loop() {
  /* PRINT BME280 DATA */
  printBME280Values();
  delay(DEFAULT_DELAY);

  /* PRINT ICM20948 DATA */
  getAndPrintICMData(accel, gyro, mag, temp);
  delay(DEFAULT_DELAY);
}