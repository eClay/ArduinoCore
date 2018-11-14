#ifndef ECLAY_PROCESSOR_TC_H
#define ECLAY_PROCESSOR_TC_H

#include "processor/sam.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
  PROCESSOR_TC_INSTANCE_TC3 = 0,
  PROCESSOR_TC_INSTANCE_TC4,
  PROCESSOR_TC_INSTANCE_TC5,
  NUM_PROCESSOR_TC_INSTANCES,
  NOT_A_PROCESSOR_TC_INSTANCE = NUM_PROCESSOR_TC_INSTANCES
} processor_tc_instance_t;

typedef enum {
  PROCESSOR_TC_CHANNEL_TC_MC0 = 0,
  PROCESSOR_TC_CHANNEL_TC_MC1 = 1,
} processor_tc_channel_t;

typedef enum {
  PROCESSOR_TC_INTERRUPT_MC0 = 0,
  PROCESSOR_TC_INTERRUPT_MC1,
  PROCESSOR_TC_INTERRUPT_SYNC_READY,
  PROCESSOR_TC_INTERRUPT_ERROR,
  PROCESSOR_TC_INTERRUPT_OVERFLOW,
} processor_tc_interrupt_t;

typedef enum {
  PROCESSOR_TC_EVENT_INPUT_MC0 = 0,
  PROCESSOR_TC_EVENT_INPUT_MC1,
  PROCESSOR_TC_EVENT_INPUT_EV,
  PROCESSOR_TC_EVENT_INPUT_EV_INVERTED,
} processor_tc_event_input_t;

typedef enum {
  PROCESSOR_TC_EVENT_INPUT_ACTION_OFF            = 0x0,
  PROCESSOR_TC_EVENT_INPUT_ACTION_RETRIGGER      = 0x1,
  PROCESSOR_TC_EVENT_INPUT_ACTION_COUNT          = 0x2,
  PROCESSOR_TC_EVENT_INPUT_ACTION_START          = 0x3,
  PROCESSOR_TC_EVENT_INPUT_ACTION_PPW            = 0x5,
  PROCESSOR_TC_EVENT_INPUT_ACTION_PWP            = 0x6,
} processor_tc_event_input_action_t;

typedef enum {
  PROCESSOR_TC_EVENT_OUTPUT_MC0,
  PROCESSOR_TC_EVENT_OUTPUT_MC1,
  PROCESSOR_TC_EVENT_OUTPUT_COUNT,
  PROCESSOR_TC_EVENT_OUTPUT_RETRIGGER,
  PROCESSOR_TC_EVENT_OUTPUT_OVERFLOW,
} processor_tc_event_output_t;

typedef enum {
  PROCESSOR_TC_EVENT_COUNT_MODE_BEGIN    = 0x0,
  PROCESSOR_TC_EVENT_COUNT_MODE_END      = 0x1,
  PROCESSOR_TC_EVENT_COUNT_MODE_BETWEEN  = 0x2,
  PROCESSOR_TC_EVENT_COUNT_MODE_BOUNDARY = 0x3,
} processor_tc_event_count_mode_t;

typedef enum {
  PROCESSOR_TC_TC_WAVEFORM_NORMAL_FREQUENCY = 0x0,
  PROCESSOR_TC_TC_WAVEFORM_MATCH_FREQUENCY  = 0x1,
  PROCESSOR_TC_TC_WAVEFORM_NORMAL_PWM       = 0x2,
  PROCESSOR_TC_TC_WAVEFORM_MATCH_PWM        = 0x3,
} processor_tc_waveform_t;


void PROCESSOR_TC_InitializeAll( void );


static inline void PROCESSOR_TC_SoftwareReset(
    processor_tc_instance_t  timer
  );


static inline void PROCESSOR_TC_Enable(
    processor_tc_instance_t  timer
  );

static inline void PROCESSOR_TC_Disable(
    processor_tc_instance_t  timer
  );


static inline void PROCESSOR_TC_Waveform_Set(
    processor_tc_instance_t  timer,
    processor_tc_waveform_t  waveform
  );


static inline void PROCESSOR_TC_Period_Set(
    processor_tc_instance_t  timer,
    uint32_t                 period
  );

