#include "sensor.h"

/***********************************************************
 * BME280
 **********************************************************/
BME280::BME280() {
  Serial.println("Initializing BME280");

  if (!(bme.begin(BME280_ADDR))) {
    Serial.println(" BME Initialization is failed");
  }
}

void BME280::printBME280Data() const {
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

/***********************************************************
 * ICM20949
 **********************************************************/

ICM20949::ICM20949() {
  Serial.println("Initializing ICM20949");

  icm.begin_I2C(ICM20948_ADDR);

  ICM20949::getAndPrintICMSpecs();
}

void ICM20949::getAndPrintICMSpecs() {
  Serial.println();

  /* ACCELERATION RANGE */

  // icm.setAccelRange(ICM20948_ACCEL_RANGE_16_G);
  Serial.print("Accelerometer range set to: ");
  switch (icm.getAccelRange()) {
    case ICM20948_ACCEL_RANGE_2_G:
      Serial.println("+-2G");
      break;
    case ICM20948_ACCEL_RANGE_4_G:
      Serial.println("+-4G");
      break;
    case ICM20948_ACCEL_RANGE_8_G:
      Serial.println("+-8G");
      break;
    case ICM20948_ACCEL_RANGE_16_G:
      Serial.println("+-16G");
      break;
  }

  /* GYRO RANGE */

  // icm.setGyroRange(ICM20948_GYRO_RANGE_2000_DPS);
  Serial.print("Gyro range set to: ");
  switch (icm.getGyroRange()) {
    case ICM20948_GYRO_RANGE_250_DPS:
      Serial.println("250 degrees/s");
      break;
    case ICM20948_GYRO_RANGE_500_DPS:
      Serial.println("500 degrees/s");
      break;
    case ICM20948_GYRO_RANGE_1000_DPS:
      Serial.println("1000 degrees/s");
      break;
    case ICM20948_GYRO_RANGE_2000_DPS:
      Serial.println("2000 degrees/s");
      break;
  }

  /* ACCELERATION RATE DIVISOR */

  //  icm.setAccelRateDivisor(4095);
  uint16_t accel_divisor = icm.getAccelRateDivisor();
  float    accel_rate    = 1125 / (1.0 + accel_divisor);

  Serial.print("Accelerometer data rate divisor set to: ");
  Serial.println(accel_divisor);
  Serial.print("Accelerometer data rate (Hz) is approximately: ");
  Serial.println(accel_rate);

  /* GYRO RATE DIVISOR */

  //  icm.setGyroRateDivisor(255);
  uint8_t gyro_divisor = icm.getGyroRateDivisor();
  float   gyro_rate    = 1100 / (1.0 + gyro_divisor);

  Serial.print("Gyro data rate divisor set to: ");
  Serial.println(gyro_divisor);
  Serial.print("Gyro data rate (Hz) is approximately: ");
  Serial.println(gyro_rate);

  /* MAGNETOMETER DATA RATE */

  // icm.setMagDataRate(AK09916_MAG_DATARATE_10_HZ);
  Serial.print("Magnetometer data rate set to: ");
  switch (icm.getMagDataRate()) {
    case AK09916_MAG_DATARATE_SHUTDOWN:
      Serial.println("Shutdown");
      break;
    case AK09916_MAG_DATARATE_SINGLE:
      Serial.println("Single/One shot");
      break;
    case AK09916_MAG_DATARATE_10_HZ:
      Serial.println("10 Hz");
      break;
    case AK09916_MAG_DATARATE_20_HZ:
      Serial.println("20 Hz");
      break;
    case AK09916_MAG_DATARATE_50_HZ:
      Serial.println("50 Hz");
      break;
    case AK09916_MAG_DATARATE_100_HZ:
      Serial.println("100 Hz");
      break;
  }
  Serial.println();
}

void ICM20949::printICM20948Data() const {
  Serial.println("==================");
  Serial.println("ICM20948 Sensor Data");
  Serial.println("==================");
}