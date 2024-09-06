#pragma once

#include <TFT_eSPI.h>
#include <esp_log.h>
#include <lvgl.h>

#include "FT6336U.h"

#define TFT_HOR_RES   240
#define TFT_VER_RES   320
#define TFT_ROTATION  LV_DISPLAY_ROTATION_0
#define DRAW_BUF_SIZE (TFT_HOR_RES * TFT_VER_RES / 10 * (LV_COLOR_DEPTH / 8))

#define I2C_SDA   21
#define I2C_SCL   22
#define RST_N_PIN -1
#define INT_N_PIN 4

/* GLOBAL VARIABLES */
extern FT6336U ft6336u;


enum ScreenID {
  StartUpMenu,
  BME280Menu,
  ICM20948Menu,
};

void setupScreens();

void qoreXLCDInit();
