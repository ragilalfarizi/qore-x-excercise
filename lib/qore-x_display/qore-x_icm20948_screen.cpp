#include "qore-x_bme280_screen.h"

lv_obj_t *createICM2094Screen() {
  lv_obj_t *screen = lv_obj_create(NULL);

  /* CREATE MAIN CONTENT */
  // TODO: break this down into pieces, not just image
  lv_obj_set_style_bg_color(screen, lv_palette_main(LV_PALETTE_YELLOW), 0);

  /* CREATE BOTTOM MENU */
  createBottomSwitch(screen);

  return screen;
}