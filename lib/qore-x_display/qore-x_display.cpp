#include "qore-x_display.h"

/* GLOBAL VARIABLES */
lv_display_t   *disp           = NULL;
lv_indev_t     *indev          = NULL;
lv_obj_t       *BME280Screen   = NULL;
lv_obj_t       *ICM20948Screen = NULL;
static uint32_t draw_buf[DRAW_BUF_SIZE / 4];

/* STATIC FUNCTION PROTOTYPE */
static void     displayInit();
static void     touchInit();
static uint32_t myTick(void);
static void     myTouchpadRead(lv_indev_t *indev, lv_indev_data_t *data);
static void     createStartUpScreen();

void qoreXLCDInit() {
  // Initialization of the display
  Serial.println("Initializing the display");
  displayInit();

  // Initialization of the touch input
  Serial.println("Initializing the touch driver");
  touchInit();
}

void setupScreens() {
  // BME280Screen   = createBME280Screen();
  // ICM20948Screen = createICM2094Screen();

  createStartUpScreen();

  delay(3000);

  // lv_screen_load(BME280Screen);
}

static void createStartUpScreen() {
  LV_IMAGE_DECLARE(screen_start_up);

  lv_obj_t *boot_screen = lv_image_create(lv_screen_active());
  lv_image_set_src(boot_screen, &screen_start_up);
  lv_obj_align(boot_screen, LV_ALIGN_CENTER, 0, 0);
}

void touchInit() {
  ft6336u.begin();

  Serial.print("FT6336U Firmware Version: ");
  Serial.println(ft6336u.read_firmware_id());
  Serial.print("FT6336U Device Mode: ");
  Serial.println(ft6336u.read_device_mode());

  // Integrate the touch with LVGL
  indev = lv_indev_create();
  lv_indev_set_type(indev, LV_INDEV_TYPE_POINTER);
  lv_indev_set_read_cb(indev, myTouchpadRead);
}

static void displayInit() {
  lv_tick_set_cb(myTick);

  disp =
      lv_tft_espi_create(TFT_HOR_RES, TFT_VER_RES, draw_buf, sizeof(draw_buf));
  lv_display_set_rotation(disp, TFT_ROTATION);
}

void myTouchpadRead(lv_indev_t *indev, lv_indev_data_t *data) {
  // Check if the touchpad is pressed
  if (ft6336u.read_touch1_event() == 2) {
    // Get the touch point coordinates
    int32_t x = (int32_t)ft6336u.read_touch1_x();
    int32_t y = (int32_t)ft6336u.read_touch1_y();

    // Feed the touch state and coordinates to LVGL
    data->state   = LV_INDEV_STATE_PRESSED;  // The screen is touched
    data->point.x = x;                       // Update the X coordinate
    data->point.y = y;                       // Update the Y coordinate
  } else {
    data->state = LV_INDEV_STATE_RELEASED;  // The screen is not touched
  }
}
/*use Arduinos millis() as tick source*/
static uint32_t myTick(void) { return millis(); }