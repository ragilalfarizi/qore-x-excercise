#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>

#include "FT6336U.h"
#include "bme280_helper.h"
#include "icm20948_helper.h"
#include "qore-x_display.h"

#define DEFAULT_DELAY 1000

/* FORWARD DECLARATION OF FUNCTIONS */
void lvglTask(void *pvParameter);

/* OBJECT INIT */
Adafruit_BME280   bme;
Adafruit_ICM20948 icm;
FT6336U           ft6336u(I2C_SDA, I2C_SCL, RST_N_PIN, INT_N_PIN);
static void       btn_event_cb(lv_event_t *e);

/* GLOBAL VARIABLES INIT */
sensors_event_t accel;
sensors_event_t gyro;
sensors_event_t mag;
sensors_event_t temp;
uint32_t        draw_buf[DRAW_BUF_SIZE / 4];
TaskHandle_t    lvglTaskHandler = NULL;
TFT_eSPI        tft;

static void helloWorldFromLVGL();

void setup() {
  uint8_t status;

  /* SERIAL INIT */
  Serial.begin(115200);
  while (!Serial);  // time to get serial running

  /* DISPLAY INIT */
  Serial.println("Initializing Qore-X LCD");
  lv_init();  // Initialize LVGL
  qoreXLCDInit();

  /* BME280 INIT */
  Serial.println("Initializing BME280");
  status = bme.begin(0x76);
  if (!status) {
    Serial.println(
        "Could not find a valid BME280 sensor, check wiring, address, sensor "
        "ID!");
  }

  /* ICM 20948 INIT */
  Serial.println("Initializing ICM20948");
  status = icm.begin_I2C(0x68);
  if (!status) {
    Serial.println("Failed to find ICM20948");
  }

  getAndPrintICMSpecs();

  Serial.println("Creating demo screen");
  helloWorldFromLVGL();

  Serial.print("\n===========================================\n");

  xTaskCreatePinnedToCore(lvglTask, "LVGL Task", 4096, NULL, 5,
                          &lvglTaskHandler, 1);
}

void loop() {
  /* PRINT BME280 DATA */
  // printBME280Values();
  // delay(DEFAULT_DELAY);

  /* PRINT ICM20948 DATA */
  // getAndPrintICMData(accel, gyro, mag, temp);
  // delay(DEFAULT_DELAY);
}

void lvglTask(void *pvParameter) {
  while (1) {
    lv_timer_handler();
    delay(5);
  }
}

static void helloWorldFromLVGL() {
  /*Change the active screen's background color*/
  lv_obj_set_style_bg_color(lv_screen_active(), lv_color_hex(0x003a57),
                            LV_PART_MAIN);

  /*Create a white label, set its text and align it to the center*/
  lv_obj_t *label = lv_label_create(lv_screen_active());
  lv_label_set_text(label, "Hello world");
  lv_obj_set_style_text_color(lv_screen_active(), lv_color_hex(0xffffff),
                              LV_PART_MAIN);
  lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);

  // create button demo
  lv_obj_t *btn =
      lv_button_create(lv_screen_active()); /*Add a button the current screen*/
  lv_obj_set_size(btn, 120, 50);            /*Set its size*/
  lv_obj_align(btn, LV_ALIGN_BOTTOM_MID, 0, 0);
  lv_obj_add_event_cb(btn, btn_event_cb, LV_EVENT_PRESSED,
                      NULL); /*Assign a callback to the button*/

  lv_obj_t *label2 = lv_label_create(btn); /*Add a label to the button*/
  lv_label_set_text(label2, "Press Me!");  /*Set the labels text*/
  lv_obj_center(label2);
}

static void btn_event_cb(lv_event_t *e) {
  Serial.println("Clicked");
}