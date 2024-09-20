#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>

#include "common.h"
#include "sensor.h"
// #include "qore-x_display.h"

#define DEFAULT_DELAY 1000

/* FORWARD DECLARATION OF FUNCTIONS */
// void lvglTask(void *pvParameter);
void acqusitionDataTask(void *pvParameter);

TaskHandle_t acquisitionDataHandler = NULL;

/* OBJECT INIT */

BME280   *bme;
ICM20949 *imu;
BMEData  bmeData;
IMUData  imuData;

/* GLOBAL VARIABLES INIT */
/* sensors_event_t accel;
sensors_event_t gyro;
sensors_event_t mag;
sensors_event_t temp;
uint32_t        draw_buf[DRAW_BUF_SIZE / 4];
TaskHandle_t    lvglTaskHandler = NULL;
TFT_eSPI        tft;
 */
void setup() {
  uint8_t status;

  /* SERIAL INIT */
  Serial.begin(115200);
  while (!Serial);  // time to get serial running

  /* DISPLAY INIT */
  // Serial.println("Initializing Qore-X LCD");
  // lv_init();  // Initialize LVGL
  // qoreXLCDInit();

  /* BME280 INIT */
  bme = new BME280();

  /* ICM 20948 INIT */
  imu = new ICM20949();
  
  // setupScreens();

  /* lv_obj_t *demoScreen = lv_obj_create(NULL);
  lv_scr_load(demoScreen); */

  Serial.print("\n===========================================\n");

  // xTaskCreatePinnedToCore(lvglTask, "LVGL Task", 4096, NULL, 5,
  //                         &lvglTaskHandler, 1);

  xTaskCreatePinnedToCore(acqusitionDataTask, "Acquisition Data Task", 2048,
                          NULL, 5, &acquisitionDataHandler, 1);
}

void loop() {
  /* PRINT BME280 DATA */
  bme->printBME280Data(bmeData);
  delay(DEFAULT_DELAY);

  /* PRINT ICM20948 DATA */
  imu->printICM20948Data();
  // delay(DEFAULT_DELAY);
}

void acqusitionDataTask(void *pvParameter) {
  while (1) {
    // BME280 Data Acquisition
    bmeData.temperature = bme->getTemperature();
    bmeData.pressure    = bme->getPressure();
    bmeData.altitude    = bme->getAltitude();
    bmeData.humidity    = bme->getHumidity();

    vTaskDelay(pdMS_TO_TICKS(1000));

    // ICM20948 Data Acquisition
    // vTaskDelay(pdMS_TO_TICKS(1000));
  }
}

// void lvglTask(void *pvParameter) {
//   while (1) {
//     lv_timer_handler();
//     delay(5);
//   }
// }