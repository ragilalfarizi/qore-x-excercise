#include "qore-x_bme280_screen.h"

lv_obj_t *createBME280Screen() {
  lv_obj_t *screen = lv_obj_create(NULL);

  /* CREATE MAIN CONTENT */
  // TODO: break this down into pieces, not just image
  // lv_obj_set_style_bg_color(screen, lv_palette_main(LV_PALETTE_INDIGO), 0);

  LV_IMAGE_DECLARE(screen_bme);

  lv_obj_t *Img = lv_image_create(screen);
  lv_image_set_src(Img, &screen_bme);
  lv_obj_align(Img, LV_ALIGN_CENTER, 0, 0);

  /* ADD SENSOR TEXT AT CERTAIN POSITION */
  lv_obj_t *temperatureValue = lv_label_create(Img);
  lv_obj_t *pressureValue = lv_label_create(Img);
  lv_obj_t *altitudeValue= lv_label_create(Img);
  lv_obj_t *humidityValue= lv_label_create(Img);
  
  // lv_label_set_text_fmt(&temperatureValue, "%.2f", bme.temperature);
  lv_label_set_text_fmt(temperatureValue, "23.91");
  lv_obj_set_pos(temperatureValue, 154, 108);
  
  lv_label_set_text_fmt(pressureValue, "24.91");
  lv_obj_set_pos(pressureValue, 154, 144);

  lv_label_set_text_fmt(altitudeValue, "25.91");
  lv_obj_set_pos(altitudeValue, 154, 178);

  lv_label_set_text_fmt(humidityValue, "26.91");
  lv_obj_set_pos(humidityValue, 154, 212);

  /* CREATE BOTTOM MENU */
  createBottomSwitch(screen);

  return screen;
}