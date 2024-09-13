#include "bme.h"

BME280 *bme;

void setUp(void) {
  // set stuff up here
  bme = new BME280();
}

void tearDown(void) {
  // clean stuff up here
  delete bme;
}

void test_bme_successfully_initiated(void) {
    TEST_ASSERT_NOT_NULL(bme);
}

int runUnityTests(void) {
  UNITY_BEGIN();
  RUN_TEST(test_bme_successfully_initiated);
//   RUN_TEST(test_function_should_doAlsoDoBlah);
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

void loop(){}