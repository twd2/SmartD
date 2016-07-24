#ifndef _WATERING_H_
#define _WATERING_H_

#define ERROR_UNKNOWN 0
#define ERROR_OK 1
#define ERROR_NOWATER 2
#define ERROR_INTERVALTOOSHORT 3
#define ERROR_MOISTURENOTCHANGE 4

#define MOISTURE_THRESHOLD 70.0 // humidity
#define WATER_TANK_THRESHOLD 200.0 // min water in tank
#define WATER_DURATION 1000L // 10000L // 10s
#define WATER_MIN_INTERVAL 0L // 21600000L // 1/4 day // milliseconds = 10^-3s

extern unsigned long waterLastTime;

int waterDo(unsigned int time);
void water(double moisture);

#endif // _WATERING_H_
