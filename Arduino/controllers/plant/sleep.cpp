#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <avr/power.h>
#include <avr/wdt.h>
#include <Arduino.h>

#include "sleep.h"

volatile int f_wdt = 0;
int _MCUSR = 0, _WDTCSR = 0;

ISR(WDT_vect)
{
  if(f_wdt == 1)
  {
    f_wdt = 0;
  }
  else
  {
    // WDT overrun!
    Serial.println("WDT Overrun!!!");
    delay(10);
  }
}

void sleepInit()
{

}

void sleep(int time)
{
  if (time == 0)
  {
    return;
  }
  wdt_reset();

  _MCUSR = MCUSR;
  _WDTCSR = WDTCSR;

  MCUSR &= ~_BV(WDRF); // Clear the reset flag.

  /* In order to change WDE or the prescaler, we need to
   * set WDCE (This will allow updates for 4 clock cycles).
   */

  if ((time & 0b111) == 0) // 8|time
  {
    WDTCSR |= _BV(WDCE) | _BV(WDE);
    WDTCSR = _BV(WDP0) | _BV(WDP3); // 8s
    WDTCSR |= _BV(WDIE); // Enable WDT interrupt (*no reset*).
    time >>= 3;
  }
  else if ((time & 0b11) == 0) // 4|time
  {
    WDTCSR |= _BV(WDCE) | _BV(WDE);
    WDTCSR = _BV(WDP3); // 4s
    WDTCSR |= _BV(WDIE); // Enable WDT interrupt (*no reset*).
    time >>= 2;
  }
  else if ((time & 0b1) == 0) // 2|time
  {
    WDTCSR |= _BV(WDCE) | _BV(WDE);
    WDTCSR = _BV(WDP0) | _BV(WDP1) | _BV(WDP2); // 2s
    WDTCSR |= _BV(WDIE); // Enable WDT interrupt (*no reset*).
    time >>= 1;
  }
  else
  {
    WDTCSR |= _BV(WDCE) | _BV(WDE);
    WDTCSR = _BV(WDP1) | _BV(WDP2); // 1s
    WDTCSR |= _BV(WDIE); // Enable WDT interrupt (*no reset*).
  }

  delay(1);

  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_enable();

  ++time;
  while (--time)
  {
    f_wdt = 1;
    sleep_mode();
    // Sleeping zzZ...
  }

  sleep_disable();
  power_all_enable();
  WDTCSR = _WDTCSR & ~_BV(WDE) & ~_BV(WDIE);
}
