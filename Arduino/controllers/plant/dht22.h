#ifndef _DHT22_H_
#define _DHT22_H_

#include <dht.h>

#define DHT22_BUS A1

extern dht dht22Instance;

void dht22Init();
bool dht22(double &temperature, double &humidity);

#endif // _DHT22_H_
