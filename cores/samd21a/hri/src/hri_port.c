#include "hri/port.h"

#include "hri/sam.h"

#include <stdbool.h>
#include <stdint.h>


#ifdef __cplusplus
 extern "C" {
#endif


void PROCESSOR_PORT_Initialize( void )
{

}


void PROCESSOR_PORT_PullSet(
    processor_port_group_t      port,
    processor_port_pin_t        pin,
    processor_port_pull_t       pull
  )
{
  PROCESSOR_PORT_RANGE_CHECK_PARAMETERS( port, pin, PROCESSOR_PORT_NO_RETURN_VALUE );

  switch( pull )
  {
    case PROCESSOR_PORT_PULL_OFF:
      PORT->Group[port].PINCFG[pin].reg &= ~PORT_PINCFG_PULLEN;
      break;

    case PROCESSOR_PORT_PULL_UP:
      if( !(PORT_IOBUS->Group[port].DIR.reg & (_UL_(1) << pin)) )
      {
        // Pull up is controlled by output register.
        // Set only if pin is configured as input.
        PORT_IOBUS->Group[port].OUTSET.reg = (_UL_(1) << pin);
      }
      PORT->Group[port].PINCFG[pin].reg |= PORT_PINCFG_PULLEN;
      break;

    case PROCESSOR_PORT_PULL_DOWN:
      if( !(PORT_IOBUS->Group[port].DIR.reg & (_UL_(1) << pin)) )
      {
        // Pull down is controlled by output register.
        // Set only if pin is configured as input.
        PORT_IOBUS->Group[port].OUTCLR.reg = (_UL_(1) << pin);
      }
      PORT->Group[port].PINCFG[pin].reg |= PORT_PINCFG_PULLEN;
      break;

    default:
      break;
  }
}

processor_port_pull_t PROCESSOR_PORT_PullGet(
    processor_port_group_t      port,
    processor_port_pin_t        pin
  )
{
  PROCESSOR_PORT_RANGE_CHECK_PARAMETERS( port, pin, PROCESSOR_PORT_PULL_INVALID );

  if( !(PORT->Group[port].PINCFG[pin].reg & PORT_PINCFG_PULLEN) )
  {
    return PROCESSOR_PORT_PULL_OFF;
  }
  else
  {
    if( PORT_IOBUS->Group[port].OUT.reg & (_UL_(1) << pin) )
    {
      return PROCESSOR_PORT_PULL_UP;
    }
    else
    {
      return PROCESSOR_PORT_PULL_DOWN;
    }
  }
}


void PROCESSOR_PORT_DriveStrengthSet(
    processor_port_group_t      port,
    processor_port_pin_t        pin,
    processor_port_strength_t   strength
  )
{
  PROCESSOR_PORT_RANGE_CHECK_PARAMETERS( port, pin, PROCESSOR_PORT_NO_RETURN_VALUE );

  switch( strength )
  {
    case PROCESSOR_PORT_STRENGTH_NORMAL:
      PORT->Group[port].PINCFG[pin].reg &= ~PORT_PINCFG_DRVSTR;
      break;

    case PROCESSOR_PORT_STRENGTH_HIGH:
      PORT->Group[port].PINCFG[pin].reg |= PORT_PINCFG_DRVSTR;
      break;

    default:
      break;
  }
}

processor_port_strength_t PROCESSOR_PORT_DriveStrengthGet(
    processor_port_group_t      port,
    processor_port_pin_t        pin
  )
{
  PROCESSOR_PORT_RANGE_CHECK_PARAMETERS( port, pin, PROCESSOR_PORT_STRENGTH_INVALID );

  if( PORT->Group[port].PINCFG[pin].reg & PORT_PINCFG_DRVSTR )
  {
    return PROCESSOR_PORT_STRENGTH_HIGH;
  }
  else
  {
    return PROCESSOR_PORT_STRENGTH_NORMAL;
  }
}


void PROCESSOR_PORT_PinMuxSet(
    processor_port_group_t      port,
    processor_port_pin_t        pin,
    processor_port_pinmux_t     mux
  )
{
  PROCESSOR_PORT_RANGE_CHECK_PARAMETERS( port, pin, PROCESSOR_PORT_NO_RETURN_VALUE );

  bool pinmux_enable = true;
  uint8_t pinmux_bitmask;
  
  switch( mux )
  {
    case PROCESSOR_PORT_PINMUX_A:
      pinmux_bitmask = PORT_PMUX_PMUXE_A_Val;
      break;
    case PROCESSOR_PORT_PINMUX_B:
      pinmux_bitmask = PORT_PMUX_PMUXE_B_Val;
      break;
    case PROCESSOR_PORT_PINMUX_C:
      pinmux_bitmask = PORT_PMUX_PMUXE_C_Val;
      break;
    case PROCESSOR_PORT_PINMUX_D:
      pinmux_bitmask = PORT_PMUX_PMUXE_D_Val;
      break;
    case PROCESSOR_PORT_PINMUX_E:
      pinmux_bitmask = PORT_PMUX_PMUXE_E_Val;
      break;
    case PROCESSOR_PORT_PINMUX_F:
      pinmux_bitmask = PORT_PMUX_PMUXE_F_Val;
      break;
    case PROCESSOR_PORT_PINMUX_G:
      pinmux_bitmask = PORT_PMUX_PMUXE_G_Val;
      break;
    case PROCESSOR_PORT_PINMUX_H:
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

processor_port_pinmux_t PROCESSOR_PORT_PinMuxGet(
    processor_port_group_t      port,
    processor_port_pin_t        pin
  )
{
  PROCESSOR_PORT_RANGE_CHECK_PARAMETERS( port, pin, PROCESSOR_PORT_PINMUX_INVALID );
  
  if( PORT->Group[port].PINCFG[pin].reg & PORT_PINCFG_PMUXEN )
  {
    uint8_t pinmux_bitmask = PORT->Group[port].PMUX[pin/2].reg;

    if( (pin % 2) == 0 )
    {
      // Even pin
      pinmux_bitmask = (pinmux_bitmask & PORT_PMUX_PMUXE_Msk) >> PORT_PMUX_PMUXE_Pos;
    }
    else
    {
      // Odd pin
      pinmux_bitmask = (pinmux_bitmask & PORT_PMUX_PMUXO_Msk) >> PORT_PMUX_PMUXO_Pos;
    }

    switch( pinmux_bitmask )
    {
      case PORT_PMUX_PMUXE_A_Val:
        return PROCESSOR_PORT_PINMUX_A;
      case PORT_PMUX_PMUXE_B_Val:
        return PROCESSOR_PORT_PINMUX_B;
      case PORT_PMUX_PMUXE_C_Val:
        return PROCESSOR_PORT_PINMUX_C;
      case PORT_PMUX_PMUXE_D_Val:
        return PROCESSOR_PORT_PINMUX_D;
      case PORT_PMUX_PMUXE_E_Val:
        return PROCESSOR_PORT_PINMUX_E;
      case PORT_PMUX_PMUXE_F_Val:
        return PROCESSOR_PORT_PINMUX_F;
      case PORT_PMUX_PMUXE_G_Val:
        return PROCESSOR_PORT_PINMUX_G;
      case PORT_PMUX_PMUXE_H_Val:
        return PROCESSOR_PORT_PINMUX_H;
      default:
        return PROCESSOR_PORT_PINMUX_DISABLED;
    }
  }
  else
  {
    return PROCESSOR_PORT_PINMUX_DISABLED;
  }
}


#ifdef __cplusplus
}
#endif
