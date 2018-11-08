#ifndef ARDUINO_TONE_H
#define ARDUINO_TONE_H

#ifdef __cplusplus

#include "A_Types.h"

void tone(pin_size_t pin, unsigned int frequency, unsigned long duration = 0);
void noTone(pin_size_t pin);

#endif  // __cplusplus

#endif  // ARDUINO_TONE_H
