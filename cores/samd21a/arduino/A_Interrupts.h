#ifndef ARDUINO_INTERRUPTS_H
#define ARDUINO_INTERRUPTS_H

#include "eclay/interrupt.h"
#include "A_Types.h"

#define interrupts()   CORE_INTERRUPT_global_disable()
#define noInterrupts() CORE_INTERRUPT_global_enable()

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
