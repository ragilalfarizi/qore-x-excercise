#include "qore-x_bme280_screen.h"

static void file_system_list(lv_obj_t *screen);
static void event_handler(lv_event_t *e);

static lv_obj_t *list1;

lv_obj_t *createFileSystemScreen() {
  lv_obj_t *screen = lv_obj_create(NULL);

  lv_color_t dimGray = lv_color_hex(0x666666);

  lv_obj_set_style_bg_color(screen, dimGray, 0);

  file_system_list(screen);

  /* CREATE BOTTOM MENU */
  createBottomSwitch(screen);

  return screen;
}

static void event_handler(lv_event_t *e) {
  lv_event_code_t code = lv_event_get_code(e);
  lv_obj_t       *obj  = (lv_obj_t *)lv_event_get_target(e);
  if (code == LV_EVENT_CLICKED) {
    LV_UNUSED(obj);
    LV_LOG_USER("Clicked: %s", lv_list_get_button_text(list1, obj));
  }
}

static void close_msgbox_event_handler(lv_event_t *e) {
  lv_obj_t *msgbox = (lv_obj_t *)lv_event_get_target(e);
  lv_obj_del(msgbox);  // Close the popup when OK is clicked
}

static void open_file_event_handler(lv_event_t *e) {
  lv_obj_t   *btn       = (lv_obj_t *)lv_event_get_target(e);
  const char *file_name = lv_list_get_button_text(list1, btn);

  // Open the file and display its content
  char full_path[64];
  sprintf(full_path, "/%s", file_name);

  File file = SD.open(full_path);
  if (file) {
    Serial.printf("Opening file: %s\n", file_name);
    String fileContent = "";
    while (file.available()) {
      fileContent += (char)file.read();
    }
    file.close();

    // Convert file content to a C string for LVGL
    static char content[1024];
    strncpy(content, fileContent.c_str(), sizeof(content) - 1);
    content[sizeof(content) - 1] = '\0';

    // Create a message box with the file content
    static const char *btns[] = {"OK", NULL};
    lv_obj_t          *msgbox = lv_msgbox_create(
        lv_scr_act());  // Create message box in current active screen

    lv_obj_set_size(msgbox, lv_pct(100), lv_pct(100));
    lv_msgbox_add_text(msgbox, content);  // Set file content as text
    // lv_msgbox_add_footer_button(msgbox, btns);     // Add "OK" button
    lv_msgbox_add_close_button(msgbox);
    lv_obj_center(msgbox);  // Center the message box
    lv_obj_add_event_cb(msgbox, close_msgbox_event_handler,
                        LV_EVENT_VALUE_CHANGED, NULL);
  } else {
    Serial.printf("Failed to open file: %s\n", file_name);
  }
}

static void file_system_list(lv_obj_t *screen) {
  /*Create a list*/
  list1 = lv_list_create(screen);
  lv_obj_set_size(list1, 180, 220);
  // lv_obj_set_size(list1, 150, 150);
  lv_obj_center(list1);

  /*Add buttons to the list*/
  lv_obj_t *btn;

  lv_list_add_text(list1, "Read Files");
  File root = SD.open("/");
  File file = root.openNextFile();
  while (file) {
    if (!file.isDirectory()) {
      const char *file_name = file.name();
      lv_obj_t *file_btn = lv_list_add_button(list1, LV_SYMBOL_FILE, file_name);
      lv_obj_add_event_cb(file_btn, open_file_event_handler, LV_EVENT_CLICKED,
                          NULL);
    }
    file = root.openNextFile();
  }
  root.close();

  lv_list_add_text(list1, "Settings");
  btn = lv_list_add_button(list1, LV_SYMBOL_BLUETOOTH, "Bluetooth");
  lv_obj_add_event_cb(btn, event_handler, LV_EVENT_CLICKED, NULL);
  btn = lv_list_add_button(list1, LV_SYMBOL_GPS, "Navigation");
  lv_obj_add_event_cb(btn, event_handler, LV_EVENT_CLICKED, NULL);
  btn = lv_list_add_button(list1, LV_SYMBOL_USB, "USB");
  lv_obj_add_event_cb(btn, event_handler, LV_EVENT_CLICKED, NULL);
  btn = lv_list_add_button(list1, LV_SYMBOL_BATTERY_FULL, "Battery");
  lv_obj_add_event_cb(btn, event_handler, LV_EVENT_CLICKED, NULL);
}