#include "icm20948.h"

// BME280  *bme;
// BMEData *bmeData;
ICM20948 *imu;
IMUData   imuData;

void setUp(void) {
  // set stuff up here
  // bme = new BME280();
  imu = new ICM20948();

  // bmeData = new BMEData;
}

void tearDown(void) {
  // clean stuff up here
  // delete bme;
  // delete bmeData;
  delete imu;
}

void test_imu_successfully_initiated(void) { TEST_ASSERT_NOT_NULL(imu); }

void test_getTemperature_should_return_float(void) {
  imuData.temperature = imu->getTemperature();

  TEST_ASSERT_GREATER_THAN(0.0f, imuData.temperature);
  TEST_ASSERT_FLOAT_IS_NOT_INF(imuData.temperature);
}

// WARNING: This test gives false positive. Fix it later.
void test_getSensorData_should_be_able_to_assign_value(void) {
  imu->getSensorData(imuData);

  TEST_ASSERT_NOT_EQUAL_FLOAT(0.0f, imuData.acceleration.x);
  TEST_ASSERT_NOT_EQUAL_FLOAT(0.0f, imuData.acceleration.y);
  TEST_ASSERT_NOT_EQUAL_FLOAT(0.0f, imuData.acceleration.z);
  Serial.printf("Acceleration : %2f; %2f; %2f", imuData.acceleration.x,
                imuData.acceleration.y, imuData.acceleration.z);

  TEST_ASSERT_NOT_EQUAL_FLOAT(0.0f, imuData.gyro.x);
  TEST_ASSERT_NOT_EQUAL_FLOAT(0.0f, imuData.gyro.y);
  TEST_ASSERT_NOT_EQUAL_FLOAT(0.0f, imuData.gyro.z);
  Serial.printf("gyro : %2f; %2f; %2f", imuData.gyro.x, imuData.gyro.y,
                imuData.gyro.z);

  TEST_ASSERT_NOT_EQUAL_FLOAT(0.0f, imuData.temperature);
  Serial.printf("temperature : %2f", imuData.temperature);

  TEST_ASSERT_NOT_EQUAL_FLOAT(0.0f, imuData.magnetic.x);
  TEST_ASSERT_NOT_EQUAL_FLOAT(0.0f, imuData.magnetic.y);
  TEST_ASSERT_NOT_EQUAL_FLOAT(0.0f, imuData.magnetic.z);
  Serial.printf("magnetic : %2f; %2f; %2f", imuData.magnetic.x,
                imuData.magnetic.y, imuData.magnetic.z);
}

int runUnityTests(void) {
  UNITY_BEGIN();
  RUN_TEST(test_imu_successfully_initiated);
  RUN_TEST(test_getTemperature_should_return_float);
  RUN_TEST(test_getSensorData_should_be_able_to_assign_value);
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