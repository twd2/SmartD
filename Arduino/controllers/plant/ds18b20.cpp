#include "ds18b20.h"

#include <OneWire.h>
#include <DallasTemperature.h>

OneWire ds18b20OneWire(DS18B20_BUS);
DallasTemperature ds18b20Instance(&ds18b20OneWire);

void ds18b20Init()
{
  ds18b20Instance.begin();
}

bool ds18b20(double &temperature)
{
  ds18b20Instance.requestTemperatures();
  if (ds18b20Instance.getDeviceCount() < 1)
  {
    return false;
  }
  temperature = ds18b20Instance.getTempCByIndex(0);
  return true;
}

