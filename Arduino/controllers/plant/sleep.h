#ifndef _SLEEP_H_
#define _SLEEP_H_

extern volatile int f_wdt;

void sleepInit();
void sleep(int);

#endif // _SLEEP_H_
