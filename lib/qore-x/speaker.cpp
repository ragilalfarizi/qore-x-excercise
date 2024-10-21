#include "speaker.h"

bool i2sInit() {
  i2s_config_t i2s_config = {
      .mode                 = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_TX),
      .sample_rate          = 44100,  // Default sample rate
      .bits_per_sample      = I2S_BITS_PER_SAMPLE_16BIT,
      .channel_format       = I2S_CHANNEL_FMT_RIGHT_LEFT,
      .communication_format = I2S_COMM_FORMAT_I2S,
      .intr_alloc_flags     = 0,     // Default interrupt priority
      .dma_buf_count        = 8,     // Number of DMA buffers
      .dma_buf_len          = 1024,  // DMA buffer size
      .use_apll             = false};

  i2s_pin_config_t pin_config = {.bck_io_num   = I2S_BCK_PIN,
                                 .ws_io_num    = I2S_LRCK_PIN,
                                 .data_out_num = I2S_DOUT_PIN,
                                 .data_in_num  = I2S_PIN_NO_CHANGE};

  if (i2s_driver_install(I2S_NUM_0, &i2s_config, 0, NULL) != ESP_OK) {
    Serial.println("I2S Driver Install is error");
    return false;
  }

  if (i2s_set_pin(I2S_NUM_0, &pin_config) != ESP_OK) {
    Serial.println("I2S Set Pin is error");
    return false;
  }

  if (i2s_zero_dma_buffer(I2S_NUM_0) != ESP_OK) {
    Serial.println("I2S zero dma buffer is error");
    return false;
  }

  return true;
}

void playAudio(const char *fileName) {
  File audioFile = SD.open(fileName);
  if (!audioFile) {
    Serial.println("Failed to open audio file");
    return;
  }

  byte   buffer[512];
  size_t bytesRead;

  while ((bytesRead = audioFile.read(buffer, sizeof(buffer))) > 0) {
    size_t bytesWritten = 0;
    while (bytesWritten < bytesRead) {
      i2s_write(I2S_NUM_0, buffer + bytesWritten, bytesRead - bytesWritten,
                &bytesWritten, portMAX_DELAY);
    }
  }

  audioFile.close();
}