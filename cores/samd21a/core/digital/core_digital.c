#include "core/digital.h"

#include "processor/port.h"

#include "processor/sam.h"

#include "utils/utils_repeat_macro.h"


typedef struct
{
  processor_port_group_t port;
  processor_port_pin_t   pin;
} core_digital_pin_definition_t;

#define CORE_DIGITAL_PIN_DEFINITION(noarg, pin)   { CORE_DIGITAL_PIN_##pin },

static const core_digital_pin_definition_t coreDigitalPins[] =
{
  REPEAT_MACRO(CORE_DIGITAL_PIN_DEFINITION, 0, CORE_DIGITAL_PIN_MAX)
};


void CORE_DIGITAL_DirectionSet_noinline(
    core_digital_pin_t        pin,
    core_digital_direction_t  direction
  )
{
  if( pin < CORE_DIGITAL_PIN_MAX )
  {
    PROCESSOR_PORT_DirectionSet( coreDigitalPins[pin].port, coreDigitalPins[pin].pin, direction );

    // Always enable input reads for digital pins
    PROCESSOR_PORT_InputEnableSet( coreDigitalPins[pin].port, coreDigitalPins[pin].pin, true );
  }
  else
  {

  }
}

core_digital_direction_t CORE_DIGITAL_DirectionGet_noinline(
    core_digital_pin_t        pin
  )
{
  if( pin < CORE_DIGITAL_PIN_MAX )
  {
    return PROCESSOR_PORT_DirectionGet( coreDigitalPins[pin].port, coreDigitalPins[pin].pin );
  }
  else
  {
    return CORE_DIGITAL_DIRECTION_INPUT;
  }
}


void CORE_DIGITAL_OutputSet_noinline(
    core_digital_pin_t        pin,
    core_digital_pinstate_t   state
  )
{
  if( pin < CORE_DIGITAL_PIN_MAX )
  {
    PROCESSOR_PORT_OutputSet( coreDigitalPins[pin].port, coreDigitalPins[pin].pin, state );
  }
  else
  {

  }
}

void CORE_DIGITAL_OutputToggle_noinline(
    core_digital_pin_t        pin
  )
{
  if( pin < CORE_DIGITAL_PIN_MAX )
  {
    PROCESSOR_PORT_OutputToggle( coreDigitalPins[pin].port, coreDigitalPins[pin].pin );
  }
  else
  {

  }
}

core_digital_pinstate_t CORE_DIGITAL_OutputGet_noinline(
    core_digital_pin_t        pin
  )
{
  if( pin < CORE_DIGITAL_PIN_MAX )
  {
    return PROCESSOR_PORT_OutputGet( coreDigitalPins[pin].port, coreDigitalPins[pin].pin );
  }
  else
  {
    return CORE_DIGITAL_PINSTATE_LOW;
  }
}


core_digital_pinstate_t CORE_DIGITAL_InputGet_noinline(
    core_digital_pin_t        pin
  )
{
  if( pin < CORE_DIGITAL_PIN_MAX )
  {
    return PROCESSOR_PORT_InputGet( coreDigitalPins[pin].port, coreDigitalPins[pin].pin );
  }
  else
  {
    return CORE_DIGITAL_PINSTATE_LOW;
  }
}


void CORE_DIGITAL_PullSet(
    core_digital_pin_t        pin,
    core_digital_pull_t       pull
  )
{
  if( pin < CORE_DIGITAL_PIN_MAX )
  {
    PROCESSOR_PORT_PullSet( coreDigitalPins[pin].port, coreDigitalPins[pin].pin, pull );
  }
  else
  {

  }
}

core_digital_pull_t CORE_DIGITAL_PullGet(
    core_digital_pin_t        pin
  )
{
  if( pin < CORE_DIGITAL_PIN_MAX )
  {
    return PROCESSOR_PORT_PullGet( coreDigitalPins[pin].port, coreDigitalPins[pin].pin );
  }
  else
  {
    return CORE_DIGITAL_PULL_INVALID;
  }
}
