#include "speaker.h"

#include <unity.h>

#include "sdcard.h"

void setUp(void) { TEST_ASSERT_TRUE(i2sInit()); }

void tearDown(void) {}

// void test_i2s_init(void) { TEST_ASSERT_TRUE(i2sInit()); }

void test_open_fs_play_mp3(void) {
  TEST_ASSERT_TRUE(SD.begin(PIN_CS));

  playAudio("/bell.wav");

  delay(3000);
}

int runUnityTests(void) {
  UNITY_BEGIN();
  // RUN_TEST(test_i2s_init);
  RUN_TEST(test_open_fs_play_mp3);

  return UNITY_END();
}

void setup() {
  delay(2000);

  runUnityTests();
}

void loop() {}