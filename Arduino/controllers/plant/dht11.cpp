#include "utils.h"
#include "dht11.h"

#include <dht.h>

dht dht11Instance;

void dht11Init()
{
  DBG("DHT Library Version: ");
  DBGLN(DHT_LIB_VERSION);
}

bool dht11(double &temperature, double &humidity)
{
  int chk = dht11Instance.read11(DHT11_BUS);
  switch (chk)
  {
    case DHTLIB_OK: 
      DBGLN("DHT11: OK"); 
      temperature = dht11Instance.temperature;
      humidity = dht11Instance.humidity;
      break;
    case DHTLIB_ERROR_CHECKSUM: 
      DBGLN("DHT11: Checksum error");
      break;
    case DHTLIB_ERROR_TIMEOUT: 
      DBGLN("DHT11: Time out error");
      break;
    case DHTLIB_ERROR_CONNECT: 
      DBGLN("DHT11: Connect error");
      break;
    case DHTLIB_ERROR_ACK_L: 
      DBGLN("DHT11: Ack L error");
      break;
    case DHTLIB_ERROR_ACK_H: 
      DBGLN("DHT11: Ack H error");
      break;
    default: 
      DBGLN("DHT11: Unknown error");
      break;
  }
  return chk == DHTLIB_OK;
}
