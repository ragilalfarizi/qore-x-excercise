#include "qore-x_bme280_screen.h"

/* Global variables for labels */
lv_obj_t *temperatureValue;
lv_obj_t *pressureValue;
lv_obj_t *altitudeValue;
lv_obj_t *humidityValue;

/* FUNCTION TO REFRESH THE LABEL VALUES */
void refresh_bme_data(lv_timer_t *timer) {
  // Buffers To Hold Text For Each Value
  char tempBuffer[16];
  char pressureBuffer[16];
  char altitudeBuffer[16];
  char humidityBuffer[16];

  // Convert float values to strings
  snprintf(tempBuffer, sizeof(tempBuffer), "%.2f", bmeData.temperature);
  snprintf(pressureBuffer, sizeof(pressureBuffer), "%.2f", bmeData.pressure);
  snprintf(altitudeBuffer, sizeof(altitudeBuffer), "%.2f", bmeData.altitude);
  snprintf(humidityBuffer, sizeof(humidityBuffer), "%.2f", bmeData.humidity);

  // Update label texts
  lv_label_set_text(temperatureValue, tempBuffer);
  lv_label_set_text(pressureValue, pressureBuffer);
  lv_label_set_text(altitudeValue, altitudeBuffer);
  lv_label_set_text(humidityValue, humidityBuffer);
}

lv_obj_t *createBME280Screen() {
  lv_obj_t *screen = lv_obj_create(NULL);

  LV_IMAGE_DECLARE(screen_bme);

  lv_obj_t *Img = lv_image_create(screen);
  lv_image_set_src(Img, &screen_bme);
  lv_obj_align(Img, LV_ALIGN_CENTER, 0, 0);

  /* ADD SENSOR TEXT AT CERTAIN POSITION */
  temperatureValue = lv_label_create(Img);
  pressureValue    = lv_label_create(Img);
  altitudeValue    = lv_label_create(Img);
  humidityValue    = lv_label_create(Img);

  lv_obj_set_pos(temperatureValue, 142, 100);
  lv_obj_set_pos(pressureValue, 142, 136);
  lv_obj_set_pos(altitudeValue, 142, 170);
  lv_obj_set_pos(humidityValue, 142, 204);

  /* CREATE BOTTOM MENU */
  createBottomSwitch(screen);

  /* START A TIMER TO REFRESH THE SENSOR DATA EVERY 2 SECONDS (2000 MS) */
  lv_timer_create(refresh_bme_data, 1000, NULL);
  return screen;
}