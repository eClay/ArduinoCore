#ifndef WIRING_INTERRUPTS_H
#define WIRING_INTERRUPTS_H

#include <stdint.h>

#ifdef __cplusplus
extern "C"{
#endif

void attachInterrupt(uint8_t, void (*)(void), int mode);
void detachInterrupt(uint8_t);

#ifdef __cplusplus
} // extern "C"
#endif

#endif