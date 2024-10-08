#include "qore-x_bme280_screen.h"

static void lv_example_list_1(lv_obj_t *screen);
static void event_handler(lv_event_t *e);

static lv_obj_t *list1;

lv_obj_t *createFileSystemScreen() {
  lv_obj_t *screen = lv_obj_create(NULL);

  lv_color_t dimGray = lv_color_hex(0x666666);

  lv_obj_set_style_bg_color(screen, dimGray, 0);

  lv_example_list_1(screen);

  /* CREATE BOTTOM MENU */
  createBottomSwitch(screen);

  return screen;
}

static void event_handler(lv_event_t *e) {
  lv_event_code_t code = lv_event_get_code(e);
  lv_obj_t       *obj  = (lv_obj_t*)lv_event_get_target(e);
  if (code == LV_EVENT_CLICKED) {
    LV_UNUSED(obj);
    LV_LOG_USER("Clicked: %s", lv_list_get_button_text(list1, obj));
  }
}

static void lv_example_list_1(lv_obj_t *screen) {
  /*Create a list*/
  list1 = lv_list_create(screen);
  lv_obj_set_size(list1, 180, 220);
  // lv_obj_set_size(list1, 150, 150);
  lv_obj_center(list1);

  /*Add buttons to the list*/
  lv_obj_t *btn;
  lv_list_add_text(list1, "File");
  btn = lv_list_add_button(list1, LV_SYMBOL_FILE, "New");
  lv_obj_add_event_cb(btn, event_handler, LV_EVENT_CLICKED, NULL);
  btn = lv_list_add_button(list1, LV_SYMBOL_DIRECTORY, "Open");
  lv_obj_add_event_cb(btn, event_handler, LV_EVENT_CLICKED, NULL);
  btn = lv_list_add_button(list1, LV_SYMBOL_SAVE, "Save");
  lv_obj_add_event_cb(btn, event_handler, LV_EVENT_CLICKED, NULL);
  btn = lv_list_add_button(list1, LV_SYMBOL_CLOSE, "Delete");
  lv_obj_add_event_cb(btn, event_handler, LV_EVENT_CLICKED, NULL);
  btn = lv_list_add_button(list1, LV_SYMBOL_EDIT, "Edit");
  lv_obj_add_event_cb(btn, event_handler, LV_EVENT_CLICKED, NULL);

  lv_list_add_text(list1, "Connectivity");
  btn = lv_list_add_button(list1, LV_SYMBOL_BLUETOOTH, "Bluetooth");
  lv_obj_add_event_cb(btn, event_handler, LV_EVENT_CLICKED, NULL);
  btn = lv_list_add_button(list1, LV_SYMBOL_GPS, "Navigation");
  lv_obj_add_event_cb(btn, event_handler, LV_EVENT_CLICKED, NULL);
  btn = lv_list_add_button(list1, LV_SYMBOL_USB, "USB");
  lv_obj_add_event_cb(btn, event_handler, LV_EVENT_CLICKED, NULL);
  btn = lv_list_add_button(list1, LV_SYMBOL_BATTERY_FULL, "Battery");
  lv_obj_add_event_cb(btn, event_handler, LV_EVENT_CLICKED, NULL);

  lv_list_add_text(list1, "Exit");
  btn = lv_list_add_button(list1, LV_SYMBOL_OK, "Apply");
  lv_obj_add_event_cb(btn, event_handler, LV_EVENT_CLICKED, NULL);
  btn = lv_list_add_button(list1, LV_SYMBOL_CLOSE, "Close");
  lv_obj_add_event_cb(btn, event_handler, LV_EVENT_CLICKED, NULL);
}