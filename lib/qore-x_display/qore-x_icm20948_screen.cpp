#include "qore-x_bme280_screen.h"

/* Global variables for labels */
lv_obj_t *tempValue;
lv_obj_t *AccelValueX;
lv_obj_t *AccelValueY;
lv_obj_t *AccelValueZ;
lv_obj_t *MagValueX;
lv_obj_t *MagValueY;
lv_obj_t *MagValueZ;
lv_obj_t *GyroValueX;
lv_obj_t *GyroValueY;
lv_obj_t *GyroValueZ;

/* FUNCTION TO REFRESH THE LABEL VALUES */
void refresh_imu_data(lv_timer_t *timer) {
  // Buffers To Hold Text For Each Value
  char tempBuffer[16];
  char AccelBufferX[16];
  char AccelBufferY[16];
  char AccelBufferZ[16];
  char MagBufferX[16];
  char MagBufferY[16];
  char MagBufferZ[16];
  char GyroBufferX[16];
  char GyroBufferY[16];
  char GyroBufferZ[16];

  // Convert float values to strings
  snprintf(tempBuffer, sizeof(tempBuffer), "%.2f", imuData.temperature);
  snprintf(AccelBufferX, sizeof(AccelBufferX), "%.2f", imuData.acceleration.x);
  snprintf(AccelBufferY, sizeof(AccelBufferY), "%.2f", imuData.acceleration.y);
  snprintf(AccelBufferZ, sizeof(AccelBufferZ), "%.2f", imuData.acceleration.z);
  snprintf(MagBufferX, sizeof(MagBufferX), "%.2f", imuData.magnetic.x);
  snprintf(MagBufferY, sizeof(MagBufferY), "%.2f", imuData.magnetic.y);
  snprintf(MagBufferZ, sizeof(MagBufferZ), "%.2f", imuData.magnetic.z);
  snprintf(GyroBufferX, sizeof(GyroBufferX), "%.2f", imuData.gyro.x);
  snprintf(GyroBufferY, sizeof(GyroBufferY), "%.2f", imuData.gyro.y);
  snprintf(GyroBufferZ, sizeof(GyroBufferZ), "%.2f", imuData.gyro.z);

  // Update label texts
  lv_label_set_text(tempValue, tempBuffer);
  lv_label_set_text(AccelValueX, AccelBufferX);
  lv_label_set_text(AccelValueY, AccelBufferY);
  lv_label_set_text(AccelValueZ, AccelBufferZ);
  lv_label_set_text(MagValueX, MagBufferX);
  lv_label_set_text(MagValueY, MagBufferY);
  lv_label_set_text(MagValueZ, MagBufferZ);
  lv_label_set_text(GyroValueX, GyroBufferX);
  lv_label_set_text(GyroValueY, GyroBufferY);
  lv_label_set_text(GyroValueZ, GyroBufferZ);
}

lv_obj_t *createICM2094Screen() {
  lv_obj_t *screen = lv_obj_create(NULL);

  /* CREATE MAIN CONTENT */
  LV_IMAGE_DECLARE(screen_icm);

  lv_obj_t *Img = lv_image_create(screen);
  lv_image_set_src(Img, &screen_icm);
  lv_obj_align(Img, LV_ALIGN_CENTER, 0, 0);

  /* ADD SENSOR TEXT AT CERTAIN POSITION */
  tempValue   = lv_label_create(Img);
  AccelValueX = lv_label_create(Img);
  AccelValueY = lv_label_create(Img);
  AccelValueZ = lv_label_create(Img);
  MagValueX   = lv_label_create(Img);
  MagValueY   = lv_label_create(Img);
  MagValueZ   = lv_label_create(Img);
  GyroValueX  = lv_label_create(Img);
  GyroValueY  = lv_label_create(Img);
  GyroValueZ  = lv_label_create(Img);

  lv_obj_set_pos(tempValue, 150, 61);
  lv_obj_set_pos(AccelValueX, 38, 129);
  lv_obj_set_pos(AccelValueY, 110, 129);
  lv_obj_set_pos(AccelValueZ, 182, 129);
  lv_obj_set_pos(MagValueX, 38, 190);
  lv_obj_set_pos(MagValueY, 110, 190);
  lv_obj_set_pos(MagValueZ, 182, 190);
  lv_obj_set_pos(GyroValueX, 38, 251);
  lv_obj_set_pos(GyroValueY, 110, 251);
  lv_obj_set_pos(GyroValueZ, 182, 251);

  /* CREATE BOTTOM MENU */
  createBottomSwitch(screen);

  /* START A TIMER TO REFRESH THE SENSOR DATA EVERY 2 SECONDS (2000 MS) */
  lv_timer_create(refresh_imu_data, 1000, NULL);

  return screen;
}