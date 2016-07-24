#ifndef _SLEEP_H_
#define _SLEEP_H_

extern volatile int f_wdt;
extern unsigned long millisOffset;

void sleepInit();
void sleep(int);

inline unsigned long fixedMillis()
{
  return millis() + millisOffset;
}

inline unsigned long fixedMicros()
{
  const unsigned long microsecondsPerMillsecond = 1000;
  return micros() + millisOffset * microsecondsPerMillsecond;
}

#endif // _SLEEP_H_
