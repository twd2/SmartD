#include "distance.h"

#include <Arduino.h>

double distanceLastValue = 0.0;

void distanceInit()
{
  pinMode(DISTANCE_ECHO, INPUT);
  pinMode(DISTANCE_TRIG, OUTPUT);
}

bool distance(double &value)
{
  digitalWrite(DISTANCE_TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(DISTANCE_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(DISTANCE_TRIG, LOW);
  double duration = pulseIn(DISTANCE_ECHO, HIGH);
  value = distanceLastValue = distanceGetVelocity(25) * duration / 1000000 * 100 / 2;
  return value >= 1.0 && value <= 1000.0; // Actually, the range is 2cm to 450cm.
}
