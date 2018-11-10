#ifndef ECLAY_CORE_PERIPHERAL_PORT_H
#define ECLAY_CORE_PERIPHERAL_PORT_H

#include "sam.h"

#include <stdbool.h>
#include <stdint.h>

#include "utils/utils_repeat_macro.h"


#ifdef __cplusplus
extern "C" {
#endif

typedef enum
{
  CORE_PERIPHERAL_PORT_GROUP_PA = 0,
  CORE_PERIPHERAL_PORT_GROUP_PB = 1,
  NUM_CORE_PERIPHERAL_PORT_GROUP,
  NOT_A_CORE_PERIPHERAL_PORT_GROUP = NUM_CORE_PERIPHERAL_PORT_GROUP
} core_peripheral_port_group_t;

typedef uint8_t core_peripheral_port_pin_t;
#define NUM_CORE_PERIPHERAL_PORT_PINS           32

typedef bool core_peripheral_port_direction_t;
#define CORE_PERIPHERAL_PORT_DIRECTION_INPUT    false
#define CORE_PERIPHERAL_PORT_DIRECTION_OUTPUT   true

typedef bool core_peripheral_port_pinstate_t;
#define CORE_PERIPHERAL_PORT_PINSTATE_LOW       false
#define CORE_PERIPHERAL_PORT_PINSTATE_HIGH      true

typedef enum
{
  CORE_PERIPHERAL_PORT_PULL_OFF = 0,
  CORE_PERIPHERAL_PORT_PULL_UP,
  CORE_PERIPHERAL_PORT_PULL_DOWN,
  NUM_CORE_PERIPHERAL_PORT_PULL,
  CORE_PERIPHERAL_PORT_PULL_INVALID = NUM_CORE_PERIPHERAL_PORT_PULL
} core_peripheral_port_pull_t;

typedef enum
{
  CORE_PERIPHERAL_PORT_STRENGTH_NORMAL = 0,
  CORE_PERIPHERAL_PORT_STRENGTH_HIGH,
  NUM_CORE_PERIPHERAL_PORT_STRENGTH,
  CORE_PERIPHERAL_PORT_STRENGTH_INVALID = NUM_CORE_PERIPHERAL_PORT_STRENGTH
} core_peripheral_port_strength_t;

typedef enum
{
  CORE_PERIPHERAL_PORT_PINMUX_A = PORT_PMUX_PMUXE_A_Val,
  CORE_PERIPHERAL_PORT_PINMUX_B = PORT_PMUX_PMUXE_B_Val,
  CORE_PERIPHERAL_PORT_PINMUX_C = PORT_PMUX_PMUXE_C_Val,
  CORE_PERIPHERAL_PORT_PINMUX_D = PORT_PMUX_PMUXE_D_Val,
  CORE_PERIPHERAL_PORT_PINMUX_E = PORT_PMUX_PMUXE_E_Val,
  CORE_PERIPHERAL_PORT_PINMUX_F = PORT_PMUX_PMUXE_F_Val,
  CORE_PERIPHERAL_PORT_PINMUX_G = PORT_PMUX_PMUXE_G_Val,
  CORE_PERIPHERAL_PORT_PINMUX_H = PORT_PMUX_PMUXE_H_Val,
  NUM_CORE_PERIPHERAL_PORT_PINMUX,
  CORE_PERIPHERAL_PORT_PINMUX_DISABLED = NUM_CORE_PERIPHERAL_PORT_PINMUX
} core_peripheral_port_pinmux_t;


static inline void CORE_PERIPHERAL_PORT_DirectionSet(
    core_peripheral_port_group_t      port,
    core_peripheral_port_pin_t        pin,
    core_peripheral_port_direction_t  direction
  ) __attribute__((always_inline, unused));

void CORE_PERIPHERAL_PORT_DirectionSet_noinline(
    core_peripheral_port_group_t      port,
    core_peripheral_port_pin_t        pin,
    core_peripheral_port_direction_t  direction
  );

static inline core_peripheral_port_direction_t CORE_PERIPHERAL_PORT_DirectionGet(
    core_peripheral_port_group_t      port,
    core_peripheral_port_pin_t        pin
  ) __attribute__((always_inline, unused));

core_peripheral_port_direction_t CORE_PERIPHERAL_PORT_DirectionGet_noinline(
    core_peripheral_port_group_t      port,
    core_peripheral_port_pin_t        pin
  );


static inline void CORE_PERIPHERAL_PORT_OutputSet(
    core_peripheral_port_group_t      port,
    core_peripheral_port_pin_t        pin,
    core_peripheral_port_pinstate_t   state
  ) __attribute__((always_inline, unused));

void CORE_PERIPHERAL_PORT_OutputSet_noinline(
    core_peripheral_port_group_t      port,
    core_peripheral_port_pin_t        pin,
    core_peripheral_port_pinstate_t   state
  );

static inline void CORE_PERIPHERAL_PORT_OutputToggle(
    core_peripheral_port_group_t      port,
    core_peripheral_port_pin_t        pin
  ) __attribute__((always_inline, unused));

void CORE_PERIPHERAL_PORT_OutputToggle_noinline(
    core_peripheral_port_group_t      port,
    core_peripheral_port_pin_t        pin
  );

static inline core_peripheral_port_pinstate_t CORE_PERIPHERAL_PORT_OutputGet(
    core_peripheral_port_group_t      port,
    core_peripheral_port_pin_t        pin
  ) __attribute__((always_inline, unused));

core_peripheral_port_pinstate_t CORE_PERIPHERAL_PORT_OutputGet_noinline(
    core_peripheral_port_group_t      port,
    core_peripheral_port_pin_t        pin
  );


static inline core_peripheral_port_pinstate_t CORE_PERIPHERAL_PORT_InputGet(
    core_peripheral_port_group_t      port,
    core_peripheral_port_pin_t        pin
  ) __attribute__((always_inline, unused));

core_peripheral_port_pinstate_t CORE_PERIPHERAL_PORT_InputGet_noinline(
    core_peripheral_port_group_t      port,
    core_peripheral_port_pin_t        pin
  );


void CORE_PERIPHERAL_PORT_InputEnableSet(
    core_peripheral_port_group_t      port,
    core_peripheral_port_pin_t        pin,
    bool                              enable
  );

bool CORE_PERIPHERAL_PORT_InputEnableGet(
    core_peripheral_port_group_t      port,
    core_peripheral_port_pin_t        pin
  );


void CORE_PERIPHERAL_PORT_PullSet(
    core_peripheral_port_group_t      port,
    core_peripheral_port_pin_t        pin,
    core_peripheral_port_pull_t       pull
  );

core_peripheral_port_pull_t CORE_PERIPHERAL_PORT_PullGet(
    core_peripheral_port_group_t      port,
    core_peripheral_port_pin_t        pin
  );


void CORE_PERIPHERAL_PORT_DriveStrengthSet(
    core_peripheral_port_group_t      port,
    core_peripheral_port_pin_t        pin,
    core_peripheral_port_strength_t   strength
  );

core_peripheral_port_strength_t CORE_PERIPHERAL_PORT_DriveStrengthGet(
    core_peripheral_port_group_t      port,
    core_peripheral_port_pin_t        pin
  );


void CORE_PERIPHERAL_PORT_PinMuxSet(
    core_peripheral_port_group_t      port,
    core_peripheral_port_pin_t        pin,
    core_peripheral_port_pinmux_t     mux
  );

core_peripheral_port_pinmux_t CORE_PERIPHERAL_PORT_PinMuxGet(
    core_peripheral_port_group_t      port,
    core_peripheral_port_pin_t        pin
  );

// REG_PORT_IOBUS registers not defined in SAMD21 package.  Use following
//   macro to calculate correct address of IOBUS registers.
#define REG_PORT_IOBUS(reg_port)  (*((RwReg  *)PORT_IOBUS + (&reg_port - (RwReg  *)PORT)))

#define CASE_PIN_WRITE_REG_PINMASK(register, pin)           \
    case pin: REG_PORT_IOBUS(REG_PORT_##register) = (_UL_(1) <<  pin);  break;

#define SWITCH_PIN_WRITE_REG_PINMASK(register, pin)         \
    switch( pin )                                           \
    {                                                       \
      REPEAT_MACRO(CASE_PIN_WRITE_REG_PINMASK, register, NUM_CORE_PERIPHERAL_PORT_PINS)      \
      default:  break;                                      \
    }

#define SWITCH_PORT_WRITE_REG_PINMASK(port, register, pin)  \
    switch( port )                                          \
    {                                                       \
      case CORE_PERIPHERAL_PORT_GROUP_PA:                   \
        SWITCH_PIN_WRITE_REG_PINMASK( register##0, pin )    \
        break;                                              \
      case CORE_PERIPHERAL_PORT_GROUP_PB:                   \
        SWITCH_PIN_WRITE_REG_PINMASK( register##1, pin )    \
        break;                                              \
      default:                                              \
        break;                                              \
    }


#define CASE_PIN_READ_REG_PINMASK(register, pin)              \
    case pin: return (REG_PORT_IOBUS(REG_PORT_##register) & (_UL_(1) <<  pin)) != 0;

#define SWITCH_PIN_READ_REG_PINMASK(register, pin)            \
    switch( pin )                                             \
    {                                                         \
      REPEAT_MACRO(CASE_PIN_READ_REG_PINMASK, register, NUM_CORE_PERIPHERAL_PORT_PINS)   \
      default:  return false;                                 \
    }

#define SWITCH_PORT_READ_REG_PINMASK(port, register, pin)     \
    switch( port )                                            \
    {                                                         \
      case CORE_PERIPHERAL_PORT_GROUP_PA:                     \
        SWITCH_PIN_READ_REG_PINMASK( register##0, pin )       \
      case CORE_PERIPHERAL_PORT_GROUP_PB:                     \
        SWITCH_PIN_READ_REG_PINMASK( register##1, pin )       \
      default:                                                \
        return false;                                         \
    }


static inline void CORE_PERIPHERAL_PORT_DirectionSet(
    core_peripheral_port_group_t      port,
    core_peripheral_port_pin_t        pin,
    core_peripheral_port_direction_t  direction
  )
{
  if( __builtin_constant_p(port) && __builtin_constant_p(pin) )
  {
    if( direction )
    { 
      SWITCH_PORT_WRITE_REG_PINMASK( port, DIRSET, pin )
    }
    else
    {
      SWITCH_PORT_WRITE_REG_PINMASK( port, DIRCLR, pin )
    }
  }
  else
  {
    CORE_PERIPHERAL_PORT_DirectionSet_noinline(port, pin, direction);
  }
}

static inline core_peripheral_port_direction_t CORE_PERIPHERAL_PORT_DirectionGet(
    core_peripheral_port_group_t      port,
    core_peripheral_port_pin_t        pin
  )
{
  if( __builtin_constant_p(port) && __builtin_constant_p(pin) )
  {
    SWITCH_PORT_READ_REG_PINMASK( port, DIR, pin )
  }
  else
  {
    return CORE_PERIPHERAL_PORT_DirectionGet_noinline( port, pin );                       \
  }
}


static inline void CORE_PERIPHERAL_PORT_OutputSet(
    core_peripheral_port_group_t      port,
    core_peripheral_port_pin_t        pin,
    core_peripheral_port_pinstate_t   state
  )
{
  if( __builtin_constant_p(port) && __builtin_constant_p(pin) )
  {
    if( state )
    { 
      SWITCH_PORT_WRITE_REG_PINMASK( port, OUTSET, pin )
    }
    else
    {
      SWITCH_PORT_WRITE_REG_PINMASK( port, OUTCLR, pin )
    }
  }
  else
  {
    CORE_PERIPHERAL_PORT_OutputSet_noinline( port, pin, state );
  }
}

static inline void CORE_PERIPHERAL_PORT_OutputToggle(
    core_peripheral_port_group_t      port,
    core_peripheral_port_pin_t        pin
  )
{
  if( __builtin_constant_p(port) && __builtin_constant_p(pin) )
  {
    SWITCH_PORT_WRITE_REG_PINMASK( port, OUTTGL, pin )
  }
  else
  {
    CORE_PERIPHERAL_PORT_OutputToggle_noinline( port, pin );
  }
}

static inline core_peripheral_port_pinstate_t CORE_PERIPHERAL_PORT_OutputGet(
    core_peripheral_port_group_t      port,
    core_peripheral_port_pin_t        pin
  )
{
  if( __builtin_constant_p(port) && __builtin_constant_p(pin) )
  {
    SWITCH_PORT_READ_REG_PINMASK( port, OUT, pin )
  }
  else
  {
    return CORE_PERIPHERAL_PORT_OutputGet_noinline( port, pin );                       \
  }
}


static inline core_peripheral_port_pinstate_t CORE_PERIPHERAL_PORT_InputGet(
    core_peripheral_port_group_t      port,
    core_peripheral_port_pin_t        pin
  )
{
  if( __builtin_constant_p(port) && __builtin_constant_p(pin) )
  {
    SWITCH_PORT_READ_REG_PINMASK( port, IN, pin )
  }
  else
  {
    return CORE_PERIPHERAL_PORT_InputGet_noinline(port, pin);
  }
}


#ifdef __cplusplus
}
#endif

#endif  // ECLAY_CORE_PERIPHERAL_PORT_H
