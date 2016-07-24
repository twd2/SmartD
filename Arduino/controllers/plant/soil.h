#ifndef _SOIL_H_
#define _SOIL_H_

#define MOISTURE_PIN A6
#define TEMPERATURE_PIN A7
#define ADC_BITS 10

// Type A (described in README.md)
// #define SOIL_SENSOR_TYPE_A 1

// Type B (described in README.md)
#define SOIL_SENSOR_TYPE_B 1
#define AREF 5.0
#define VOLTAGE_RANGE 2 // 0~2V
#define MOISTURE_RANGE 50 // 0~50%
#define TEMPERATURE_RANGE_MIN -30 // -30~70C
#define TEMPERATURE_RANGE_MAX 70

#if defined(SOIL_SENSOR_TYPE_A) && defined(SOIL_SENSOR_TYPE_B)
#error can not use both A and B
#endif

void soilInit();
int soilAnalogRead(int port);
bool soil(double &temperature, double &moisture);

#endif // _SOIL_H_