static inline void PROCESSOR_TC_Count_Set(
    processor_tc_instance_t  timer,
    uint32_t                 count
  );

static inline uint32_t PROCESSOR_TC_Count_Get(
    processor_tc_instance_t  timer
  );

static inline void PROCESSOR_TC_Compare_Set(
    processor_tc_instance_t  timer,
    processor_tc_channel_t   channel,
    uint32_t                 compare
  );

static inline uint32_t PROCESSOR_TC_Capture_Get(
    processor_tc_instance_t  timer,
    processor_tc_channel_t   channel
  );


static inline void PROCESSOR_TC_CMD_Retrigger(
    processor_tc_instance_t  timer
  );

static inline void PROCESSOR_TC_CMD_Stop(
    processor_tc_instance_t  timer
  );


static inline void PROCESSOR_TC_EVENT_Output_Enable(
    processor_tc_instance_t      timer,
    processor_tc_event_output_t  event
  );

static inline void PROCESSOR_TC_EVENT_Output_Disable(
    processor_tc_instance_t      timer,
    processor_tc_event_output_t  event
  );

static inline void PROCESSOR_TC_EVENT_CountMode_Set(
    processor_tc_instance_t          timer,
    processor_tc_event_count_mode_t  mode
  );


static inline void PROCESSOR_TC_EVENT_Input_Enable(
    processor_tc_instance_t      timer,
    processor_tc_event_input_t   event
  );

static inline void PROCESSOR_TC_EVENT_Input_Disable(
    processor_tc_instance_t      timer,
    processor_tc_event_input_t   event
  );

static inline void PROCESSOR_TC_EVENT_InputAction_Set(
    processor_tc_instance_t            timer,
    processor_tc_event_input_action_t  action
  );



//********************************************************

static inline void PROCESSOR_TC_SoftwareReset(
    processor_tc_instance_t  timer
  )
{
  switch( timer )
  {
    case PROCESSOR_TC_INSTANCE_TC3:
      TC3->COUNT32.CTRLA.bit.SWRST = 1;
      while( TC3->COUNT32.CTRLA.bit.SWRST );
      break;
    case PROCESSOR_TC_INSTANCE_TC4:
      TC4->COUNT32.CTRLA.bit.SWRST = 1;
      while( TC4->COUNT32.CTRLA.bit.SWRST );
      break;
    case PROCESSOR_TC_INSTANCE_TC5:
      TC5->COUNT32.CTRLA.bit.SWRST = 1;
      while( TC5->COUNT32.CTRLA.bit.SWRST );
      break;
    default:
      break;
  }
}


static inline void PROCESSOR_TC_Enable(
    processor_tc_instance_t  timer
  )
{
  switch( timer )
  {
    case PROCESSOR_TC_INSTANCE_TC3:
      TC3->COUNT32.CTRLA.bit.ENABLE = 1;
      while( TC3->COUNT32.STATUS.bit.SYNCBUSY );
      break;
    case PROCESSOR_TC_INSTANCE_TC4:
      TC4->COUNT32.CTRLA.bit.ENABLE = 1;
      while( TC4->COUNT32.STATUS.bit.SYNCBUSY );
      break;
    case PROCESSOR_TC_INSTANCE_TC5:
      TC5->COUNT32.CTRLA.bit.ENABLE = 1;
      while( TC5->COUNT32.STATUS.bit.SYNCBUSY );
      break;
    default:
      break;
  }
}

static inline void PROCESSOR_TC_Disable(
    processor_tc_instance_t  timer
  )
{
  switch( timer )
  {
    case PROCESSOR_TC_INSTANCE_TC3:
      TC3->COUNT32.CTRLA.bit.ENABLE = 0;
      while( TC3->COUNT32.STATUS.bit.SYNCBUSY );
      break;
    case PROCESSOR_TC_INSTANCE_TC4:
      TC4->COUNT32.CTRLA.bit.ENABLE = 0;
      while( TC4->COUNT32.STATUS.bit.SYNCBUSY );
      break;
    case PROCESSOR_TC_INSTANCE_TC5:
      TC5->COUNT32.CTRLA.bit.ENABLE = 0;
      while( TC5->COUNT32.STATUS.bit.SYNCBUSY );
      break;
    default:
      break;
  }
}


