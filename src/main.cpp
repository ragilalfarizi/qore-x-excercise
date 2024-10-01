#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>

#include "common.h"
#include "qore-x_display.h"
#include "sensor.h"

#define DEFAULT_DELAY 1000

/* FORWARD DECLARATION OF FUNCTIONS */
void lvglTask(void *pvParameter);
void acqusitionDataTask(void *pvParameter);

/* OBJECT INIT */
BME280   *bme;
ICM20948 *imu;
BMEData   bmeData;
IMUData   imuData;

/* GLOBAL VARIABLES INIT */
// TODO: Review these Global Variables
uint32_t     draw_buf[DRAW_BUF_SIZE / 4];
TFT_eSPI     tft;
FT6336U      ft6336u(I2C_SDA, I2C_SCL, RST_N_PIN, INT_N_PIN);
TaskHandle_t lvglTaskHandler = NULL;
TaskHandle_t acquisitionDataHandler = NULL;

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
  bme = new BME280();

  /* ICM 20948 INIT */
  imu = new ICM20948();

  /* DRAW SCREENS */
  setupScreens();

  Serial.print("\n===========================================\n");

  xTaskCreatePinnedToCore(lvglTask, "LVGL Task", 4096, NULL, 5,
                          &lvglTaskHandler, 1);

  xTaskCreatePinnedToCore(acqusitionDataTask, "Acquisition Data Task", 2048,
                          NULL, 5, &acquisitionDataHandler, 1);
}

void loop() {
  /* PRINT BME280 DATA */
  bme->printBME280Data(bmeData);
  delay(DEFAULT_DELAY);

  Serial.println();

  /* PRINT ICM20948 DATA */
  imu->printICM20948Data(imuData);
  // imu->getSensorData(imuData);
  delay(DEFAULT_DELAY);

  Serial.println();
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
    imu->getSensorData(imuData);
    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}

void lvglTask(void *pvParameter) {
  while (1) {
    lv_timer_handler();
    vTaskDelay(pdMS_TO_TICKS(5));
  }
}