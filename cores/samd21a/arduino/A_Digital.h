#ifndef ARDUINO_DIGITAL_H
#define ARDUINO_DIGITAL_H

#include "arduino/A_Types.h"

#include "eclay/digital.h"


static inline void pinMode( eclay_digital_pin_t pin, PinMode mode );
static inline void pinMode( eclay_digital_pin_t pin, PinMode mode )
{
  switch( mode )
  {
    case INPUT:
      ECLAY_DIGITAL_DirectionSet( pin, ECLAY_DIGITAL_DIRECTION_INPUT );
      ECLAY_DIGITAL_PullSet( pin, ECLAY_DIGITAL_PULL_OFF );
      break;
    case OUTPUT:
      ECLAY_DIGITAL_DirectionSet( pin, ECLAY_DIGITAL_DIRECTION_OUTPUT );
      break;
    case INPUT_PULLUP:
      ECLAY_DIGITAL_DirectionSet( pin, ECLAY_DIGITAL_DIRECTION_INPUT );
      ECLAY_DIGITAL_PullSet( pin, ECLAY_DIGITAL_PULL_UP );
      break;
    case INPUT_PULLDOWN:
      ECLAY_DIGITAL_DirectionSet( pin, ECLAY_DIGITAL_DIRECTION_INPUT );
      ECLAY_DIGITAL_PullSet( pin, ECLAY_DIGITAL_PULL_DOWN );
      break;
  }
}

#define digitalWrite(pinNumber, status)  ECLAY_DIGITAL_OutputSet(pinNumber, status)

#define digitalRead(pinNumber)           ECLAY_DIGITAL_InputGet(pinNumber)


#endif  // ARDUINO_DIGITAL_H
