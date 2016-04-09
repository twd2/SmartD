#if !defined(USE_DHT22) && defined(DHT22_BUS)
#define USE_DHT22

#include <DHT22.h>

DHT22 myDHT22(DHT22_BUS);

void initDHT22()
{
  #ifdef DEBUG

  #endif
}

double *doDHT22()
{
  delay(2000);
  double *ret = new double[2];
  ret[0] = 0;
  ret[1] = -1;
  DHT22_ERROR_t errorCode = myDHT22.readData();
  switch(errorCode)
  {
    case DHT_ERROR_NONE:
      Serial.println("Got Data ");
      ret[0] = myDHT22.getTemperatureC();
      ret[1] = myDHT22.getHumidity();
      break;
    case DHT_ERROR_CHECKSUM:
      #ifdef DEBUG
        Serial.println("check sum error ");
      #endif
      break;
    case DHT_BUS_HUNG:
      #ifdef DEBUG
        Serial.println("BUS Hung ");
      #endif
      break;
    case DHT_ERROR_NOT_PRESENT:
      #ifdef DEBUG
        Serial.println("Not Present ");
      #endif
      break;
    case DHT_ERROR_ACK_TOO_LONG:
      #ifdef DEBUG
        Serial.println("ACK time out ");
      #endif
      break;
    case DHT_ERROR_SYNC_TIMEOUT:
      #ifdef DEBUG
        Serial.println("Sync Timeout ");
      #endif
      break;
    case DHT_ERROR_DATA_TIMEOUT:
      #ifdef DEBUG
        Serial.println("Data Timeout ");
      #endif
      break;
    case DHT_ERROR_TOOQUICK:
      #ifdef DEBUG
        Serial.println("Polled to quick ");
      #endif
      break;
  }
  return ret;
}

#endif
