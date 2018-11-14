#include "processor/evsys.h"

#include "processor/sam.h"
#include "utils/utils.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


typedef struct
{
  processor_event_system_detect_callback_t   detect_callback;
  processor_event_system_overrun_callback_t  overrun_callback;
} processor_event_system_callbacks_t;

static processor_event_system_callbacks_t _interrupt_callbacks[PROCESSOR_EVENT_SYSTEM_NUM_CHANNELS];


void PROCESSOR_EVENT_SYSTEM_Initialize( void )
{
  EVSYS->CTRL.bit.SWRST = 1;
  while( EVSYS->CTRL.bit.SWRST );
}


void PROCESSOR_EVENT_SYSTEM_User_Set(
    processor_event_system_user_t user,
    processor_event_system_user_channel_t channel
  )
{
  EVSYS->USER.reg = EVSYS_USER_CHANNEL(channel) | EVSYS_USER_USER(user);
}

void PROCESSOR_EVENT_SYSTEM_Generator_Set(
    processor_event_system_generator_t generator,
    processor_event_system_channel_t channel,
    processor_event_system_edge_t edge,
    processor_event_system_path_t path
  )
{
  if (channel >= PROCESSOR_EVENT_SYSTEM_NUM_CHANNELS)   return;

  EVSYS->CHANNEL.reg = EVSYS_CHANNEL_CHANNEL(channel) | 
                       EVSYS_CHANNEL_EVGEN(generator) |
                       EVSYS_CHANNEL_EDGSEL(edge) |
                       EVSYS_CHANNEL_PATH(path);
}

void PROCESSOR_EVENT_SYSTEM_SoftwareTrigger(
    processor_event_system_channel_t channel
  )
{
  if( channel >= PROCESSOR_EVENT_SYSTEM_NUM_CHANNELS )  return;

  // Need to use 16-bit write to assert Software Trigger
  *(__IO uint16_t*)&EVSYS->CHANNEL.reg = (uint16_t)(EVSYS_CHANNEL_CHANNEL(channel) |
                                                    EVSYS_CHANNEL_SWEVT );
}

bool PROCESSOR_EVENT_SYSTEM_isChannelBusy(
    processor_event_system_channel_t channel
  )
{
  if( channel >= PROCESSOR_EVENT_SYSTEM_NUM_CHANNELS )  return false;

  if( channel < 8 )
  {
    return (EVSYS->CHSTATUS.reg | (EVSYS_CHSTATUS_CHBUSY0 << channel)) != 0;
  }
  else
  {
    return (EVSYS->CHSTATUS.reg | (EVSYS_CHSTATUS_CHBUSY8 << (channel-8))) != 0;
  }
}

bool PROCESSOR_EVENT_SYSTEM_isChannelUserReady(
    processor_event_system_channel_t channel
  )
{
  if( channel >= PROCESSOR_EVENT_SYSTEM_NUM_CHANNELS )  return false;

  if( channel < 8 )
  {
    return (EVSYS->CHSTATUS.reg | (EVSYS_CHSTATUS_USRRDY0 << channel)) != 0;
  }
  else
  {
    return (EVSYS->CHSTATUS.reg | (EVSYS_CHSTATUS_USRRDY8 << (channel-8))) != 0;
  }
}

void PROCESSOR_EVENT_SYSTEM_EventDetectCallback_Set(
    processor_event_system_channel_t channel,
    processor_event_system_detect_callback_t callback
  )
{
  if( channel >= PROCESSOR_EVENT_SYSTEM_NUM_CHANNELS )  return;

  _interrupt_callbacks[channel].detect_callback = callback;
}

void PROCESSOR_EVENT_SYSTEM_OverrunCallback_Set(
    processor_event_system_channel_t channel,
    processor_event_system_overrun_callback_t callback
  )
{
  if( channel >= PROCESSOR_EVENT_SYSTEM_NUM_CHANNELS )  return;

  _interrupt_callbacks[channel].overrun_callback = callback;
}

