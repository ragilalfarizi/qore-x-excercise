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
  Vector3D acceleration, altitude, humidity;
  float    temperature;
};
