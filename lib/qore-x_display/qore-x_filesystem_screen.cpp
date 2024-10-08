#include "qore-x_bme280_screen.h"

lv_obj_t *createFileSystemScreen() {
  lv_obj_t *screen = lv_obj_create(NULL);

  /* CREATE BOTTOM MENU */
  createBottomSwitch(screen);

  return screen;
}