#ifndef ECLAY_CORE_DIGITAL_H
#define ECLAY_CORE_DIGITAL_H

#include "peripheral/port/core_peripheral_port.h"

#include <stdint.h>

#include "utils/utils_increment_macro.h"
#include "utils/utils_repeat_macro.h"


typedef uint32_t  core_digital_pin_t;

typedef core_peripheral_port_direction_t  core_digital_direction_t;
#define CORE_DIGITAL_DIRECTION_INPUT    CORE_PERIPHERAL_PORT_DIRECTION_INPUT
#define CORE_DIGITAL_DIRECTION_OUTPUT   CORE_PERIPHERAL_PORT_DIRECTION_OUTPUT

typedef core_peripheral_port_pinstate_t  core_digital_pinstate_t;
#define CORE_DIGITAL_PINSTATE_LOW       CORE_PERIPHERAL_PORT_PINSTATE_LOW
#define CORE_DIGITAL_PINSTATE_HIGH      CORE_PERIPHERAL_PORT_PINSTATE_HIGH


static inline void CORE_DIGITAL_DirectionSet_pin(
    core_digital_pin_t        pin,
    core_digital_pinstate_t   state
  ) __attribute__((always_inline, unused));

void CORE_DIGITAL_DirectionSet_pin_variable(
    core_digital_pin_t        pin,
    core_digital_direction_t  direction
  );

core_digital_direction_t CORE_DIGITAL_DirectionGet_pin(
    core_digital_pin_t        pin
  );


static inline void CORE_DIGITAL_OutputSet_pin(
    core_digital_pin_t        pin,
    core_digital_pinstate_t   state
  ) __attribute__((always_inline, unused));

void CORE_DIGITAL_OutputSet_pin_variable(
    core_digital_pin_t        pin,
    core_digital_pinstate_t   state
  );


static inline void CORE_DIGITAL_OutputToggle_pin(
    core_digital_pin_t        pin
  ) __attribute__((always_inline, unused));

void CORE_DIGITAL_OutputToggle_pin_variable(
    core_digital_pin_t        pin
  );


static inline core_digital_pinstate_t CORE_DIGITAL_OutputRead_pin(
    core_digital_pin_t        pin
  ) __attribute__((always_inline, unused));

core_digital_pinstate_t CORE_DIGITAL_OutputRead_pin_variable(
    core_digital_pin_t        pin
  );


#define CORE_DIGITAL_PIN_0    NOT_A_CORE_PERIPHERAL_PORT_GROUP, 0

#define CORE_DIGITAL_PIN_1    CORE_PERIPHERAL_PORT_GROUP_PA   , 0
#define CORE_DIGITAL_PIN_2    CORE_PERIPHERAL_PORT_GROUP_PA   , 1
#define CORE_DIGITAL_PIN_3    CORE_PERIPHERAL_PORT_GROUP_PA   , 2
#define CORE_DIGITAL_PIN_4    CORE_PERIPHERAL_PORT_GROUP_PA   , 3
#define CORE_DIGITAL_PIN_5    NOT_A_CORE_PERIPHERAL_PORT_GROUP, 0
#define CORE_DIGITAL_PIN_6    NOT_A_CORE_PERIPHERAL_PORT_GROUP, 0
#define CORE_DIGITAL_PIN_7    CORE_PERIPHERAL_PORT_GROUP_PB,    8
#define CORE_DIGITAL_PIN_8    CORE_PERIPHERAL_PORT_GROUP_PB,    9
#define CORE_DIGITAL_PIN_9    CORE_PERIPHERAL_PORT_GROUP_PA,    4
#define CORE_DIGITAL_PIN_10   CORE_PERIPHERAL_PORT_GROUP_PA,    5
#define CORE_DIGITAL_PIN_11   CORE_PERIPHERAL_PORT_GROUP_PA,    6
#define CORE_DIGITAL_PIN_12   CORE_PERIPHERAL_PORT_GROUP_PA,    7

#define CORE_DIGITAL_PIN_13   CORE_PERIPHERAL_PORT_GROUP_PA,    8
#define CORE_DIGITAL_PIN_14   CORE_PERIPHERAL_PORT_GROUP_PA,    9
#define CORE_DIGITAL_PIN_15   CORE_PERIPHERAL_PORT_GROUP_PA,   10
#define CORE_DIGITAL_PIN_16   CORE_PERIPHERAL_PORT_GROUP_PA,   11
#define CORE_DIGITAL_PIN_17   NOT_A_CORE_PERIPHERAL_PORT_GROUP, 0
#define CORE_DIGITAL_PIN_18   NOT_A_CORE_PERIPHERAL_PORT_GROUP, 0
#define CORE_DIGITAL_PIN_19   CORE_PERIPHERAL_PORT_GROUP_PB,   10
#define CORE_DIGITAL_PIN_20   CORE_PERIPHERAL_PORT_GROUP_PB,   11
#define CORE_DIGITAL_PIN_21   CORE_PERIPHERAL_PORT_GROUP_PA,   12
#define CORE_DIGITAL_PIN_22   CORE_PERIPHERAL_PORT_GROUP_PA,   13
#define CORE_DIGITAL_PIN_23   CORE_PERIPHERAL_PORT_GROUP_PA,   14
#define CORE_DIGITAL_PIN_24   CORE_PERIPHERAL_PORT_GROUP_PA,   15

