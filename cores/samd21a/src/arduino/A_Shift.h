#ifndef ARDUINO_SHIFT_H
#define ARDUINO_SHIFT_H

#include <stdint.h>

#include "A_Types.h"

#ifdef __cplusplus
extern "C"{
#endif

uint8_t shiftIn(pin_size_t dataPin, pin_size_t clockPin, BitOrder bitOrder);
void shiftOut(pin_size_t dataPin, pin_size_t clockPin, BitOrder bitOrder, uint8_t value);

#ifdef __cplusplus
} // extern "C"
#endif

#endif  // ARDUINO_SHIFT_H
