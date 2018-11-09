#ifndef ARDUINO_DIGITAL_H
#define ARDUINO_DIGITAL_H

#include "core/core_digital.h"

// Arduino Function Mapping
#define pinMode(pinNumber, pinMode)      CORE_DIGITAL_PinModeSet(pinNumber, pinMode)
#define digitalWrite(pinNumber, status)  CORE_DIGITAL_OutputPinSet(pinNumber, status)
#define digitalRead(pinNumber)           CORE_DIGITAL_InputPinRead(pinNumber)

#endif  // ARDUINO_DIGITAL_H
