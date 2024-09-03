#pragma once

#include <Adafruit_BME280.h>
#include <Adafruit_Sensor.h>
#include <Arduino.h>

#define SEALEVELPRESSURE_HPA (1013.25)

extern HardwareSerial  Serial;
extern Adafruit_BME280 bme;  // I2C

struct BME280Data {
  float temperature;
  float pressure;
  float altitude;
  float humidity;
};

void printBME280Values();