static inline void PROCESSOR_TC_Waveform_Set(
    processor_tc_instance_t  timer,
    processor_tc_waveform_t  waveform
  )
{
  switch( timer )
  {
    case PROCESSOR_TC_INSTANCE_TC3:
      TC3->COUNT32.CTRLA.bit.WAVEGEN = waveform;
      break;
    case PROCESSOR_TC_INSTANCE_TC4:
      TC4->COUNT32.CTRLA.bit.WAVEGEN = waveform;
      break;
    case PROCESSOR_TC_INSTANCE_TC5:
      TC5->COUNT32.CTRLA.bit.WAVEGEN = waveform;
      break;
    default:
      break;
  }
}


static inline void PROCESSOR_TC_Period_Set(
    processor_tc_instance_t  timer,
    uint32_t                 period
  )
{
  switch( timer )
  {
    case PROCESSOR_TC_INSTANCE_TC3:
      TC3->COUNT8.PER.reg = period;
      while( TC3->COUNT8.STATUS.bit.SYNCBUSY );
      break;
    case PROCESSOR_TC_INSTANCE_TC4:
      TC4->COUNT8.PER.reg = period;
      while( TC4->COUNT8.STATUS.bit.SYNCBUSY );
      break;
    case PROCESSOR_TC_INSTANCE_TC5:
      TC5->COUNT8.PER.reg = period;
      while( TC5->COUNT8.STATUS.bit.SYNCBUSY );
      break;
    default:
      break;
  }
}

static inline void PROCESSOR_TC_Count_Set(
    processor_tc_instance_t  timer,
    uint32_t                 count
  )
{
  switch( timer )
  {
    case PROCESSOR_TC_INSTANCE_TC3:
      TC3->COUNT32.COUNT.reg = count;
      while( TC3->COUNT32.STATUS.bit.SYNCBUSY );
      break;
    case PROCESSOR_TC_INSTANCE_TC4:
      TC4->COUNT32.COUNT.reg = count;
      while( TC4->COUNT32.STATUS.bit.SYNCBUSY );
      break;
    case PROCESSOR_TC_INSTANCE_TC5:
      TC5->COUNT32.COUNT.reg = count;
      while( TC5->COUNT32.STATUS.bit.SYNCBUSY );
      break;
    default:
      break;
  }
}

static inline uint32_t PROCESSOR_TC_Count_Get(
    processor_tc_instance_t  timer
  )
{
  switch( timer )
  {
    case PROCESSOR_TC_INSTANCE_TC3:
      TC3->COUNT32.READREQ.reg = TC_READREQ_RREQ | TC_READREQ_ADDR(offsetof(TcCount32, COUNT.reg));
      while( TC3->COUNT32.STATUS.bit.SYNCBUSY );
      return TC3->COUNT32.COUNT.reg;
    case PROCESSOR_TC_INSTANCE_TC4:
      TC4->COUNT32.READREQ.reg = TC_READREQ_RREQ | TC_READREQ_ADDR(offsetof(TcCount32, COUNT.reg));
      while( TC4->COUNT32.STATUS.bit.SYNCBUSY );
      return TC4->COUNT32.COUNT.reg;
    case PROCESSOR_TC_INSTANCE_TC5:
      TC5->COUNT32.READREQ.reg = TC_READREQ_RREQ | TC_READREQ_ADDR(offsetof(TcCount32, COUNT.reg));
      while( TC5->COUNT32.STATUS.bit.SYNCBUSY );
      return TC5->COUNT32.COUNT.reg;
    default:
      return 0;
  }
}

static inline void PROCESSOR_TC_Compare_Set(
    processor_tc_instance_t  timer,
    processor_tc_channel_t   channel,
    uint32_t                 compare
  )
{
  switch( timer )
  {
    case PROCESSOR_TC_INSTANCE_TC3:
      if( channel <= PROCESSOR_TC_CHANNEL_TC_MC1 )
      {
        TC3->COUNT32.CC[channel].reg = compare;
        while( TC3->COUNT32.STATUS.bit.SYNCBUSY );
      }
      break;
    case PROCESSOR_TC_INSTANCE_TC4:
      if( channel <= PROCESSOR_TC_CHANNEL_TC_MC1 )
      {
        TC4->COUNT32.CC[channel].reg = compare;
        while( TC4->COUNT32.STATUS.bit.SYNCBUSY );
      }
      break;
    case PROCESSOR_TC_INSTANCE_TC5:
      if( channel <= PROCESSOR_TC_CHANNEL_TC_MC1 )
      {
        TC5->COUNT32.CC[channel].reg = compare;
        while( TC5->COUNT32.STATUS.bit.SYNCBUSY );
      }
      break;
    default:
      break;
  }
}


