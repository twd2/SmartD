#ifndef _DS18B20_H_
#define _DS18B20_H_

#include <OneWire.h>
#include <DallasTemperature.h>

#define DS18B20_BUS 2

extern OneWire ds18b20OneWire;
extern DallasTemperature ds18b20Instance;

void ds18b20Init();
bool ds18b20(double &temperature);

#endif // _DS18B20_H_
