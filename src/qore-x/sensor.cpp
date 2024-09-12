#include "sensor.h"

BME280::BME280() {
  Serial.println("Initializing BME280");

  bme.begin(BME280_ADDR);
}

void BME280::printBME280Data(const SensorData &data) const {
  Serial.println("==================");
  Serial.println("BME280 Sensor Data");
  Serial.println("==================");

  // Serial.println("Temperature = ");
  // Serial.print(data.bme.temperature);
}

float BME280::getTemperature() { return bme.readTemperature(); }
float BME280::getPressure() { return bme.readPressure() / 100.0f; }
float BME280::getAltitude() { return bme.readAltitude(SEALEVELPRESSURE_HPA); }
float BME280::getHumidity() { return bme.readHumidity(); }

ICM20949::ICM20949() {
  Serial.println("Initializing ICM20949");
}