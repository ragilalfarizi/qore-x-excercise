#include "sdcard.h"

#include <unity.h>

#define FILE_PATH "/data.txt"

void setUp(void) {
  Serial.begin(115200);
  SD.begin(PIN_CS);
}

void tearDown(void) {}

void test_sdcard_init(void) {
  Serial.println("Halo halo bandung");
  TEST_ASSERT_TRUE(SD.begin(PIN_CS));
}

void test_card_type(void) { TEST_ASSERT_NOT_EQUAL(CARD_NONE, SD.cardType()); }

void test_write_to_sd(void) {
  File file = SD.open(FILE_PATH, FILE_WRITE);
  TEST_ASSERT_TRUE(file);  // Ensure file opened successfully

  const char *content      = "Hello, world!";
  size_t      bytesToWrite = strlen(content);
  size_t      bytesWritten = file.write(
      (const uint8_t *)content, bytesToWrite);  // Use correct write signature

  file.close();
  TEST_ASSERT_EQUAL(bytesToWrite, bytesWritten);
  TEST_ASSERT_EQUAL(strlen(content), bytesWritten);
}

void test_read_from_sd(void) {
  File file = SD.open(FILE_PATH, FILE_READ);

  TEST_ASSERT_TRUE(file);

  String fileContent = "";
  while (file.available()) {
    fileContent += (char)file.read();
  }

  file.close();

  TEST_ASSERT_EQUAL_STRING("Hello, world!", fileContent.c_str());

  // TEST_ASSERT_NOT_NULL(fileContent);
}

int runUnityTests(void) {
  UNITY_BEGIN();
  RUN_TEST(test_sdcard_init);
  RUN_TEST(test_card_type);
  RUN_TEST(test_write_to_sd);
  RUN_TEST(test_read_from_sd);

  return UNITY_END();
}

/**
 * For Arduino framework
 */
void setup() {
  // Wait ~2 seconds before the Unity test runner
  // establishes connection with a board Serial interface
  delay(2000);

  runUnityTests();
}

void loop() {}