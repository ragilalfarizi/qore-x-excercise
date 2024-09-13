#include "bme.h"

BME280  *bme;
BMEData *bmeData;

void setUp(void) {
  // set stuff up here
  bme = new BME280();

  bmeData = new BMEData;
}

void tearDown(void) {
  // clean stuff up here
  delete bme;
  delete bmeData;
}

void test_bme_successfully_initiated(void) { TEST_ASSERT_NOT_NULL(bme); }

void test_getTemperature_should_return_float(void) {
  bmeData->temperature = bme->getTemperature();
  
  TEST_ASSERT_NOT_NULL(bmeData->temperature);
  TEST_ASSERT_FLOAT_IS_NOT_INF(bmeData->temperature);
}

int runUnityTests(void) {
  UNITY_BEGIN();
  RUN_TEST(test_bme_successfully_initiated);
  RUN_TEST(test_getTemperature_should_return_float);
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