#ifndef ARDUINO_PULSE_H
#define ARDUINO_PULSE_H

#include "A_Types.h"

unsigned long pulseIn(pin_size_t pin, PinStatus state, unsigned long timeout);
unsigned long pulseInLong(pin_size_t pin, PinStatus state, unsigned long timeout);

#ifdef __cplusplus

unsigned long pulseIn(pin_size_t pin, PinStatus state, unsigned long timeout = 1000000L);
unsigned long pulseInLong(pin_size_t pin, PinStatus state, unsigned long timeout = 1000000L);

#endif  // __cplusplus

#endif  // ARDUINO_PULSE_H
