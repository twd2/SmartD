#include "utils.h"
#include "watering.h"
#include "distance.h"
#include "relay.h"
#include "ids.h"
#include "wireless.h"
#include "sleep.h"

#include <Arduino.h>

unsigned long waterLastTime = 0;

int waterDo(unsigned int time)
{
  if (waterLastTime != 0 && (unsigned long)(fixedMillis() - waterLastTime) < WATER_MIN_INTERVAL)
  {
    return ERROR_INTERVALTOOSHORT;
  }

  if (distanceLastValue > WATER_TANK_THRESHOLD)
  {
    return ERROR_NOWATER;
  }

  DBG("Watering: ");
  relay(true);
  delay(time);
  relay(false);
  DBGLN("done.");

  // TODO(twd2): check if moisture changed

  waterLastTime = fixedMillis();
  return ERROR_OK;
}

void water(double moisture)
{
  if (moisture < MOISTURE_THRESHOLD) // watering is needed
  {
    auto errorCode = waterDo(WATER_DURATION);
    DBG("Sending error code: ");
    sendValue(TYPE_Watered, errorCode);
  }
}
