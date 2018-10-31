#ifndef WIRING_PULSE_H
#define WIRING_PULSE_H

#ifdef __cplusplus
#include <stdint.h>

unsigned long pulseIn(uint8_t pin, uint8_t state, unsigned long timeout = 1000000L);
unsigned long pulseInLong(uint8_t pin, uint8_t state, unsigned long timeout = 1000000L);
#endif

#endif
