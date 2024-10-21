#include <Arduino.h>
#include <driver/i2s.h>

#include "sdcard.h"

#define I2S_BCK_PIN  17
#define I2S_LRCK_PIN 16
#define I2S_DOUT_PIN 26

bool i2sInit();
void playAudio(const char *fileName);