#if !defined(USE_DS18B20) && defined(DS18B20_BUS)
#define USE_DS18B20

#include <OneWire.h>
#include <DallasTemperature.h>

OneWire oneWireDS18B20(DS18B20_BUS);
DallasTemperature sDS18B20(&oneWireDS18B20);

void initDS18B20()
{
  sDS18B20.begin();
}

double doDS18B20()
{
  sDS18B20.requestTemperatures();
  lasttemp = sDS18B20.getTempCByIndex(0);
  return lasttemp;
}

#endif
