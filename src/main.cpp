#include <Adafruit_BME280.h>
#include <Adafruit_Sensor.h>
#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>

#include "bme280_helper.h"

#define DEFAULT_DELAY 1000

/* OBJECT INIT */
Adafruit_BME280 bme;

/* GLOBAL VARIABLES INIT */
BME280Data      bmeData;

void setup() {
  /* SERIAL INIT */
  Serial.begin(115200);
  while (!Serial);  // time to get serial running
  Serial.println(F("BME280 test"));

  /* BME280 INIT */
  unsigned status;
  status = bme.begin(0x76);
  if (!status) {
    Serial.println(
        "Could not find a valid BME280 sensor, check wiring, address, sensor "
        "ID!");
  }
}

void loop() {
  /* PRINT BME280 DATA */
  printBME280Values();
  delay(DEFAULT_DELAY);
}