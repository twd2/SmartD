#include <RCSwitch.h>
//#include <OneWire.h>
//#include <DallasTemperature.h>
//#include <DHT22.h>
//#include <dht11.h>
#include <Wire.h>
#include <math.h> 
#include <SPI.h>
#include "plant.h"

void setup()
{
  #ifdef DEBUG
    Serial.begin(115200);
    Serial.println("Initializing...");
    Serial.print("My address is ");
    Serial.println(ADDRESS);
  #endif
  
  #ifdef USE_DS18B20
    #ifdef DEBUG
      Serial.println("Using DS18B20");
    #endif
    initDS18B20();
  #endif
  
  #ifdef USE_DISTANCE
    #ifdef DEBUG
      Serial.println("Using Distance");
    #endif
    initDistance();
  #endif
  
  #ifdef USE_DHT11
    #ifdef DEBUG
      Serial.println("Using DHT11");
    #endif
    initDHT11();
  #endif
  
  #ifdef USE_DHT22
    #ifdef DEBUG
      Serial.println("Using DHT22");
    #endif
    initDHT22();
  #endif
  
  #ifdef USE_BH1750
    #ifdef DEBUG
      Serial.println("Using BH1750");
    #endif
    initBH1750();
  #endif
  
  #ifdef USE_SHUMIDITY
    #ifdef DEBUG
      Serial.println("Using SHumidity");
    #endif
    initSHumidity();
  #endif
  
  pinMode(RELAY_TRIG, OUTPUT);
  digitalWrite(RELAY_TRIG, LOW);

  #ifdef DEBUG
      Serial.println("Delay ADDRESS * 250 ms");
  #endif
  delay(ADDRESS * 250);
}

void loop()
{ 
  double v;
  unsigned int vv;
  
  #ifdef USE_DISTANCE
    v = doDistance();
    #ifdef DEBUG
      Serial.print("Distance: ");
      Serial.print(v);
      Serial.println("cm");
    #endif
    #ifdef USE_WIRELESS
      #ifdef DEBUG
        Serial.print("Sending Distance: ");
      #endif
      sendValue(TYPE_Distance, (long)(v * 100));
    #endif
  #endif
  
  #ifdef USE_DS18B20
    v = doDS18B20();
    #ifdef DEBUG
      Serial.print("DS18B20: ");
      Serial.print(v);
      Serial.println("oC");
    #endif
    #ifdef USE_WIRELESS
      #ifdef DEBUG
        Serial.print("Sending Temperature: ");
      #endif
      sendValue(TYPE_Temperature, (long)(v * 100));
    #endif
  #endif
  
  #ifdef USE_DHT11
    double *dR1 = doDHT11();
    #ifdef DEBUG
      Serial.print("DHT11: t=");
      Serial.print(dR1[0]);
      Serial.print("oC, h=");
      Serial.print(dR1[1]);
      Serial.println("%");
    #endif
    #ifdef USE_WIRELESS
        #ifndef USE_DS18B20
          #ifdef DEBUG
            Serial.print("Sending Temperature: ");
          #endif
          sendValue(TYPE_Temperature, (long)(dR1[0] * 100));
        #endif
        #ifdef DEBUG
          Serial.print("Sending Humidity: ");
        #endif
        sendValue(TYPE_Humidity, (long)(dR1[1] * 100));
    #endif
    delete [] dR1;
  #endif
 
  #ifdef USE_DHT22
    Serial.print("DHT22: ");
    double *dR2 = doDHT22();
    if (dR2[1] >= 0)
    {
      #ifdef DEBUG
        Serial.print("DHT22: t=");
        Serial.print(dR2[0]);
        Serial.print("oC, h=");
        Serial.print(dR2[1]);
        Serial.println("%");
      #endif
      #ifdef USE_WIRELESS
          #ifndef USE_DS18B20
            #ifdef DEBUG
              Serial.print("Sending Temperature: ");
            #endif
            sendValue(TYPE_Temperature, (long)(dR2[0] * 100));
          #endif
          #ifdef DEBUG
            Serial.print("Sending Humidity: ");
          #endif
          sendValue(TYPE_Humidity, (long)(dR2[1] * 100));
      #endif
    }
    delete [] dR2;
  #endif
  
  #ifdef USE_BH1750
    vv = doBH1750();
    #ifdef DEBUG
      Serial.print("BH1750: ");
      Serial.print(vv);
      Serial.println("lux");
    #endif
    #ifdef USE_WIRELESS
      #ifdef DEBUG
        Serial.print("Sending Illumination: ");
      #endif
      sendValue(TYPE_Illumination, vv);
    #endif
  #endif
  
  #ifdef USE_SHUMIDITY
    vv = doSHumidity();
    water_plant(vv);
    #ifdef DEBUG
      Serial.print("SHumidity: ");
      Serial.print(vv);
      Serial.println("/1024");
    #endif
    #ifdef USE_WIRELESS
      #ifdef DEBUG
        Serial.print("Sending SHumidity: ");
      #endif
      sendValue(TYPE_SHumidity, vv);
    #endif
  #endif
  
  #ifdef DEBUG
    Serial.println("Snoozing...");
    for(int i = 1; i <= SnoozingTimeMS / 1000; ++i)
    {
      Serial.print("Snoozing(");
      Serial.print(i);
      Serial.println("s)...");
      delay(1000);
    }
  #else
    delay(SnoozingTimeMS);
  #endif
  delay(ADDRESS * 100);
}
