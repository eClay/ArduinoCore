#ifndef WIRING_SHIFT_H
#define WIRING_SHIFT_H

#include <stdint.h>

#ifdef __cplusplus
extern "C"{
#endif

uint8_t shiftIn(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder);
void shiftOut(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder, uint8_t value);

#ifdef __cplusplus
} // extern "C"
#endif

#endif
