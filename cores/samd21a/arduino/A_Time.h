#ifndef ARDUINO_TIME_H
#define ARDUINO_TIME_H

#include "eclay/time.h"

#define millis()  (unsigned long)CORE_TIME_Read_mS()
#define micros()  (unsigned long)CORE_TIME_Read_uS()

#endif  // ARDUINO_TIME_H
