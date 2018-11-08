#ifndef ARDUINO_DIGITAL_H
#define ARDUINO_DIGITAL_H

#include "A_Types.h"

#ifdef __cplusplus
extern "C"{
#endif

void pinMode(pin_size_t pinNumber, PinMode pinMode);
//void digitalWrite(pin_size_t pinNumber, PinStatus status);
PinStatus digitalRead(pin_size_t pinNumber);

#ifdef __cplusplus
} // extern "C"
#endif

#endif  // ARDUINO_DIGITAL_H
