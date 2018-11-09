#ifndef ARDUINO_DELAY_H
#define ARDUINO_DELAY_H

#include "core/core_time.h"

#define delay(ms)               CORE_TIME_Delay_mS(ms)
#define delayMicroseconds(us)   CORE_TIME_Delay_uS(us)

#endif  // ARDUINO_DELAY_H
