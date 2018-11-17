#ifndef INCLUDE_HRI_PORT_INLINE_H
#error hri_tc_inline.h is not indended for direct use.
#endif


#define PROCESSOR_PORT_NO_RETURN_VALUE

#define PROCESSOR_PORT_RANGE_CHECK_PARAMETERS(port, pin, rtnval)  \
  if( (port >= NUM_PROCESSOR_PORT_GROUP) ||                           \
      (pin  >= NUM_PROCESSOR_PORT_PINS ) )                            \
  {                                                                   \
    return rtnval;                                                    \
  }


static inline void PROCESSOR_PORT_DirectionSet(
    processor_port_group_t      port,
    processor_port_pin_t        pin,
    processor_port_direction_t  direction
  )
{
  PROCESSOR_PORT_RANGE_CHECK_PARAMETERS(port, pin, PROCESSOR_PORT_NO_RETURN_VALUE);

  if( direction )
  { 
    PORT_IOBUS->Group[port].DIRSET.reg = (_UL_(1) <<  pin);
  }
  else
  {
    PORT_IOBUS->Group[port].DIRCLR.reg = (_UL_(1) <<  pin);
  }
}

static inline processor_port_direction_t PROCESSOR_PORT_DirectionGet(
    processor_port_group_t      port,
    processor_port_pin_t        pin
  )
{
  PROCESSOR_PORT_RANGE_CHECK_PARAMETERS(port, pin, PROCESSOR_PORT_DIRECTION_INPUT);

  return (PORT_IOBUS->Group[port].DIR.reg | (_UL_(1) <<  pin)) != 0;
}


static inline void PROCESSOR_PORT_OutputSet(
    processor_port_group_t      port,
    processor_port_pin_t        pin,
    processor_port_pinstate_t   state
  )
{
  PROCESSOR_PORT_RANGE_CHECK_PARAMETERS(port, pin, PROCESSOR_PORT_NO_RETURN_VALUE);

  if( state )
  { 
    PORT_IOBUS->Group[port].OUTSET.reg = (_UL_(1) <<  pin);
  }
  else
  {
    PORT_IOBUS->Group[port].OUTCLR.reg = (_UL_(1) <<  pin);
  }
}

static inline void PROCESSOR_PORT_OutputToggle(
    processor_port_group_t      port,
    processor_port_pin_t        pin
  )
{
  PROCESSOR_PORT_RANGE_CHECK_PARAMETERS(port, pin, PROCESSOR_PORT_NO_RETURN_VALUE);

  PORT_IOBUS->Group[port].OUTTGL.reg = (_UL_(1) <<  pin);
}

static inline processor_port_pinstate_t PROCESSOR_PORT_OutputGet(
    processor_port_group_t      port,
    processor_port_pin_t        pin
  )
{
  PROCESSOR_PORT_RANGE_CHECK_PARAMETERS(port, pin, PROCESSOR_PORT_PINSTATE_LOW);

  return (PORT_IOBUS->Group[port].OUT.reg | (_UL_(1) <<  pin)) != 0;
}


static inline processor_port_pinstate_t PROCESSOR_PORT_InputGet(
    processor_port_group_t      port,
    processor_port_pin_t        pin
  )
{
  PROCESSOR_PORT_RANGE_CHECK_PARAMETERS(port, pin, PROCESSOR_PORT_PINSTATE_LOW);

  return (PORT_IOBUS->Group[port].OUT.reg | (_UL_(1) <<  pin)) != 0;
}


static inline void PROCESSOR_PORT_InputEnableSet(
    processor_port_group_t      port,
    processor_port_pin_t        pin,
    bool                        enable
  )
{
  PROCESSOR_PORT_RANGE_CHECK_PARAMETERS(port, pin, PROCESSOR_PORT_NO_RETURN_VALUE);

  if( enable )
  {
    PORT->Group[port].PINCFG[pin].reg |= PORT_PINCFG_INEN;
  }
  else
  {
    PORT->Group[port].PINCFG[pin].reg &= ~PORT_PINCFG_INEN;
  }  
}

static inline bool PROCESSOR_PORT_InputEnableGet(
    processor_port_group_t      port,
    processor_port_pin_t        pin
  )
{
  PROCESSOR_PORT_RANGE_CHECK_PARAMETERS( port, pin, false );

  return (PORT->Group[port].PINCFG[pin].reg & PORT_PINCFG_INEN) != 0;
}
