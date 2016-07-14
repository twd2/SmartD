#if !defined(USE_DHT11) && defined(DHT11_BUS)
#define USE_DHT11

#include <dht11.h>

dht11 DHT11;

void initDHT11()
{
  #ifdef DEBUG
    Serial.print("DHT11 Library Version: ");
    Serial.println(DHT11LIB_VERSION);
  #endif
}

double *doDHT11()
{
  double *ret = new double[2];
  int chk = DHT11.read(DHT11_BUS);

  switch (chk)
  {
    case 0: 
      #ifdef DEBUG
        Serial.println("DHT11: OK"); 
      #endif
        ret[1] = DHT11.humidity;
        ret[0] = DHT11.temperature;
      break;
    case -1: 
      #ifdef DEBUG
        Serial.println("DHT11: Checksum error");
      #endif
      break;
    case -2: 
      #ifdef DEBUG
        Serial.println("DHT11: Time out error");
      #endif
      break;
    default: 
      #ifdef DEBUG
        Serial.println("DHT11: Unknown error");
      #endif
      break;
  }
  return ret;
}

#endif
