#ifndef _WIRELESS_H_
#define _WIRELESS_H_

#include <RCSwitch.h>

#define ADDRESS 1L
#define WIRELESS_TXD 10

extern RCSwitch wirelessInstance;

void wirelessInit();
void sendValue(unsigned long type, unsigned long value);
void sendValue(unsigned long addr, unsigned long type, unsigned long value);

#endif // _WIRELESS_H_
