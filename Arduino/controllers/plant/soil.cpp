#include "soil.h"

#include <Arduino.h>

void soilInit()
{
  pinMode(MOISTURE_PIN, INPUT);
  pinMode(TEMPERATURE_PIN, INPUT);
}

int soilAnalogRead(int port)
{
  // TODO(twd2): use more precise (16 bits) external ADC
  return analogRead(port);
}

#ifdef SOIL_SENSOR_TYPE_A
bool soil(double &temperature, double &moisture)
{
  moisture = soilAnalogRead(MOISTURE_PIN);
  moisture = 1.0 - moisture / (1 << ADC_BITS);

  temperature = -327.68;

  return true;
}
#endif

#ifdef SOIL_SENSOR_TYPE_B
bool soil(double &temperature, double &moisture)
{
  moisture = soilAnalogRead(MOISTURE_PIN);
  moisture = moisture * AREF / (1 << ADC_BITS) * (MOISTURE_RANGE / VOLTAGE_RANGE);

  temperature = soilAnalogRead(TEMPERATURE_PIN);
  temperature = temperature * AREF / (1 << ADC_BITS) * ((TEMPERATURE_RANGE_MAX - TEMPERATURE_RANGE_MIN) / VOLTAGE_RANGE)  + TEMPERATURE_RANGE_MIN;

  return true;
}
#endif

