#include "core/digital.h"

#include "core/peripheral/port.h"

#include "sam.h"

#include "utils/utils_repeat_macro.h"


typedef struct
{
  core_peripheral_port_group_t port;
  core_peripheral_port_pin_t   pin;
} core_digital_pin_definition_t;

#define CORE_DIGITAL_PIN_DEFINITION(noarg, pin)   { CORE_DIGITAL_PIN_##pin },

static const core_digital_pin_definition_t coreDigitalPins[] =
{
  REPEAT_MACRO(CORE_DIGITAL_PIN_DEFINITION, 0, CORE_DIGITAL_PIN_MAX)

  // { CORE_DIGITAL_PIN_0 },  // Pin 0  - No pin

  // { CORE_PERIPHERAL_PORT_GROUP_PA,    0 },  // Pin 1  - PA00
  // { CORE_PERIPHERAL_PORT_GROUP_PA,    1 },  // Pin 2  - PA01
  // { CORE_PERIPHERAL_PORT_GROUP_PA,    2 },  // Pin 3  - PA02
  // { CORE_PERIPHERAL_PORT_GROUP_PA,    3 },  // Pin 4  - PA03
  // { NOT_A_CORE_PERIPHERAL_PORT_GROUP, 0 },  // Pin 5  - GNDANA
  // { NOT_A_CORE_PERIPHERAL_PORT_GROUP, 0 },  // Pin 6  - VDDANA
  // { CORE_PERIPHERAL_PORT_GROUP_PB,    8 },  // Pin 7  - PB08
  // { CORE_PERIPHERAL_PORT_GROUP_PB,    9 },  // Pin 8  - PB09
  // { CORE_PERIPHERAL_PORT_GROUP_PA,    4 },  // Pin 9  - PA04
  // { CORE_PERIPHERAL_PORT_GROUP_PA,    5 },  // Pin 10 - PA05
  // { CORE_PERIPHERAL_PORT_GROUP_PA,    6 },  // Pin 11 - PA06
  // { CORE_PERIPHERAL_PORT_GROUP_PA,    7 },  // Pin 12 - PA07

  // { CORE_PERIPHERAL_PORT_GROUP_PA,    8 },  // Pin 13 - PA08
  // { CORE_PERIPHERAL_PORT_GROUP_PA,    9 },  // Pin 14 - PA09
  // { CORE_PERIPHERAL_PORT_GROUP_PA,   10 },  // Pin 15 - PA10
  // { CORE_PERIPHERAL_PORT_GROUP_PA,   11 },  // Pin 16 - PA11
  // { NOT_A_CORE_PERIPHERAL_PORT_GROUP, 0 },  // Pin 17 - VDDIO
  // { NOT_A_CORE_PERIPHERAL_PORT_GROUP, 0 },  // Pin 18 - GND
  // { CORE_PERIPHERAL_PORT_GROUP_PB,   10 },  // Pin 19 - PB10
  // { CORE_PERIPHERAL_PORT_GROUP_PB,   11 },  // Pin 20 - PB11
  // { CORE_PERIPHERAL_PORT_GROUP_PA,   12 },  // Pin 21 - PA12
  // { CORE_PERIPHERAL_PORT_GROUP_PA,   13 },  // Pin 22 - PA13
  // { CORE_PERIPHERAL_PORT_GROUP_PA,   14 },  // Pin 23 - PA14
  // { CORE_PERIPHERAL_PORT_GROUP_PA,   15 },  // Pin 24 - PA15

  // { CORE_PERIPHERAL_PORT_GROUP_PA,   16 },  // Pin 25 - PA16
  // { CORE_PERIPHERAL_PORT_GROUP_PA,   17 },  // Pin 26 - PA17
  // { CORE_PERIPHERAL_PORT_GROUP_PA,   18 },  // Pin 27 - PA18
  // { CORE_PERIPHERAL_PORT_GROUP_PA,   19 },  // Pin 28 - PA19
  // { CORE_PERIPHERAL_PORT_GROUP_PA,   20 },  // Pin 29 - PA20
  // { CORE_PERIPHERAL_PORT_GROUP_PA,   21 },  // Pin 30 - PA21
  // { CORE_PERIPHERAL_PORT_GROUP_PA,   22 },  // Pin 31 - PA22
  // { CORE_PERIPHERAL_PORT_GROUP_PA,   23 },  // Pin 32 - PA23
  // { CORE_PERIPHERAL_PORT_GROUP_PA,   24 },  // Pin 33 - PA24
  // { CORE_PERIPHERAL_PORT_GROUP_PA,   25 },  // Pin 34 - PA25
  // { NOT_A_CORE_PERIPHERAL_PORT_GROUP, 0 },  // Pin 35 - GND
  // { NOT_A_CORE_PERIPHERAL_PORT_GROUP, 0 },  // Pin 36 - VDDIO

  // { CORE_PERIPHERAL_PORT_GROUP_PB,   22 },  // Pin 37 - PB22
  // { CORE_PERIPHERAL_PORT_GROUP_PB,   23 },  // Pin 38 - PB23
  // { CORE_PERIPHERAL_PORT_GROUP_PA,   27 },  // Pin 39 - PA27
  // { NOT_A_CORE_PERIPHERAL_PORT_GROUP, 0 },  // Pin 40 - !RESET
  // { CORE_PERIPHERAL_PORT_GROUP_PA,   28 },  // Pin 41 - PA28
  // { NOT_A_CORE_PERIPHERAL_PORT_GROUP, 0 },  // Pin 42 - GND
  // { NOT_A_CORE_PERIPHERAL_PORT_GROUP, 0 },  // Pin 43 - VDDCORE
  // { NOT_A_CORE_PERIPHERAL_PORT_GROUP, 0 },  // Pin 44 - VDDIN
  // { CORE_PERIPHERAL_PORT_GROUP_PA,   30 },  // Pin 45 - PA30
  // { CORE_PERIPHERAL_PORT_GROUP_PA,   31 },  // Pin 46 - PA31
  // { CORE_PERIPHERAL_PORT_GROUP_PB,    2 },  // Pin 47 - PB02
  // { CORE_PERIPHERAL_PORT_GROUP_PB,    3 },  // Pin 48 - PB03
};


