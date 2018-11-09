#include "core_peripheral_port.h"

#include "arduino/A_Digital.h"

#include "arduino/A_Math.h"
#include "arduino/A_Types.h"

#include "sam.h"


#ifdef __cplusplus
 extern "C" {
#endif


#define RANGE_CHECK_PORT_PIN_PARAMETERS(port, pin)   \
  if( (port >= NOT_A_CORE_PERIPHERAL_PORT_GROUP) ||  \
      (pin  >= CORE_PERIPHERAL_PORT_PIN_MAX    ) )   \
  {                                                  \
    return;                                          \
  }



void CORE_PERIPHERAL_PORT_DirectionSet_noinline(
    core_peripheral_port_group_t      port,
    core_peripheral_port_pin_t        pin,
    core_peripheral_port_direction_t  direction
  )
{
  RANGE_CHECK_PORT_PIN_PARAMETERS( port, pin );

  switch( direction )
  {
    case CORE_PERIPHERAL_PORT_DIRECTION_INPUT:
      PORT->Group[port].DIRCLR.reg = (_UL_(1) << pin);
      break;

    case CORE_PERIPHERAL_PORT_DIRECTION_OUTPUT:
      PORT->Group[port].DIRSET.reg = (_UL_(1) << pin);
      break;

    default:
      break;
  }
}

core_peripheral_port_direction_t CORE_PERIPHERAL_PORT_DirectionGet_noinline(
    core_peripheral_port_group_t      port,
    core_peripheral_port_pin_t        pin
  )
{
  RANGE_CHECK_PORT_PIN_PARAMETERS( port, pin );

  return (PORT->Group[port].DIR.reg & (_UL_(1) << pin)) != 0;
}


void CORE_PERIPHERAL_PORT_OutputSet_noinline(
    core_peripheral_port_group_t      port,
    core_peripheral_port_pin_t        pin,
    core_peripheral_port_pinstate_t   state
  )
{
  RANGE_CHECK_PORT_PIN_PARAMETERS( port, pin );

  switch( state )
  {
    case CORE_PERIPHERAL_PORT_PINSTATE_LOW:
      PORT->Group[port].OUTCLR.reg = (_UL_(1) << pin);
      break;

    case CORE_PERIPHERAL_PORT_PINSTATE_HIGH:
      PORT->Group[port].OUTSET.reg = (_UL_(1) << pin);
      break;

    default:
      break;
  }
}

void CORE_PERIPHERAL_PORT_OutputToggle_noinline(
    core_peripheral_port_group_t      port,
    core_peripheral_port_pin_t        pin
  )
{
  RANGE_CHECK_PORT_PIN_PARAMETERS( port, pin );

  PORT->Group[port].OUTTGL.reg = (_UL_(1) << pin);
}

core_peripheral_port_pinstate_t CORE_PERIPHERAL_PORT_OutputGet_noinline(
    core_peripheral_port_group_t      port,
    core_peripheral_port_pin_t        pin
  )
{
  RANGE_CHECK_PORT_PIN_PARAMETERS( port, pin );

  return (PORT->Group[port].OUT.reg & (_UL_(1) << pin)) != 0;
}


core_peripheral_port_pinstate_t CORE_PERIPHERAL_PORT_InputGet_noinline(
    core_peripheral_port_group_t      port,
    core_peripheral_port_pin_t        pin
  )
{
  RANGE_CHECK_PORT_PIN_PARAMETERS( port, pin );

  return (PORT->Group[port].IN.reg & (_UL_(1) << pin)) != 0;
}


void CORE_PERIPHERAL_PORT_InputEnableSet(
    core_peripheral_port_group_t      port,
    core_peripheral_port_pin_t        pin,
    bool                              enable
  )
{
  RANGE_CHECK_PORT_PIN_PARAMETERS( port, pin );

  if( enable )
  {
    PORT->Group[port].PINCFG[pin].reg |= PORT_PINCFG_INEN;
  }
  else
  {
    PORT->Group[port].PINCFG[pin].reg &= ~PORT_PINCFG_INEN;
  }  
}

bool CORE_PERIPHERAL_PORT_InputEnableGet(
    core_peripheral_port_group_t      port,
    core_peripheral_port_pin_t        pin
  )
{
  RANGE_CHECK_PORT_PIN_PARAMETERS( port, pin );

  return (PORT->Group[port].PINCFG[pin].reg & PORT_PINCFG_INEN) != 0;
}


void CORE_PERIPHERAL_PORT_PullSet(
    core_peripheral_port_group_t      port,
    core_peripheral_port_pin_t        pin,
    core_peripheral_port_pull_t       pull
  )
{
  RANGE_CHECK_PORT_PIN_PARAMETERS( port, pin );

  switch( pull )
  {
    case CORE_PERIPHERAL_PORT_PULL_OFF:
      PORT->Group[port].PINCFG[pin].reg &= ~PORT_PINCFG_PULLEN;
      break;

    case CORE_PERIPHERAL_PORT_PULL_UP:
      if( !(PORT->Group[port].DIR & (_UL_(1) << pin)) )
      {
        // Pull up is controlled by output register.
        // Set only if pin is configured as input.
        PORT->Group[port].OUTSET.reg = (_UL_(1) << pin);
      }
      PORT->Group[port].PINCFG[pin].reg |= PORT_PINCFG_PULLEN;
      break;

    case CORE_PERIPHERAL_PORT_PULL_DOWN:
      if( !(PORT->Group[port].DIR & (_UL_(1) << pin)) )
      {
        // Pull down is controlled by output register.
        // Set only if pin is configured as input.
        PORT->Group[port].OUTCLR.reg = (_UL_(1) << pin);
      }
      PORT->Group[port].PINCFG[pin].reg |= PORT_PINCFG_PULLEN;
      break;

    default:
      break;
  }
}

core_peripheral_port_pull_t CORE_PERIPHERAL_PORT_PullGet(
    core_peripheral_port_group_t      port,
    core_peripheral_port_pin_t        pin
  )
{
  RANGE_CHECK_PORT_PIN_PARAMETERS( port, pin );

  if( PORT->Group[port].PINCFG[pin].reg & PORT_PINCFG_PULLEN )
  {
    return CORE_PERIPHERAL_PORT_PULL_OFF;
  }
  else
  {
    if( PORT->Group[port].OUT.reg & (_UL_(1) << pin) )
    {
      return CORE_PERIPHERAL_PORT_PULL_UP;
    }
    else
    {
      return CORE_PERIPHERAL_PORT_PULL_DOWN;
    }
  }
}


void CORE_PERIPHERAL_PORT_DriveStrengthSet(
    core_peripheral_port_group_t      port,
    core_peripheral_port_pin_t        pin,
    core_peripheral_port_strength_t   strength
  )
{
  RANGE_CHECK_PORT_PIN_PARAMETERS( port, pin );

  switch( strength )
  {
    case CORE_PERIPHERAL_PORT_STRENGTH_NORMAL:
      PORT->Group[port].PINCFG[pin].reg &= ~PORT_PINCFG_DRVSTR;
      break;

    case CORE_PERIPHERAL_PORT_STRENGTH_HIGH:
      PORT->Group[port].PINCFG[pin].reg |= PORT_PINCFG_DRVSTR;
      break;

    default:
      break;
  }
}

core_peripheral_port_strength_t CORE_PERIPHERAL_PORT_DriveStrengthGet(
    core_peripheral_port_group_t      port,
    core_peripheral_port_pin_t        pin
  )
{
  if( PORT->Group[port].PINCFG[pin].reg & PORT_PINCFG_DRVSTR )
  {
    return CORE_PERIPHERAL_PORT_STRENGTH_HIGH;
  }
  else
  {
    return CORE_PERIPHERAL_PORT_STRENGTH_NORMAL
  }
}


void CORE_PERIPHERAL_PORT_PinMuxSet(
    core_peripheral_port_group_t      port,
    core_peripheral_port_pin_t        pin,
    core_peripheral_port_pinmux_t     mux
  )
{
  RANGE_CHECK_PORT_PIN_PARAMETERS( port, pin );

  bool pinmask_enable = true;
  uint8_t pinmux_bitmask;
  
  switch( mux )
  {
    case CORE_PERIPHERAL_PORT_PINMUX_A:
      pinmux_bitmask = PORT_PMUX_PMUXE_A_Val;
      break;
    case CORE_PERIPHERAL_PORT_PINMUX_B:
      pinmux_bitmask = PORT_PMUX_PMUXE_B_Val;
      break;
    case CORE_PERIPHERAL_PORT_PINMUX_C:
      pinmux_bitmask = PORT_PMUX_PMUXE_C_Val;
      break;
    case CORE_PERIPHERAL_PORT_PINMUX_D:
      pinmux_bitmask = PORT_PMUX_PMUXE_D_Val;
      break;
    case CORE_PERIPHERAL_PORT_PINMUX_E:
      pinmux_bitmask = PORT_PMUX_PMUXE_E_Val;
      break;
    case CORE_PERIPHERAL_PORT_PINMUX_F:
      pinmux_bitmask = PORT_PMUX_PMUXE_F_Val;
      break;
    case CORE_PERIPHERAL_PORT_PINMUX_G:
      pinmux_bitmask = PORT_PMUX_PMUXE_G_Val;
      break;
    case CORE_PERIPHERAL_PORT_PINMUX_H:
      pinmux_bitmask = PORT_PMUX_PMUXE_H_Val;
      break;
    default:
      pinmux_enable = false;
      break;
  }

  if( pinmux_enable )
  {
    if( (pin % 2) == 0 )
    {
      // Even pin
      PORT->Group[port].PMUX[pin/2].reg &= ~PORT_PMUX_PMUXE_Msk;
      PORT->Group[port].PMUX[pin/2].reg |= PORT_PMUX_PMUXE(pinmux_bitmask);
    }
    else
    {
      // Odd pin
      PORT->Group[port].PMUX[pin/2].reg &= ~PORT_PMUX_PMUXO_Msk;
      PORT->Group[port].PMUX[pin/2].reg |= PORT_PMUX_PMUXO(pinmux_bitmask);
    }
    PORT->Group[port].PINCFG[pin].reg |= PORT_PINCFG_PMUXEN;
  }
  else
  {
    PORT->Group[port].PINCFG[pin].reg &= ~PORT_PINCFG_PMUXEN;
  }
}

core_peripheral_port_pinmux_t CORE_PERIPHERAL_PORT_PinMuxGet(
    core_peripheral_port_group_t      port,
    core_peripheral_port_pin_t        pin
  )
{
  RANGE_CHECK_PORT_PIN_PARAMETERS( port, pin );
  
  uint8_t pinmux_bitmask;

  if( PORT->Group[port].PINCFG[pin].reg & PORT_PINCFG_PMUXEN )
  {
    pinmux_bitmask = PORT->Group[port].PMUX[pin/2].reg;

    if( (pin % 2) == 0 )
    {
      pinmux_bitmask = (pinmux_bitmask & PORT_PMUX_PMUXE_Msk) >> PORT_PMUX_PMUXE_Pos;
    }
    else
    {
      pinmux_bitmask = (pinmux_bitmask & PORT_PMUX_PMUXO_Msk) >> PORT_PMUX_PMUXO_Pos;
    }

    switch( mux )
    {
      case PORT_PMUX_PMUXE_A_Val:
        return CORE_PERIPHERAL_PORT_PINMUX_A;
      case PORT_PMUX_PMUXE_B_Val:
        return CORE_PERIPHERAL_PORT_PINMUX_B;
      case PORT_PMUX_PMUXE_C_Val:
        return CORE_PERIPHERAL_PORT_PINMUX_C;
      case PORT_PMUX_PMUXE_D_Val:
        return CORE_PERIPHERAL_PORT_PINMUX_D;
      case PORT_PMUX_PMUXE_E_Val:
        return CORE_PERIPHERAL_PORT_PINMUX_E;
      case PORT_PMUX_PMUXE_F_Val:
        return CORE_PERIPHERAL_PORT_PINMUX_F;
      case PORT_PMUX_PMUXE_G_Val:
        return CORE_PERIPHERAL_PORT_PINMUX_G;
      case PORT_PMUX_PMUXE_H_Val:
        return CORE_PERIPHERAL_PORT_PINMUX_H;
      default:
        return CORE_PERIPHERAL_PORT_PINMUX_DISABLED;
    }
  }
  else
  {
    return CORE_PERIPHERAL_PORT_PINMUX_DISABLED;
  }
}


#ifdef __cplusplus
}
#endif
