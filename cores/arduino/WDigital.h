#ifndef WIRING_DIGITAL_H
#define WIRING_DIGITAL_H

#include "WTypes.h"

#ifdef __cplusplus
extern "C"{
#endif

int digitalRead(uint8_t pin);
void digitalWrite(uint8_t pin, uint8_t value);
void pinMode(uint8_t pin, uint8_t mode);

#ifdef __cplusplus
} // extern "C"
#endif

#endif