static inline uint32_t PROCESSOR_TC_Capture_Get(
    processor_tc_instance_t  timer,
    processor_tc_channel_t   channel
  )
{
  switch( timer )
  {
    case PROCESSOR_TC_INSTANCE_TC3:
      if( channel <= PROCESSOR_TC_CHANNEL_TC_MC1 )
      {
        TC3->COUNT32.READREQ.reg = TC_READREQ_RREQ | TC_READREQ_ADDR(offsetof(TcCount32, CC[channel].reg));
        while( TC3->COUNT32.STATUS.bit.SYNCBUSY );
        return TC3->COUNT32.CC[channel].reg;
      }
      else
      {
        return 0;
      }
    case PROCESSOR_TC_INSTANCE_TC4:
      if( channel <= PROCESSOR_TC_CHANNEL_TC_MC1 )
      {
        TC4->COUNT32.READREQ.reg = TC_READREQ_RREQ | TC_READREQ_ADDR(offsetof(TcCount32, CC[channel].reg));
        while( TC4->COUNT32.STATUS.bit.SYNCBUSY );
        return TC4->COUNT32.CC[channel].reg;
      }
      else
      {
        return 0;
      }
    case PROCESSOR_TC_INSTANCE_TC5:
      if( channel <= PROCESSOR_TC_CHANNEL_TC_MC1 )
      {
        TC5->COUNT32.READREQ.reg = TC_READREQ_RREQ | TC_READREQ_ADDR(offsetof(TcCount32, CC[channel].reg));
        while( TC5->COUNT32.STATUS.bit.SYNCBUSY );
        return TC5->COUNT32.CC[channel].reg;
      }
      else
      {
        return 0;
      }
    default:
      return 0;
  }
}


static inline void PROCESSOR_TC_CMD_Retrigger(
    processor_tc_instance_t  timer
  )
{
  switch( timer )
  {
    case PROCESSOR_TC_INSTANCE_TC3:
      TC3->COUNT32.CTRLBSET.reg = TC_CTRLBSET_CMD_RETRIGGER;
      while( TC3->COUNT32.STATUS.bit.SYNCBUSY );
      break;
    case PROCESSOR_TC_INSTANCE_TC4:
      TC4->COUNT32.CTRLBSET.reg = TC_CTRLBSET_CMD_RETRIGGER;
      while( TC4->COUNT32.STATUS.bit.SYNCBUSY );
      break;
    case PROCESSOR_TC_INSTANCE_TC5:
      TC5->COUNT32.CTRLBSET.reg = TC_CTRLBSET_CMD_RETRIGGER;
      while( TC5->COUNT32.STATUS.bit.SYNCBUSY );
      break;
    default:
      break;
  }
}

static inline void PROCESSOR_TC_CMD_Stop(
    processor_tc_instance_t  timer
  )
{
  switch( timer )
  {
    case PROCESSOR_TC_INSTANCE_TC3:
      TC3->COUNT32.CTRLBSET.reg = TC_CTRLBSET_CMD_STOP;
      while( TC3->COUNT32.STATUS.bit.SYNCBUSY );
      break;
    case PROCESSOR_TC_INSTANCE_TC4:
      TC4->COUNT32.CTRLBSET.reg = TC_CTRLBSET_CMD_STOP;
      while( TC4->COUNT32.STATUS.bit.SYNCBUSY );
      break;
    case PROCESSOR_TC_INSTANCE_TC5:
      TC5->COUNT32.CTRLBSET.reg = TC_CTRLBSET_CMD_STOP;
      while( TC5->COUNT32.STATUS.bit.SYNCBUSY );
      break;
    default:
      break;
  }
}


#ifdef __cplusplus
}
#endif

#endif  // ECLAY_PROCESSOR_TC_H