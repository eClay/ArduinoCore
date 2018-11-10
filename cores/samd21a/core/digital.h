#ifndef ECLAY_CORE_DIGITAL_H
#define ECLAY_CORE_DIGITAL_H

#include "processor/port.h"

#include <stdbool.h>
#include <stdint.h>

#include "utils/utils_repeat_macro.h"


#ifdef __cplusplus
extern "C" {
#endif

typedef uint32_t  core_digital_pin_t;

typedef processor_port_direction_t      core_digital_direction_t;
#define CORE_DIGITAL_DIRECTION_INPUT    PROCESSOR_PORT_DIRECTION_INPUT
#define CORE_DIGITAL_DIRECTION_OUTPUT   PROCESSOR_PORT_DIRECTION_OUTPUT

typedef processor_port_pinstate_t       core_digital_pinstate_t;
#define CORE_DIGITAL_PINSTATE_LOW       PROCESSOR_PORT_PINSTATE_LOW
#define CORE_DIGITAL_PINSTATE_HIGH      PROCESSOR_PORT_PINSTATE_HIGH

typedef processor_port_pull_t           core_digital_pull_t;
#define CORE_DIGITAL_PULL_OFF           PROCESSOR_PORT_PULL_OFF
#define CORE_DIGITAL_PULL_UP            PROCESSOR_PORT_PULL_UP
#define CORE_DIGITAL_PULL_DOWN          PROCESSOR_PORT_PULL_DOWN
#define CORE_DIGITAL_PULL_INVALID       PROCESSOR_PORT_PULL_INVALID


static inline void CORE_DIGITAL_DirectionSet(
    core_digital_pin_t        pin,
    core_digital_direction_t  direction
  ) __attribute__((always_inline, unused));

void CORE_DIGITAL_DirectionSet_noinline(
    core_digital_pin_t        pin,
    core_digital_direction_t  direction
  );

static inline core_digital_direction_t CORE_DIGITAL_DirectionGet(
    core_digital_pin_t        pin
  ) __attribute__((always_inline, unused));

core_digital_direction_t CORE_DIGITAL_DirectionGet_noinline(
    core_digital_pin_t        pin
  );


static inline void CORE_DIGITAL_OutputSet(
    core_digital_pin_t        pin,
    core_digital_pinstate_t   state
  ) __attribute__((always_inline, unused));

void CORE_DIGITAL_OutputSet_noinline(
    core_digital_pin_t        pin,
    core_digital_pinstate_t   state
  );

static inline void CORE_DIGITAL_OutputToggle(
    core_digital_pin_t        pin
  ) __attribute__((always_inline, unused));

void CORE_DIGITAL_OutputToggle_noinline(
    core_digital_pin_t        pin
  );

static inline core_digital_pinstate_t CORE_DIGITAL_OutputGet(
    core_digital_pin_t        pin
  ) __attribute__((always_inline, unused));

core_digital_pinstate_t CORE_DIGITAL_OutputGet_noinline(
    core_digital_pin_t        pin
  );


static inline core_digital_pinstate_t CORE_DIGITAL_InputGet(
    core_digital_pin_t        pin
  ) __attribute__((always_inline, unused));

core_digital_pinstate_t CORE_DIGITAL_InputGet_noinline(
    core_digital_pin_t        pin
  );


void CORE_DIGITAL_PullSet(
    core_digital_pin_t        pin,
    core_digital_pull_t       pull
  );

core_digital_pull_t CORE_DIGITAL_PullGet(
    core_digital_pin_t        pin
  );


#define CORE_DIGITAL_PIN_0    NOT_A_PROCESSOR_PORT_GROUP, 0

#define CORE_DIGITAL_PIN_1    PROCESSOR_PORT_GROUP_PA   , 0
#define CORE_DIGITAL_PIN_2    PROCESSOR_PORT_GROUP_PA   , 1
#define CORE_DIGITAL_PIN_3    PROCESSOR_PORT_GROUP_PA   , 2
#define CORE_DIGITAL_PIN_4    PROCESSOR_PORT_GROUP_PA   , 3
#define CORE_DIGITAL_PIN_5    NOT_A_PROCESSOR_PORT_GROUP, 0
#define CORE_DIGITAL_PIN_6    NOT_A_PROCESSOR_PORT_GROUP, 0
#define CORE_DIGITAL_PIN_7    PROCESSOR_PORT_GROUP_PB,    8
#define CORE_DIGITAL_PIN_8    PROCESSOR_PORT_GROUP_PB,    9
#define CORE_DIGITAL_PIN_9    PROCESSOR_PORT_GROUP_PA,    4
#define CORE_DIGITAL_PIN_10   PROCESSOR_PORT_GROUP_PA,    5
#define CORE_DIGITAL_PIN_11   PROCESSOR_PORT_GROUP_PA,    6
#define CORE_DIGITAL_PIN_12   PROCESSOR_PORT_GROUP_PA,    7

#define CORE_DIGITAL_PIN_13   PROCESSOR_PORT_GROUP_PA,    8
#define CORE_DIGITAL_PIN_14   PROCESSOR_PORT_GROUP_PA,    9
#define CORE_DIGITAL_PIN_15   PROCESSOR_PORT_GROUP_PA,   10
#define CORE_DIGITAL_PIN_16   PROCESSOR_PORT_GROUP_PA,   11
#define CORE_DIGITAL_PIN_17   NOT_A_PROCESSOR_PORT_GROUP, 0
#define CORE_DIGITAL_PIN_18   NOT_A_PROCESSOR_PORT_GROUP, 0
#define CORE_DIGITAL_PIN_19   PROCESSOR_PORT_GROUP_PB,   10
#define CORE_DIGITAL_PIN_20   PROCESSOR_PORT_GROUP_PB,   11
#define CORE_DIGITAL_PIN_21   PROCESSOR_PORT_GROUP_PA,   12
#define CORE_DIGITAL_PIN_22   PROCESSOR_PORT_GROUP_PA,   13
#define CORE_DIGITAL_PIN_23   PROCESSOR_PORT_GROUP_PA,   14
#define CORE_DIGITAL_PIN_24   PROCESSOR_PORT_GROUP_PA,   15

#define CORE_DIGITAL_PIN_25   PROCESSOR_PORT_GROUP_PA,   16
#define CORE_DIGITAL_PIN_26   PROCESSOR_PORT_GROUP_PA,   17
#define CORE_DIGITAL_PIN_27   PROCESSOR_PORT_GROUP_PA,   18
#define CORE_DIGITAL_PIN_28   PROCESSOR_PORT_GROUP_PA,   19
#define CORE_DIGITAL_PIN_29   PROCESSOR_PORT_GROUP_PA,   20
#define CORE_DIGITAL_PIN_30   PROCESSOR_PORT_GROUP_PA,   21
#define CORE_DIGITAL_PIN_31   PROCESSOR_PORT_GROUP_PA,   22
#define CORE_DIGITAL_PIN_32   PROCESSOR_PORT_GROUP_PA,   23
#define CORE_DIGITAL_PIN_33   PROCESSOR_PORT_GROUP_PA,   24
#define CORE_DIGITAL_PIN_34   PROCESSOR_PORT_GROUP_PA,   25
#define CORE_DIGITAL_PIN_35   NOT_A_PROCESSOR_PORT_GROUP, 0
#define CORE_DIGITAL_PIN_36   NOT_A_PROCESSOR_PORT_GROUP, 0

#define CORE_DIGITAL_PIN_37   PROCESSOR_PORT_GROUP_PB,   22
#define CORE_DIGITAL_PIN_38   PROCESSOR_PORT_GROUP_PB,   23
#define CORE_DIGITAL_PIN_39   PROCESSOR_PORT_GROUP_PA,   27
#define CORE_DIGITAL_PIN_40   NOT_A_PROCESSOR_PORT_GROUP, 0
#define CORE_DIGITAL_PIN_41   PROCESSOR_PORT_GROUP_PA,   28
#define CORE_DIGITAL_PIN_42   NOT_A_PROCESSOR_PORT_GROUP, 0
#define CORE_DIGITAL_PIN_43   NOT_A_PROCESSOR_PORT_GROUP, 0
#define CORE_DIGITAL_PIN_44   NOT_A_PROCESSOR_PORT_GROUP, 0
#define CORE_DIGITAL_PIN_45   PROCESSOR_PORT_GROUP_PA,   30
#define CORE_DIGITAL_PIN_46   PROCESSOR_PORT_GROUP_PA,   31
#define CORE_DIGITAL_PIN_47   PROCESSOR_PORT_GROUP_PB,    2
#define CORE_DIGITAL_PIN_48   PROCESSOR_PORT_GROUP_PB,    3

#define CORE_DIGITAL_PIN_MAX  49


#define CASE_CALL_PIN_FUNCTION(function, pin)   \
    case pin:  function(CORE_DIGITAL_PIN_##pin);  break;

#define SWITCH_CALL_PIN_FUNCTION(case_function, pin, default_function)  \
    switch( pin )   \
    {   \
      REPEAT_MACRO(CASE_CALL_PIN_FUNCTION, case_function, CORE_DIGITAL_PIN_MAX)    \
      default:  default_function(pin);  break;   \
    }


#define CASE_CALL_PIN_FUNCTION_SET_FALSE(function, pin)   \
    case pin:  function(CORE_DIGITAL_PIN_##pin, false);  break;

#define SWITCH_CALL_PIN_FUNCTION_SET_FALSE(case_function, pin, default_function)  \
    switch( pin )   \
    {   \
      REPEAT_MACRO(CASE_CALL_PIN_FUNCTION_SET_FALSE, case_function, CORE_DIGITAL_PIN_MAX)    \
      default:  default_function(pin, false);  break;  \
    }


#define CASE_CALL_PIN_FUNCTION_SET_TRUE(function, pin)   \
    case pin:  function(CORE_DIGITAL_PIN_##pin, true);  break;

#define SWITCH_CALL_PIN_FUNCTION_SET_TRUE(case_function, pin, default_function)  \
    switch( pin )   \
    {   \
      REPEAT_MACRO(CASE_CALL_PIN_FUNCTION_SET_TRUE, case_function, CORE_DIGITAL_PIN_MAX)    \
      default:  default_function(pin, true);  break;  \
    }


#define CASE_CALL_PIN_FUNCTION_SET_VALUE(function, pin)   \
    case pin:  function(CORE_DIGITAL_PIN_##pin, value);  break;

#define SWITCH_CALL_PIN_FUNCTION_SET_VALUE(case_function, pin, default_function)  \
    switch( pin )   \
    {   \
      REPEAT_MACRO(CASE_CALL_PIN_FUNCTION_SET_VALUE, case_function, CORE_DIGITAL_PIN_MAX)    \
      default:  default_function(pin, value);  break;\
    }


#define CASE_CALL_PIN_FUNCTION_GET(function, pin)   \
    case pin:  return function(CORE_DIGITAL_PIN_##pin);

#define SWITCH_CALL_PIN_FUNCTION_GET(case_function, pin, default_function) \
    switch( pin )   \ 
    {   \
      REPEAT_MACRO(CASE_CALL_PIN_FUNCTION_GET, case_function, CORE_DIGITAL_PIN_MAX)    \
      default:  return default_function(pin);    \
    }


static inline void CORE_DIGITAL_EmptyFunction_pin_direction( 
    core_digital_pin_t        pin,
    core_digital_direction_t  value
  )
{  
}


static inline void CORE_DIGITAL_DirectionSet(
    core_digital_pin_t        pin,
    core_digital_direction_t  value
  )
{
  if( __builtin_constant_p(pin) )
  {
    SWITCH_CALL_PIN_FUNCTION_SET_VALUE( PROCESSOR_PORT_DirectionSet, pin, CORE_DIGITAL_DirectionSet_noinline );
    SWITCH_CALL_PIN_FUNCTION_SET_TRUE( PROCESSOR_PORT_InputEnableSet, pin, CORE_DIGITAL_EmptyFunction_pin_direction );
  }
  else
  {
    CORE_DIGITAL_DirectionSet_noinline( pin, value );
  }
}

static inline core_digital_direction_t CORE_DIGITAL_DirectionGet(
    core_digital_pin_t        pin
  )
{
  if( __builtin_constant_p(pin) )
  {
    SWITCH_CALL_PIN_FUNCTION_GET( PROCESSOR_PORT_DirectionGet, pin, CORE_DIGITAL_DirectionGet_noinline );
  }
  else
  {
    return CORE_DIGITAL_DirectionGet_noinline( pin );
  }
}


static inline void CORE_DIGITAL_OutputSet(
    core_digital_pin_t        pin,
    core_digital_pinstate_t   value
  )
{
  if( __builtin_constant_p(pin) )
  {
    SWITCH_CALL_PIN_FUNCTION_SET_VALUE( PROCESSOR_PORT_OutputSet, pin, CORE_DIGITAL_OutputSet_noinline );
  }
  else
  {
    CORE_DIGITAL_OutputSet_noinline( pin, value );
  }
}

static inline void CORE_DIGITAL_OutputToggle(
    core_digital_pin_t        pin
  )
{
  if( __builtin_constant_p(pin) )
  {
    SWITCH_CALL_PIN_FUNCTION( PROCESSOR_PORT_OutputToggle, pin, CORE_DIGITAL_OutputToggle_noinline );
  }
  else
  {
    CORE_DIGITAL_OutputToggle_noinline( pin );
  }
}

static inline core_digital_pinstate_t CORE_DIGITAL_OutputGet(
    core_digital_pin_t        pin
  )
{
  if( __builtin_constant_p(pin) )
  {
    SWITCH_CALL_PIN_FUNCTION_GET( PROCESSOR_PORT_OutputGet, pin, CORE_DIGITAL_OutputGet_noinline );
  }
  else
  {
    return CORE_DIGITAL_OutputGet_noinline( pin );
  }
}


static inline core_digital_pinstate_t CORE_DIGITAL_InputGet(
    core_digital_pin_t        pin
  )
{
  if( __builtin_constant_p(pin) )
  {
    SWITCH_CALL_PIN_FUNCTION_GET( PROCESSOR_PORT_InputGet, pin, CORE_DIGITAL_InputGet_noinline );
  }
  else
  {
    return CORE_DIGITAL_InputGet_noinline( pin );
  }
}


#ifdef __cplusplus
}
#endif

#endif  // ECLAY_CORE_DIGITAL_H
