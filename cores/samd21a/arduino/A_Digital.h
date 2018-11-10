#ifndef ARDUINO_DIGITAL_H
#define ARDUINO_DIGITAL_H

#include "arduino/A_Types.h"

#include "core/digital.h"


static inline void pinMode( core_digital_pin_t pin, PinMode mode );
static inline void pinMode( core_digital_pin_t pin, PinMode mode )
{
  switch( mode )
  {
    case INPUT:
      CORE_DIGITAL_DirectionSet( pin, CORE_DIGITAL_DIRECTION_INPUT );
      CORE_DIGITAL_PullSet( pin, CORE_DIGITAL_PULL_OFF );
      break;
    case OUTPUT:
      CORE_DIGITAL_DirectionSet( pin, CORE_DIGITAL_DIRECTION_OUTPUT );
      break;
    case INPUT_PULLUP:
      CORE_DIGITAL_DirectionSet( pin, CORE_DIGITAL_DIRECTION_INPUT );
      CORE_DIGITAL_PullSet( pin, CORE_DIGITAL_PULL_UP );
      break;
    case INPUT_PULLDOWN:
      CORE_DIGITAL_DirectionSet( pin, CORE_DIGITAL_DIRECTION_INPUT );
      CORE_DIGITAL_PullSet( pin, CORE_DIGITAL_PULL_DOWN );
      break;
  }
}

#define digitalWrite(pinNumber, status)  CORE_DIGITAL_OutputSet(pinNumber, status)

#define digitalRead(pinNumber)           CORE_DIGITAL_InputGet(pinNumber)


#endif  // ARDUINO_DIGITAL_H
