#if !defined(USE_WIRELESS) && defined(WIRELESS_TXD)
#define USE_WIRELESS

#include <RCSwitch.h>

RCSwitch mySwitch = RCSwitch();

void sendValue(unsigned long addr, unsigned long type, unsigned long value);

void sendValue(unsigned long type, unsigned long value)
{
  sendValue(ADDRESS, type, value);
}

void sendValue(unsigned long addr, unsigned long type, unsigned long value)
{
  mySwitch.enableTransmit(WIRELESS_TXD);
  mySwitch.setRepeatTransmit(4); // watch this, 3-8 repeats will be enough 
  char dataBit[33] = {0};
  toBinary((((addr << 24) & ADDR_MASK) | ((type << 16) & TYPE_MASK) | (value & VALUE_MASK)), dataBit, 32);
  mySwitch.send(dataBit);
  #ifdef DEBUG
    Serial.print("Sent: ");
    Serial.println(dataBit);
  #endif
  mySwitch.disableTransmit();
  delay(50);
}

#endif
