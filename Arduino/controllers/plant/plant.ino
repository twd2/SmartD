#include "plant.h"
#include "sleep.h"
#include "ids.h"

#include <math.h>

void setup()
{
  sleepInit();

#ifdef DEBUG
  Serial.begin(115200);
#endif

  DBGLN("Initializing...");
  DBG("My address is ");
  DBGLN(ADDRESS);

#ifdef _WIRELESS_H_
  DBGLN("Using wireless transmitter");
  wirelessInit();
#endif

#ifdef _DS18B20_H_
  DBGLN("Using DS18B20");
  ds18b20Init();
#endif

#ifdef _DISTANCE_H_
  DBGLN("Using distance sensor");
  distanceInit();
#endif

#ifdef _DHT11_H_
  DBGLN("Using DHT11");
  dht11Init();
#endif

#ifdef _DHT22_H_
  DBGLN("Using DHT22");
  dht22Init();
#endif

#ifdef _BH1750_H_
  DBGLN("Using BH1750");
  bh1750Init();
#endif

#ifdef _SOIL_H_
  DBGLN("Using soil sensors");
  soilInit();
#endif

#ifdef _RELAY_H_
  DBGLN("Using relay as executer");
  relayInit();
#endif

  DBGLN("Delay ADDRESS * 251 ms");
  delay(ADDRESS * 251);
}

void loop()
{
  double dValue1 = 0.0, dValue2 = 0.0;
  unsigned int uValue = 0;

#ifdef _DISTANCE_H_
  DBG("Distance: ");
  if (distance(dValue1))
  {
    DBG(dValue1);
    DBGLN("cm");
#ifdef _WIRELESS_H_
    sendValue(TYPE_Distance, toFixedPoint(dValue1));
#endif
  }
  else
  {
    DBGLN("failed");
  }
#endif

#ifdef _DS18B20_H_
  DBG("DS18B20: ");
  if (ds18b20(dValue1))
  {
    DBG(dValue1);
    DBGLN("C");
#ifdef _WIRELESS_H_
    sendValue(TYPE_Temperature, toFixedPoint(dValue1));
#endif
  }
  else
  {
    DBGLN("Failed");
  }
#endif

#ifdef _DHT11_H_
  DBG("DHT11: ");
  if (dht11(dValue1, dValue2))
  {
    DBG("t=");
    DBG(dValue1);
    DBG("C, h=");
    DBG(dValue2);
    DBGLN("%");
#ifdef _WIRELESS_H_
#ifndef _DS18B20_H_
    DBG("Sending Temperature: ");
    sendValue(TYPE_Temperature, toFixedPoint(dValue1));
#endif
    DBG("Sending Humidity: ");
    sendValue(TYPE_Humidity, toFixedPoint(dValue2));
#endif
  }
  else
  {
    DBGLN("Failed");
  }
#endif

#ifdef _DHT22_H_
  DBG("DHT22: ");
  if (dht22(dValue1, dValue2))
  {
    DBG("t=");
    DBG(dValue1);
    DBG("C, h=");
    DBG(dValue2);
    DBGLN("%");
#ifdef _WIRELESS_H_
#ifndef _DS18B20_H_
    DBG("Sending Temperature: ");
    sendValue(TYPE_Temperature, toFixedPoint(dValue1));
#endif
    DBG("Sending Humidity: ");
    sendValue(TYPE_Humidity, toFixedPoint(dValue2));
#endif
  }
  else
  {
    DBGLN("Failed");
  }
#endif

#ifdef _BH1750_H_
  DBG("BH1750: ");
  if (bh1750(uValue))
  {
    DBG(uValue);
    DBGLN("lux");
#ifdef _WIRELESS_H_
    sendValue(TYPE_Illumination, uValue);
#endif
  }
  else
  {
    DBGLN("failed");
  }
#endif

#ifdef _SOIL_H_
  DBG("Soil: ");
  if (soil(dValue1, dValue2))
  {
    DBG("t=");
    DBG(dValue1);
    DBG("C, m=");
    DBG(dValue2);
    DBGLN("%");
#ifdef _WIRELESS_H_
    DBG("Sending Temperature: ");
    sendValue(TYPE_Temperature, toFixedPoint(dValue1));
    DBG("Sending Moisture: ");
    sendValue(TYPE_Moisture, toFixedPoint(dValue2));
#endif
    water(dValue2);
  }
  else
  {
    DBGLN("Failed");
  }
#endif

#ifdef DEBUG
  DBGLN("Snoozing...");
  for (int i = 1; i <= SnoozingTimeS; ++i)
  {
    DBG("Snoozing(");
    DBG(i);
    DBGLN("s)...");
    delay(10); // Wait Serial to transmit signals.
    sleep(1);
  }
#else
  sleep(SnoozingTimeS);
#endif

  DBGLN("Delay ADDRESS * 97 ms");
  delay(ADDRESS * 97);
}

