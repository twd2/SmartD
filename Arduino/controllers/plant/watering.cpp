#include "utils.h"
#include "watering.h"
#include "distance.h"
#include "relay.h"

#include <Arduino.h>

bool water_do(unsigned int time)
{
  #ifdef DEBUG
    Serial.print("Watering...");
  #endif
  int succeeded = 1;
  if (distanceLastValue > WATER_TANK_THRESHOLD)
  {
    succeeded = 0;
  }
  else
  {
    relay(true);
    delay(time);
    relay(false);
  }
  #ifdef USE_WIRELESS
    #ifdef DEBUG
      Serial.print("Sending state: ");
    #endif
    sendValue(TYPE_Watered, succeeded);
  #endif
  #ifdef DEBUG
    Serial.println("done.");
  #endif
  return succeeded;
}

void water_plant(double moisture)
{
  static unsigned long last_water = 0;
  if (moisture < MOISTURE_THRESHOLD)
  {
    // watering is needed
    if (last_water == 0 || (unsigned long)(fixedMillis() - last_water) >= WATER_MIN_INTERVAL)
    {
      if (water_do(WATER_DURATION))
      {
        last_water = fixedMillis();
      }
    }
  }
}