#define CORE_DIGITAL_PIN_25   CORE_PERIPHERAL_PORT_GROUP_PA,   16
#define CORE_DIGITAL_PIN_26   CORE_PERIPHERAL_PORT_GROUP_PA,   17
#define CORE_DIGITAL_PIN_27   CORE_PERIPHERAL_PORT_GROUP_PA,   18
#define CORE_DIGITAL_PIN_28   CORE_PERIPHERAL_PORT_GROUP_PA,   19
#define CORE_DIGITAL_PIN_29   CORE_PERIPHERAL_PORT_GROUP_PA,   20
#define CORE_DIGITAL_PIN_30   CORE_PERIPHERAL_PORT_GROUP_PA,   21
#define CORE_DIGITAL_PIN_31   CORE_PERIPHERAL_PORT_GROUP_PA,   22
#define CORE_DIGITAL_PIN_32   CORE_PERIPHERAL_PORT_GROUP_PA,   23
#define CORE_DIGITAL_PIN_33   CORE_PERIPHERAL_PORT_GROUP_PA,   24
#define CORE_DIGITAL_PIN_34   CORE_PERIPHERAL_PORT_GROUP_PA,   25
#define CORE_DIGITAL_PIN_35   NOT_A_CORE_PERIPHERAL_PORT_GROUP, 0
#define CORE_DIGITAL_PIN_36   NOT_A_CORE_PERIPHERAL_PORT_GROUP, 0

#define CORE_DIGITAL_PIN_37   CORE_PERIPHERAL_PORT_GROUP_PB,   22
#define CORE_DIGITAL_PIN_38   CORE_PERIPHERAL_PORT_GROUP_PB,   23
#define CORE_DIGITAL_PIN_39   CORE_PERIPHERAL_PORT_GROUP_PA,   27
#define CORE_DIGITAL_PIN_40   NOT_A_CORE_PERIPHERAL_PORT_GROUP, 0
#define CORE_DIGITAL_PIN_41   CORE_PERIPHERAL_PORT_GROUP_PA,   28
#define CORE_DIGITAL_PIN_42   NOT_A_CORE_PERIPHERAL_PORT_GROUP, 0
#define CORE_DIGITAL_PIN_43   NOT_A_CORE_PERIPHERAL_PORT_GROUP, 0
#define CORE_DIGITAL_PIN_44   NOT_A_CORE_PERIPHERAL_PORT_GROUP, 0
#define CORE_DIGITAL_PIN_45   CORE_PERIPHERAL_PORT_GROUP_PA,   30
#define CORE_DIGITAL_PIN_46   CORE_PERIPHERAL_PORT_GROUP_PA,   31
#define CORE_DIGITAL_PIN_47   CORE_PERIPHERAL_PORT_GROUP_PB,    2
#define CORE_DIGITAL_PIN_48   CORE_PERIPHERAL_PORT_GROUP_PB,    3

#define CORE_DIGITAL_PIN_MAX  49


#define CASE_CALL_PIN_FUNCTION_SET(function, pin)   \
    case pin:  function(CORE_DIGITAL_PIN_##pin, value);  break;

#define SWITCH_CALL_PIN_FUNCTION_SET(function, pin, value)   \ 
    switch( pin )   \ 
    {   \
      REPEAT_MACRO(CASE_CALL_PIN_FUNCTION_SET, function, CORE_DIGITAL_PIN_MAX)    \
      default:  break;    \
    }


#define CASE_CALL_PIN_FUNCTION_GET(function, pin)   \
    case pin:  return function(CORE_DIGITAL_PIN_##pin);  break;

#define SWITCH_CALL_PIN_FUNCTION_GET(function, pin)
    switch( pin )   \ 
    {   \
      REPEAT_MACRO(CASE_CALL_PIN_FUNCTION_GET, function, CORE_DIGITAL_PIN_MAX)    \
      default:  break;    \
    }


static inline void CORE_DIGITAL_DirectionSet_pin(
    core_digital_pin_t        pin,
    core_digital_direction_t  direction
  )
{
  if( __builtin_constant_p(pin) )
  {
    CALL_PIN_FUNCTION_SET( CORE_PERIPHERAL_PORT_DirectionSet_pin, pin, direction );
  }
  else
  {
    CORE_DIGITAL_DirectionSet_pin_variable( pin, direction );
  }
}

static inline void CORE_DIGITAL_OutputSet_pin(
    core_digital_pin_t        pin,
    core_digital_pinstate_t   state
  )
{
  if( __builtin_constant_p(pin) )
  {
    CALL_PIN_FUNCTION_SET( CORE_PERIPHERAL_PORT_OutputSet_pin, pin, state );
  }
  else
  {
    CORE_DIGITAL_OutputSet_pin_variable( pin, state );
  }
}

static inline void CORE_DIGITAL_OutputToggle_pin(
    core_digital_pin_t        pin
  )
{
  if( __builtin_constant_p(pin) )
  {
    CALL_PIN_FUNCTION_SET( CORE_PERIPHERAL_PORT_OutputToggle_pin, pin );
  }
  else
  {
    CORE_DIGITAL_OutputToggle_pin_variable( pin );
  }
}

#endif  // ECLAY_CORE_DIGITAL_H