void PROCESSOR_EVENT_SYSTEM_EventDetectInterruptEnable_Set(
    processor_event_system_channel_t channel,
    bool enable
  )
{
  if( channel >= PROCESSOR_EVENT_SYSTEM_NUM_CHANNELS )  return;

  if( channel < 8 )
  {
    if( enable )
    {
      EVSYS->INTENSET.reg = EVSYS_INTENSET_EVD0 << channel;
    }
    else
    {
      EVSYS->INTENCLR.reg = EVSYS_INTENCLR_EVD0 << channel;
    }
  }
  else
  {
    if( enable )
    {
      EVSYS->INTENSET.reg = EVSYS_INTENSET_EVD8 << (channel-8);
    }
    else
    {
      EVSYS->INTENCLR.reg = EVSYS_INTENCLR_EVD8 << (channel-8);
    }
  }
}

void PROCESSOR_EVENT_SYSTEM_OverrunInterruptEnable_Set(
    processor_event_system_channel_t channel,
    bool enable
  )
{
  if( channel >= PROCESSOR_EVENT_SYSTEM_NUM_CHANNELS )  return;

  if( channel < 8 )
  {
    if( enable )
    {
      EVSYS->INTENSET.reg = EVSYS_INTENSET_OVR0 << channel;
    }
    else
    {
      EVSYS->INTENCLR.reg = EVSYS_INTENCLR_OVR0 << channel;
    }
  }
  else
  {
    if( enable )
    {
      EVSYS->INTENSET.reg = EVSYS_INTENSET_OVR8 << (channel-8);
    }
    else
    {
      EVSYS->INTENCLR.reg = EVSYS_INTENCLR_OVR8 << (channel-8);
    }
  }
}

bool PROCESSOR_EVENT_SYSTEM_EventDetectInterruptFlag_Get(
    processor_event_system_channel_t channel
  )
{
  if( channel >= PROCESSOR_EVENT_SYSTEM_NUM_CHANNELS )  return false;
  
  if( channel < 8 )
  {
    return (EVSYS->INTFLAG.reg | (EVSYS_INTFLAG_EVD0 << channel)) != 0;
  }
  else
  {
    return (EVSYS->INTFLAG.reg | (EVSYS_INTFLAG_EVD8 << (channel-8))) != 0;
  }
}

bool PROCESSOR_EVENT_SYSTEM_OverrunInterruptFlag_Get(
    processor_event_system_channel_t channel
  )
{
  if( channel >= PROCESSOR_EVENT_SYSTEM_NUM_CHANNELS )  return false;

  if( channel < 8 )
  {
    return (EVSYS->INTFLAG.reg | (EVSYS_INTFLAG_OVR0 << channel)) != 0;
  }
  else
  {
    return (EVSYS->INTFLAG.reg | (EVSYS_INTFLAG_OVR8 << (channel-8))) != 0;
  }
}

void PROCESSOR_EVENT_SYSTEM_EventDetectInterruptFlag_Clear(
    processor_event_system_channel_t channel
  )
{
  if( channel >= PROCESSOR_EVENT_SYSTEM_NUM_CHANNELS )  return;

  if( channel < 8 )
  {
    EVSYS->INTFLAG.reg = EVSYS_INTFLAG_EVD0 << channel;
  }
  else
  {
    EVSYS->INTFLAG.reg = EVSYS_INTFLAG_EVD8 << (channel-8);
  }
}

void PROCESSOR_EVENT_SYSTEM_OverrunInterruptFlag_Clear(
    processor_event_system_channel_t channel
  )
{
  if( channel >= PROCESSOR_EVENT_SYSTEM_NUM_CHANNELS )  return;

  if( channel < 8 )
  {
    EVSYS->INTFLAG.reg = EVSYS_INTFLAG_OVR0 << channel;
  }
  else
  {
    EVSYS->INTFLAG.reg = EVSYS_INTFLAG_OVR8 << (channel-8);
  }
}

