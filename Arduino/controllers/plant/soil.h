#ifndef _SOIL_H_
#define _SOIL_H_

#define MOISTURE_PIN A6
#define TEMPERATURE_PIN A7
#define AREF 5
#define ADC_BITS 10
#define VOLTAGE_RANGE 2 // 0~2V
#define MOISTURE_RANGE 50 // 0~50%
#define TEMPERATURE_RANGE_MIN -30 // -30~70C
#define TEMPERATURE_RANGE_MAX 70

void soilInit();
int soilAnalogRead(int port);
bool soil(double &temperature, double &moisture);

#endif // _SOIL_H_
