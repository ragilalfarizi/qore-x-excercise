#pragma once

struct Vector3D {
  float x, y, z;
};

struct BMEData {
  float temperature;
  float pressure;
  float altitude;
  float humidity;
};

struct IMUData {
  struct {
    float x;
    float y;
    float z;
  } acceleration, gyro, magnetic;

  float temperature;
};
