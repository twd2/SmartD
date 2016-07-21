#ifndef _DHT11_H_
#define _DHT11_H_

#include <dht.h>

#define DHT11_BUS A1

extern dht dht11Instance;

void dht11Init();
bool dht11(double &temperature, double &humidity);

#endif // _DHT11_H_
