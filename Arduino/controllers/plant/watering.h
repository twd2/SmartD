#ifndef _WATERING_H_
#define _WATERING_H_

#define MOISTURE_THRESHOLD 70.0 // humidity
#define WATER_TANK_THRESHOLD 200.0 // min water in tank
#define WATER_DURATION 1000L // 10000L // 10s
#define WATER_MIN_INTERVAL 0L // 21600000L // 1/4 day // milliseconds = 10^-3s

bool water_do(unsigned int time);
void water_plant(double moisture);

#endif // _WATERING_H_
