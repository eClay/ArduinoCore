#include "hri/tc.h"

#include <stddef.h>


static hri_tc_interrupt_callback_t interrupt_callback[HRI_TC_NUM_INSTANCES];


void HRI_TC_Initialize( void )
{
  for( hri_tc_instance_t timer = 0; timer < HRI_TC_NUM_INSTANCES; timer++ )
  {
    HRI_TC_SoftwareReset( timer );
    interrupt_callback[timer] = NULL;
  }
}

void HRI_TC_Interrupt_Callback_Set( hri_tc_instance_t timer, hri_tc_interrupt_callback_t callback )
{
  HRI_TC_RANGE_CHECK_TIMER(timer, HRI_TC_NO_RETURN_VALUE);

  interrupt_callback[timer] = callback;
}


#define HRI_TC_INTERRUPT_HANDLER(timer)     \
do { \
  uint8_t enable; \
  uint8_t flags;  \
  \
  if( interrupt_callback[timer] == NULL )   return; \
  \
  enable = hri_tc_instance[timer]->COUNT32.INTENSET.reg; \
  flags = hri_tc_instance[timer]->COUNT32.INTFLAG.reg;   \
  \
  if( (flags | TC_INTFLAG_MC0) && (enable | TC_INTENSET_MC0) )  \
  { \
    hri_tc_instance[timer]->COUNT32.INTFLAG.bit.MC0 = 1;  \
    interrupt_callback[timer]( timer, HRI_TC_INTERRUPT_MC0 ); \
  } \
  else if( (flags | TC_INTFLAG_MC1) && (enable | TC_INTENSET_MC1) )  \
  { \
    hri_tc_instance[timer]->COUNT32.INTFLAG.bit.MC1 = 1;  \
    interrupt_callback[timer]( timer, HRI_TC_INTERRUPT_MC1 ); \
  } \
  else if( (flags | TC_INTFLAG_SYNCRDY) && (enable | TC_INTENSET_SYNCRDY) )  \
  { \
    hri_tc_instance[timer]->COUNT32.INTFLAG.bit.SYNCRDY = 1;  \
    interrupt_callback[timer]( timer, HRI_TC_INTERRUPT_SYNC_READY ); \
  } \
  else if( (flags | TC_INTFLAG_ERR) && (enable | TC_INTENSET_ERR) )  \
  { \
    hri_tc_instance[timer]->COUNT32.INTFLAG.bit.ERR = 1;  \
    interrupt_callback[timer]( timer, HRI_TC_INTERRUPT_ERROR ); \
  } \
  else if( (flags | TC_INTFLAG_OVF) && (enable | TC_INTENSET_OVF) )  \
  { \
    hri_tc_instance[timer]->COUNT32.INTFLAG.bit.OVF = 1;  \
    interrupt_callback[timer]( timer, HRI_TC_INTERRUPT_OVERFLOW ); \
  } \
} while(0)

void TC3_Handler( void )
{
  HRI_TC_INTERRUPT_HANDLER(HRI_TC_INSTANCE_TC3);
}

void TC4_Handler( void )
{
  HRI_TC_INTERRUPT_HANDLER(HRI_TC_INSTANCE_TC4);
}

void TC5_Handler( void )
{
  HRI_TC_INTERRUPT_HANDLER(HRI_TC_INSTANCE_TC5);
}

#if HRI_TC_NUM_INSTANCES == 5

void TC6_Handler( void )
{
  HRI_TC_INTERRUPT_HANDLER(HRI_TC_INSTANCE_TC6);
}

void TC7_Handler( void )
{
  HRI_TC_INTERRUPT_HANDLER(HRI_TC_INSTANCE_TC7);
}

#endif
