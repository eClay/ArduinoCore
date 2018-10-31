#ifndef WIRING_ANALOG_H
#define WIRING_ANALOG_H

#include <stdint.h>

#ifdef __cplusplus
extern "C"{
#endif

int analogRead(uint8_t pin);
void analogReference(uint8_t type);
void analogWrite(uint8_t pin, int value);

void analogReadResolution(int bits);
void analogWriteResolution(int bits);

#ifdef __cplusplus
} // extern "C"
#endif

#endif
