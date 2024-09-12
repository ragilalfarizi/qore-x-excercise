#pragma once

#include <Arduino.h>

class Vector3D {
 private:
  float x, y, z;
};

class IMUData {
 private:
  float    temperature;
  Vector3D accel, mag, gyro;
};

class BMEData {
 private:
  float temperature;
  float pressure;
  float altitude;
  float humidity;
};

class SensorData {
 private:
  BMEData bme;
  IMUData imu;

 public:
  BMEData& getBME() { return bme; } // Accessor method
  IMUData& getIMU() { return imu; }
};