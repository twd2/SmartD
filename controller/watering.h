#define WATER_THRESHOLD 200 // humidity
#define WATER_TANK_THRESHOLD 180.0 // min water in tank
#define WATER_TIME 5000L // 5s
#define WATER_MIN_INTERVAL 86400000L // 1day // milliseconds = 10^-3s

bool water_do(unsigned int time)
{
  #ifdef DEBUG
    Serial.print("Watering...");
  #endif
  int succeeded = 1;
  if (last_distance > WATER_TANK_THRESHOLD)
  {
    succeeded = 0;
  }
  else
  {
    digitalWrite(RELAY_TRIG, HIGH);
    delay(time);
    digitalWrite(RELAY_TRIG, LOW);
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

void water_plant(unsigned int hu)
{
  static unsigned long last_water = 0;
  if (hu < WATER_THRESHOLD)
  {
    // watering is needed
    if (last_water == 0 || millis() - last_water >= WATER_MIN_INTERVAL)
    {
      if (water_do(WATER_TIME))
      {
        last_water = millis();
      }
    }
  }
}