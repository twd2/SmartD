#ifndef _RELAY_H_
#define _RELAY_H_

#define RELAY_PIN 6

#include <Arduino.h>

inline void relayInit()
{
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW);
}

inline void relay(bool state)
{
  digitalWrite(RELAY_PIN, state);
}

#endif // _RELAY_H_