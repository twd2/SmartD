#include <RCSwitch.h>
//#include <OneWire.h>
//#include <DallasTemperature.h>
//#include <DHT22.h>
//#include <dht11.h>
#include <Wire.h>
#include <math.h> 
#include <SPI.h>
#include "plant.h"
#include "sleep.h"

void setup()
{
  sleepInit();

#ifdef DEBUG
  Serial.begin(115200);
#endif

  DBGLN("Initializing...");
  DBG("My address is ");
  DBGLN(ADDRESS);

#ifdef USE_DS18B20
  DBGLN("Using DS18B20");
  initDS18B20();
#endif

#ifdef USE_DISTANCE
  DBGLN("Using Distance");
  initDistance();
#endif

#ifdef USE_DHT11
  DBGLN("Using DHT11");
  initDHT11();
#endif

#ifdef USE_DHT22
  DBGLN("Using DHT22");
  initDHT22();
#endif

#ifdef USE_BH1750
  DBGLN("Using BH1750");
  initBH1750();
#endif

#ifdef USE_SHUMIDITY
  DBGLN("Using SHumidity");
  initSHumidity();
#endif

  pinMode(RELAY_TRIG, OUTPUT);
  digitalWrite(RELAY_TRIG, LOW);

  DBGLN("Delay ADDRESS * 250 ms");
  delay(ADDRESS * 250);
}

void loop()
{ 
  double v;
  unsigned int vv;

#ifdef USE_DISTANCE
  v = doDistance();
  DBG("Distance: ");
  DBG(v);
  DBGLN("cm");
#ifdef USE_WIRELESS
  sendValue(TYPE_Distance, (long)(v * 100));
#endif
#endif

#ifdef USE_DS18B20
  v = doDS18B20();
  DBG("DS18B20: ");
  DBG(v);
  DBGLN("C");
#ifdef USE_WIRELESS
  sendValue(TYPE_Temperature, (long)(v * 100));
#endif
#endif

#ifdef USE_DHT11
  double *dR1 = doDHT11();
  DBG("DHT11: t=");
  DBG(dR1[0]);
  DBG("C, h=");
  DBG(dR1[1]);
  DBGLN("%");
#ifdef USE_WIRELESS
#ifndef USE_DS18B20
  DBG("Sending Temperature: ");
  sendValue(TYPE_Temperature, (long)(dR1[0] * 100));
#endif
  DBG("Sending Humidity: ");
  sendValue(TYPE_Humidity, (long)(dR1[1] * 100));
#endif
  delete [] dR1;
#endif

#ifdef USE_DHT22
  DBG("DHT22: ");
  double *dR2 = doDHT22();
  if (dR2[1] >= 0)
  {
#ifdef DEBUG
    DBG("DHT22: t=");
    DBG(dR2[0]);
    DBG("C, h=");
    DBG(dR2[1]);
    DBGLN("%");
#endif
#ifdef USE_WIRELESS
#ifndef USE_DS18B20
   DBG("Sending Temperature: ");
   sendValue(TYPE_Temperature, (long)(dR2[0] * 100));
#endif
   DBG("Sending Humidity: ");
   sendValue(TYPE_Humidity, (long)(dR2[1] * 100));
#endif
  }
  delete [] dR2;
#endif

#ifdef USE_BH1750
  vv = doBH1750();
  DBG("BH1750: ");
  DBG(vv);
  DBGLN("lux");
#ifdef USE_WIRELESS
  sendValue(TYPE_Illumination, vv);
#endif
#endif

#ifdef USE_SHUMIDITY
  vv = doSHumidity();
  water_plant(vv);
  DBG("SHumidity: ");
  DBG(vv);
  DBGLN("/1024");
#ifdef USE_WIRELESS
  sendValue(TYPE_SHumidity, vv);
#endif
#endif

#ifdef DEBUG
  DBGLN("Snoozing...");
  for (int i = 1; i <= SnoozingTimeMS / 1000; ++i)
  {
    DBG("Snoozing(");
    DBG(i);
    DBGLN("s)...");
    delay(10); // Wait Serial to transmit signals.
    sleep(1);
  }
#else
  sleep(SnoozingTimeMS);
#endif
  delay(ADDRESS * 100);
}

