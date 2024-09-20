#pragma once

#include <Adafruit_BME280.h>
#include <Adafruit_ICM20948.h>
#include <Adafruit_Sensor.h>
#include <common.h>

#include <string>

#define BME280_ADDR          0x76
#define ICM20948_ADDR        0x68
#define SEALEVELPRESSURE_HPA (1013.25)

class BME280 {
 public:
  BME280();
  void  printBME280Data(const BMEData &data) const;
  float getTemperature();
  float getPressure();
  float getAltitude();
  float getHumidity();

 private:
  Adafruit_BME280 bme;
};

class ICM20949 {
 public:
  ICM20949();
  void printICM20948Data() const;
  void getAndPrintICMSpecs();

 private:
  Adafruit_ICM20948 icm;
};