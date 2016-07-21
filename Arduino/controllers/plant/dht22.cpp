#include "utils.h"
#include "dht22.h"

#include <dht.h>

dht dht22Instance;

void dht22Init()
{
  DBG("DHT Library Version: ");
  DBGLN(DHT_LIB_VERSION);
}

bool dht22(double &temperature, double &humidity)
{
  delay(2000);

  int chk = dht22Instance.read22(DHT22_BUS);
  switch (chk)
  {
    case DHTLIB_OK: 
      DBGLN("DHT22: OK"); 
      temperature = dht22Instance.temperature;
      humidity = dht22Instance.humidity;
      break;
    case DHTLIB_ERROR_CHECKSUM: 
      DBGLN("DHT122: Checksum error");
      break;
    case DHTLIB_ERROR_TIMEOUT: 
      DBGLN("DHT22: Time out error");
      break;
    case DHTLIB_ERROR_CONNECT: 
      DBGLN("DHT22: Connect error");
      break;
    case DHTLIB_ERROR_ACK_L: 
      DBGLN("DHT22: Ack L error");
      break;
    case DHTLIB_ERROR_ACK_H: 
      DBGLN("DHT22: Ack H error");
      break;
    default: 
      DBGLN("DHT22: Unknown error");
      break;
  }
  return chk == DHTLIB_OK;
}
