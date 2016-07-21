#ifndef _DISTANCE_H_
#define _DISTANCE_H_

#define DISTANCE_TRIG 8
#define DISTANCE_ECHO 7

extern double distanceLastValue;

void distanceInit();

inline double distanceGetVelocity(double T)
{
  return 331.0 + 0.6 * T;
}

bool distance(double &value);

#endif // _DISTANCE_H_
