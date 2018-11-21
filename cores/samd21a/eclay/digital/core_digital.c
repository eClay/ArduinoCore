#include "eclay/digital.h"

#include "hri/port.h"

#include <sam.h>

#include "utils/utils_repeat_macro.h"


typedef struct
{
  hri_port_group_t port;
  hri_port_pin_t   pin;
} eclay_digital_pin_definition_t;

#define ECLAY_DIGITAL_PIN_DEFINITION(noarg, pin)   { ECLAY_DIGITAL_PIN_##pin },

static const eclay_digital_pin_definition_t coreDigitalPins[] =
{
  REPEAT_MACRO(ECLAY_DIGITAL_PIN_DEFINITION, 0, ECLAY_DIGITAL_PIN_MAX)
};


void ECLAY_DIGITAL_DirectionSet_noinline(
    eclay_digital_pin_t        pin,
    eclay_digital_direction_t  direction
  )
{
  if( pin < ECLAY_DIGITAL_PIN_MAX )
  {
    HRI_PORT_DirectionSet( coreDigitalPins[pin].port, coreDigitalPins[pin].pin, direction );

    // Always enable input reads for digital pins
    HRI_PORT_InputEnableSet( coreDigitalPins[pin].port, coreDigitalPins[pin].pin, true );
  }
  else
  {

  }
}

eclay_digital_direction_t ECLAY_DIGITAL_DirectionGet_noinline(
    eclay_digital_pin_t        pin
  )
{
  if( pin < ECLAY_DIGITAL_PIN_MAX )
  {
    return HRI_PORT_DirectionGet( coreDigitalPins[pin].port, coreDigitalPins[pin].pin );
  }
  else
  {
    return ECLAY_DIGITAL_DIRECTION_INPUT;
  }
}


void ECLAY_DIGITAL_OutputSet_noinline(
    eclay_digital_pin_t        pin,
    eclay_digital_pinstate_t   state
  )
{
  if( pin < ECLAY_DIGITAL_PIN_MAX )
  {
    HRI_PORT_OutputSet( coreDigitalPins[pin].port, coreDigitalPins[pin].pin, state );
  }
  else
  {

  }
}

void ECLAY_DIGITAL_OutputToggle_noinline(
    eclay_digital_pin_t        pin
  )
{
  if( pin < ECLAY_DIGITAL_PIN_MAX )
  {
    HRI_PORT_OutputToggle( coreDigitalPins[pin].port, coreDigitalPins[pin].pin );
  }
  else
  {

  }
}

eclay_digital_pinstate_t ECLAY_DIGITAL_OutputGet_noinline(
    eclay_digital_pin_t        pin
  )
{
  if( pin < ECLAY_DIGITAL_PIN_MAX )
  {
    return HRI_PORT_OutputGet( coreDigitalPins[pin].port, coreDigitalPins[pin].pin );
  }
  else
  {
    return ECLAY_DIGITAL_PINSTATE_LOW;
  }
}


eclay_digital_pinstate_t ECLAY_DIGITAL_InputGet_noinline(
    eclay_digital_pin_t        pin
  )
{
  if( pin < ECLAY_DIGITAL_PIN_MAX )
  {
    return HRI_PORT_InputGet( coreDigitalPins[pin].port, coreDigitalPins[pin].pin );
  }
  else
  {
    return ECLAY_DIGITAL_PINSTATE_LOW;
  }
}


void ECLAY_DIGITAL_PullSet(
    eclay_digital_pin_t        pin,
    eclay_digital_pull_t       pull
  )
{
  if( pin < ECLAY_DIGITAL_PIN_MAX )
  {
    HRI_PORT_PullSet( coreDigitalPins[pin].port, coreDigitalPins[pin].pin, pull );
  }
  else
  {

  }
}

eclay_digital_pull_t ECLAY_DIGITAL_PullGet(
    eclay_digital_pin_t        pin
  )
{
  if( pin < ECLAY_DIGITAL_PIN_MAX )
  {
    return HRI_PORT_PullGet( coreDigitalPins[pin].port, coreDigitalPins[pin].pin );
  }
  else
  {
    return ECLAY_DIGITAL_PULL_INVALID;
  }
}
