#ifndef _UTILS_H_
#define _UTILS_H_

#define DEBUG 1

#ifdef DEBUG
#define DBG(x) (Serial.print(x))
#define DBGLN(x) (Serial.println(x))
#else
#define DBG(x) ((void)0)
#define DBGLN(x) ((void)0)
#endif

#define toFixedPoint(x) ((long)((x) * 100)) // TODO(twd2): round?

#endif // _UTILS_H_
