#pragma once

#include <lvgl.h>
#include <TFT_eSPI.h>
#include <esp_log.h>

#define TFT_HOR_RES   240
#define TFT_VER_RES   320
#define TFT_ROTATION  LV_DISPLAY_ROTATION_0
#define DRAW_BUF_SIZE (TFT_HOR_RES * TFT_VER_RES / 10 * (LV_COLOR_DEPTH / 8))

// void  display_init();
void qoreXLCDInit();
