#ifndef ARDUINO_ANALOG_H
#define ARDUINO_ANALOG_H

#include <stdint.h>

#include "A_Types.h"

#ifdef __cplusplus
extern "C"{
#endif

int analogRead(pin_size_t pinNumber);
void analogReference(uint8_t mode);
void analogWrite(pin_size_t pinNumber, int value);

void analogReadResolution(int bits);
void analogWriteResolution(int bits);

#ifdef __cplusplus
} // extern "C"
#endif

#endif  // ARDUINO_ANALOG_H
