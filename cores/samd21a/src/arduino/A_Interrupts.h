#ifndef ARDUINO_INTERRUPTS_H
#define ARDUINO_INTERRUPTS_H

#include "A_Types.h"

// interrupts() / noInterrupts() must be defined by the core

#ifdef __cplusplus
extern "C"{
#endif

typedef void (*voidFuncPtr)(void);
typedef void (*voidFuncPtrParam)(void*);

void attachInterrupt(pin_size_t interruptNumber, voidFuncPtr callback, PinStatus mode);
void attachInterruptParam(pin_size_t interruptNumber, voidFuncPtrParam callback, PinStatus mode, void* param);
void detachInterrupt(pin_size_t interruptNumber);

#ifdef __cplusplus
} // extern "C"
#endif

#endif  // ARDUINO_INTERRUPTS_H
