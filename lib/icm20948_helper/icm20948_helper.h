#pragma once

#include <Adafruit_ICM20948.h>
#include <Arduino.h>

extern HardwareSerial    Serial;
extern Adafruit_ICM20948 icm;

void getAndPrintICMSpecs();

void getAndPrintICMData(sensors_event_t& accel, sensors_event_t& gyro,
                        sensors_event_t& temp, sensors_event_t& mag);