#define NO_RETURN_VALUE

#define RANGE_CHECK_PIN_PARAMETER(pin, rtnval)    \
  if( pin  >= CORE_DIGITAL_PIN_MAX )              \
  {                                               \
    return rtnval;                                \
  }


void CORE_DIGITAL_DirectionSet_noinline(
    core_digital_pin_t        pin,
    core_digital_direction_t  direction
  )
{
  RANGE_CHECK_PIN_PARAMETER( pin, NO_RETURN_VALUE );

  CORE_PERIPHERAL_PORT_DirectionSet( coreDigitalPins[pin].port, coreDigitalPins[pin].pin, direction );

  // Always enable input reads for digital pins
  CORE_PERIPHERAL_PORT_InputEnableSet( coreDigitalPins[pin].port, coreDigitalPins[pin].pin, true );
}

core_digital_direction_t CORE_DIGITAL_DirectionGet_noinline(
    core_digital_pin_t        pin
  )
{
  RANGE_CHECK_PIN_PARAMETER( pin, CORE_DIGITAL_DIRECTION_INPUT );

  return CORE_PERIPHERAL_PORT_DirectionGet( coreDigitalPins[pin].port, coreDigitalPins[pin].pin );
}


void CORE_DIGITAL_OutputSet_noinline(
    core_digital_pin_t        pin,
    core_digital_pinstate_t   state
  )
{
  RANGE_CHECK_PIN_PARAMETER( pin, NO_RETURN_VALUE );

  CORE_PERIPHERAL_PORT_OutputSet( coreDigitalPins[pin].port, coreDigitalPins[pin].pin, state );
}

void CORE_DIGITAL_OutputToggle_noinline(
    core_digital_pin_t        pin
  )
{
  RANGE_CHECK_PIN_PARAMETER( pin, NO_RETURN_VALUE );

  CORE_PERIPHERAL_PORT_OutputToggle( coreDigitalPins[pin].port, coreDigitalPins[pin].pin );
}

core_digital_pinstate_t CORE_DIGITAL_OutputGet_noinline(
    core_digital_pin_t        pin
  )
{
  RANGE_CHECK_PIN_PARAMETER( pin, CORE_DIGITAL_PINSTATE_LOW );

  return CORE_PERIPHERAL_PORT_OutputGet( coreDigitalPins[pin].port, coreDigitalPins[pin].pin );
}


core_digital_pinstate_t CORE_DIGITAL_InputGet_noinline(
    core_digital_pin_t        pin
  )
{
  RANGE_CHECK_PIN_PARAMETER( pin, CORE_DIGITAL_PINSTATE_LOW );

  return CORE_PERIPHERAL_PORT_InputGet( coreDigitalPins[pin].port, coreDigitalPins[pin].pin );
}


void CORE_DIGITAL_PullSet(
    core_digital_pin_t        pin,
    core_digital_pull_t       pull
  )
{
  RANGE_CHECK_PIN_PARAMETER( pin, NO_RETURN_VALUE );

  CORE_PERIPHERAL_PORT_PullSet( coreDigitalPins[pin].port, coreDigitalPins[pin].pin, pull );
}

core_digital_pull_t CORE_DIGITAL_PullGet(
    core_digital_pin_t        pin
  )
{
  RANGE_CHECK_PIN_PARAMETER( pin, CORE_DIGITAL_PULL_INVALID );

  return CORE_PERIPHERAL_PORT_PullGet( coreDigitalPins[pin].port, coreDigitalPins[pin].pin );
}
