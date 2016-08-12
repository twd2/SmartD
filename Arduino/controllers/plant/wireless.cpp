#include "utils.h"
#include "ids.h"
#include "wireless.h"

#include <RCSwitch.h>

RCSwitch wirelessInstance;

void wirelessInit()
{
}

void sendValue(unsigned long type, unsigned long value)
{
  sendValue(ADDRESS, type, value);
}

void sendValue(unsigned long addr, unsigned long type, unsigned long value)
{
  unsigned long packet = (((addr << 24) & _32_ADDR_MASK) | ((type << 16) & _32_TYPE_MASK) | (value & _32_VALUE_MASK));

  wirelessInstance.enableTransmit(WIRELESS_TXD);
  wirelessInstance.setRepeatTransmit(4); // watch this, 3~8 repeats will be enough 
  wirelessInstance.send(packet, 32);
  wirelessInstance.disableTransmit();

  DBG("Wireless: sent ");
  DBGLN(packet);

  delay(5);
}
