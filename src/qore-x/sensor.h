#pragma once

#include <Adafruit_BME280.h>
#include <string>
#include <Adafruit_Sensor.h>
#include "qore-x.h"

#define BME280_ADDR 0x76
#define SEALEVELPRESSURE_HPA (1013.25)

class Sensor {
 public:
  virtual float       readValue()     = 0;
  virtual std::string getName() const = 0;
};

class BME280 : public Sensor {
 public:
  BME280();
  void printBME280Data(const SensorData &data) const;
  float getTemperature();
  float getPressure();
  float getAltitude();
  float getHumidity();

 private:
  Adafruit_BME280 bme;
};

class ICM20949 : public Sensor {
 public:
  ICM20949();
  void printICM20949Data(const SensorData &data) const;
};