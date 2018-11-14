#include "processor/evsys.h"

#include "processor/sam.h"
#include "utils/utils.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


static processor_evsys_interrupt_callback_t _interrupt_callback[PROCESSOR_EVSYS_NUM_CHANNELS];


void PROCESSOR_EVSYS_Initialize( void )
{
  EVSYS->CTRL.bit.SWRST = 1;
  while( EVSYS->CTRL.bit.SWRST );
}


void PROCESSOR_EVSYS_User_Set(
    processor_evsys_user_t user,
    processor_evsys_user_channel_t channel
  )
{
  EVSYS->USER.reg = EVSYS_USER_CHANNEL(channel) | EVSYS_USER_USER(user);
}

void PROCESSOR_EVSYS_Generator_Set(
    processor_evsys_generator_t generator,
    processor_evsys_channel_t channel,
    processor_evsys_edge_t edge,
    processor_evsys_path_t path
  )
{
  if (channel >= PROCESSOR_EVSYS_NUM_CHANNELS)   return;

  EVSYS->CHANNEL.reg = EVSYS_CHANNEL_CHANNEL(channel) | 
                       EVSYS_CHANNEL_EVGEN(generator) |
                       EVSYS_CHANNEL_EDGSEL(edge) |
                       EVSYS_CHANNEL_PATH(path);
}

void PROCESSOR_EVSYS_SoftwareTrigger(
    processor_evsys_channel_t channel
  )
{
  if( channel >= PROCESSOR_EVSYS_NUM_CHANNELS )  return;

  // Need to use 16-bit write to assert Software Trigger
  *(__IO uint16_t*)&EVSYS->CHANNEL.reg = (uint16_t)(EVSYS_CHANNEL_CHANNEL(channel) |
                                                    EVSYS_CHANNEL_SWEVT );
}

bool PROCESSOR_EVSYS_isChannelBusy(
    processor_evsys_channel_t channel
  )
{
  if( channel >= PROCESSOR_EVSYS_NUM_CHANNELS )  return false;

  if( channel < 8 )
  {
    return (EVSYS->CHSTATUS.reg | (EVSYS_CHSTATUS_CHBUSY0 << channel)) != 0;
  }
  else
  {
    return (EVSYS->CHSTATUS.reg | (EVSYS_CHSTATUS_CHBUSY8 << (channel-8))) != 0;
  }
}

bool PROCESSOR_EVSYS_isChannelUserReady(
    processor_evsys_channel_t channel
  )
{
  if( channel >= PROCESSOR_EVSYS_NUM_CHANNELS )  return false;

  if( channel < 8 )
  {
    return (EVSYS->CHSTATUS.reg | (EVSYS_CHSTATUS_USRRDY0 << channel)) != 0;
  }
  else
  {
    return (EVSYS->CHSTATUS.reg | (EVSYS_CHSTATUS_USRRDY8 << (channel-8))) != 0;
  }
}


void PROCESSOR_EVSYS_InterruptCallback_Set(
    processor_evsys_channel_t channel,
    processor_evsys_interrupt_callback_t callback
  )
{
  if( channel >= PROCESSOR_EVSYS_NUM_CHANNELS )  return;

  _interrupt_callback[channel] = callback;
}

void PROCESSOR_EVSYS_Interrupt_Enable(
    processor_evsys_channel_t channel,
    processor_evsys_interrupt_t interrupt
  )
{
  if( channel >= PROCESSOR_EVSYS_NUM_CHANNELS )  return;

  switch( interrupt )
  {
    case PROCESSOR_EVSYS_INTERRUPT_DETECT:
      if( channel < 8 )
      {
        EVSYS->INTENSET.reg = EVSYS_INTENSET_EVD0 << channel;
      }
      else
      {
        EVSYS->INTENSET.reg = EVSYS_INTENSET_EVD8 << (channel-8);
      }
      break;

    case PROCESSOR_EVSYS_INTERRUPT_OVERRUN:
      if( channel < 8 )
      {
        EVSYS->INTENSET.reg = EVSYS_INTENSET_OVR0 << channel;
      }
      else
      {
        EVSYS->INTENSET.reg = EVSYS_INTENSET_OVR8 << (channel-8);
      }
      break;

    default:
      break;
  }
}


void PROCESSOR_EVSYS_Interrupt_Disable(
    processor_evsys_channel_t channel,
    processor_evsys_interrupt_t interrupt
  )
{
  if( channel >= PROCESSOR_EVSYS_NUM_CHANNELS )  return;

  switch( interrupt )
  {
    case PROCESSOR_EVSYS_INTERRUPT_DETECT:
      if( channel < 8 )
      {
        EVSYS->INTENCLR.reg = EVSYS_INTENCLR_EVD0 << channel;
      }
      else
      {
        EVSYS->INTENCLR.reg = EVSYS_INTENCLR_EVD8 << (channel-8);
      }
      break;

    case PROCESSOR_EVSYS_INTERRUPT_OVERRUN:
      if( channel < 8 )
      {
        EVSYS->INTENCLR.reg = EVSYS_INTENCLR_OVR0 << channel;
      }
      else
      {
        EVSYS->INTENCLR.reg = EVSYS_INTENCLR_OVR8 << (channel-8);
      }
      break;

    default:
      break;
  }
}

bool PROCESSOR_EVSYS_InterruptFlag_Get(
    processor_evsys_channel_t channel,
    processor_evsys_interrupt_t interrupt
  )
{
  if( channel >= PROCESSOR_EVSYS_NUM_CHANNELS )  return false;

  switch( interrupt )
  {
    case PROCESSOR_EVSYS_INTERRUPT_DETECT:
      if( channel < 8 )
      {
        return (EVSYS->INTFLAG.reg | (EVSYS_INTFLAG_EVD0 << channel)) != 0;
      }
      else
      {
        return (EVSYS->INTFLAG.reg | (EVSYS_INTFLAG_EVD8 << (channel-8))) != 0;
      }
    
    case PROCESSOR_EVSYS_INTERRUPT_OVERRUN:
      if( channel < 8 )
      {
        return (EVSYS->INTFLAG.reg | (EVSYS_INTFLAG_OVR0 << channel)) != 0;
      }
      else
      {
        return (EVSYS->INTFLAG.reg | (EVSYS_INTFLAG_OVR8 << (channel-8))) != 0;
      }

    default:
      return false;
  }
}

void PROCESSOR_EVSYS_InterruptFlag_Clear(
    processor_evsys_channel_t channel,
    processor_evsys_interrupt_t interrupt
  )
{
  uint8_t channel_shift = (uint8_t)channel;

  if( channel >= PROCESSOR_EVSYS_NUM_CHANNELS )  return;

  switch( interrupt )
  {
    case PROCESSOR_EVSYS_INTERRUPT_DETECT:
      if( channel < 8 )
      {
        EVSYS->INTFLAG.reg = EVSYS_INTFLAG_EVD0 << channel;
      }
      else
      {
        EVSYS->INTFLAG.reg = EVSYS_INTFLAG_EVD8 << (channel-8);
      }
      break;

    case PROCESSOR_EVSYS_INTERRUPT_OVERRUN:
      if( channel < 8 )
      {
        EVSYS->INTFLAG.reg = EVSYS_INTFLAG_OVR0 << channel;
      }
      else
      {
        EVSYS->INTFLAG.reg = EVSYS_INTFLAG_OVR8 << (channel-8);
      }
      break;

    default:
      break;
  }
}
