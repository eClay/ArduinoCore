#ifndef ECLAY_PROCESSOR_TC_H
#define ECLAY_PROCESSOR_TC_H

#include "processor/sam.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


#ifdef __cplusplus
extern "C" {
#endif

static const Tc* processor_tc_instance[TC_INST_NUM] = TC_INSTS;

typedef enum {
  PROCESSOR_TC_INSTANCE_TC3 = 0,
  PROCESSOR_TC_INSTANCE_TC4,
  PROCESSOR_TC_INSTANCE_TC5,
#if (TC_INST_NUM == 5)
  PROCESSOR_TC_INSTANCE_TC6,
  PROCESSOR_TC_INSTANCE_TC7,
#endif
  NUM_PROCESSOR_TC_INSTANCES,
  NOT_A_PROCESSOR_TC_INSTANCE = NUM_PROCESSOR_TC_INSTANCES
} processor_tc_instance_t;

typedef enum {
  PROCESSOR_TC_MODE_8BIT  = 0x1,
  PROCESSOR_TC_MODE_16BIT = 0x0,
  PROCESSOR_TC_MODE_32BIT = 0x2,
} processor_tc_mode_t;

typedef enum {
  PROCESSOR_TC_CHANNEL_MC0 = 0,
  PROCESSOR_TC_CHANNEL_MC1 = 1,
} processor_tc_channel_t;

typedef enum {
  PROCESSOR_TC_OUTPUT_WO0 = 0,
  PROCESSOR_TC_OUTPUT_WO1 = 1,
} processor_tc_output_t;

typedef enum {
  PROCESSOR_TC_OUTPUT_PIN_WO0,
  PROCESSOR_TC_OUTPUT_PIN_WO1 = 1,
} processor_tc_4_output_PIN_t;

typedef enum {
  PROCESSOR_TC_PRESCALE_DIV1    = 0x0,
  PROCESSOR_TC_PRESCALE_DIV2    = 0x1,
  PROCESSOR_TC_PRESCALE_DIV4    = 0x2,
  PROCESSOR_TC_PRESCALE_DIV8    = 0x3,
  PROCESSOR_TC_PRESCALE_DIV16   = 0x4,
  PROCESSOR_TC_PRESCALE_DIV64   = 0x5,
  PROCESSOR_TC_PRESCALE_DIV256  = 0x6,
  PROCESSOR_TC_PRESCALE_DIV1024 = 0x7,
} processor_tc_prescale_t;

typedef enum {
  PROCESSOR_TC_WAVEFORM_NORMAL_FREQUENCY = 0x0,
  PROCESSOR_TC_WAVEFORM_MATCH_FREQUENCY  = 0x1,
  PROCESSOR_TC_WAVEFORM_NORMAL_PWM       = 0x2,
  PROCESSOR_TC_WAVEFORM_MATCH_PWM        = 0x3,
} processor_tc_waveform_t;

typedef enum {
  PROCESSOR_TC_DIRECTION_UP   = 0x0,
  PROCESSOR_TC_DIRECTION_DOWN = 0x1,
} processor_tc_direction_t;

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


void PROCESSOR_TC_Initialize( void );


static inline void PROCESSOR_TC_SoftwareReset(
    processor_tc_instance_t  timer
  );


static inline void PROCESSOR_TC_Enable(
    processor_tc_instance_t  timer
  );

static inline void PROCESSOR_TC_Disable(
    processor_tc_instance_t  timer
  );


static inline void PROCESSOR_TC_Prescaler_Set(
    processor_tc_instance_t  timer,
    processor_tc_prescale_t  prescale
  );

static inline processor_tc_prescale_t PROCESSOR_TC_Prescaler_Get(
    processor_tc_instance_t  timer
  );

static inline uint32_t PROCESSOR_TC_PrescalerDivisorValue_Get(
    processor_tc_instance_t  timer
  );

static inline uint32_t PROCESSOR_TC_PrescalerDivisorShift_Get(
    processor_tc_instance_t  timer
  );


static inline void PROCESSOR_TC_Waveform_Set(
    processor_tc_instance_t  timer,
    processor_tc_waveform_t  waveform
  );


static inline void PROCESSOR_TC_RunInStandby_Enable(
    processor_tc_instance_t  timer
  );

static inline void PROCESSOR_TC_RunInStandby_Disable(
    processor_tc_instance_t  timer
  );


static inline void PROCESSOR_TC_Direction_Set(
    processor_tc_instance_t  timer,
    processor_tc_direction_t direction
  );

static inline processor_tc_direction_t PROCESSOR_TC_Direction_Get(
    processor_tc_instance_t  timer
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


static inline void PROCESSOR_TC_INTERRUPT_Callback_Set(
    processor_tc_instance_t  timer,
    processor_tc_interrupt_t interrupt
  );

static inline void PROCESSOR_TC_INTERRUPT_Enable(
    processor_tc_instance_t  timer,
    processor_tc_interrupt_t interrupt
  );

static inline void PROCESSOR_TC_INTERRUPT_Disable(
    processor_tc_instance_t  timer,
    processor_tc_interrupt_t interrupt
  );


static inline void PROCESSOR_TC_CMD_Retrigger(
    processor_tc_instance_t  timer
  );

static inline void PROCESSOR_TC_CMD_Stop(
    processor_tc_instance_t  timer
  );


static inline void PROCESSOR_TC_Oneshot_Enable(
    processor_tc_instance_t  timer
  );

static inline void PROCESSOR_TC_Oneshot_Disable(
    processor_tc_instance_t  timer
  );


static inline void PROCESSOR_TC_Direction_Set(
    processor_tc_instance_t  timer
  );

static inline void PROCESSOR_TC_Direction_Get(
    processor_tc_instance_t  timer
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


static inline void PROCESSOR_TC_EVENT_Output_Enable(
    processor_tc_instance_t      timer,
    processor_tc_event_output_t  event
  );

static inline void PROCESSOR_TC_EVENT_Output_Disable(
    processor_tc_instance_t      timer,
    processor_tc_event_output_t  event
  );


//********************************************************
// INLINE FUNCTION DEFINITIONS
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


static inline void PROCESSOR_TC_Prescaler_Set(
    processor_tc_instance_t  timer,
    processor_tc_prescale_t  prescale
  )
{
  switch( timer )
  {
    case PROCESSOR_TC_INSTANCE_TC3:
      TC3->COUNT32.CTRLA.bit.PRESCALER = prescale;
      break;
    case PROCESSOR_TC_INSTANCE_TC4:
      TC4->COUNT32.CTRLA.bit.PRESCALER = prescale;
      break;
    case PROCESSOR_TC_INSTANCE_TC5:
      TC5->COUNT32.CTRLA.bit.PRESCALER = prescale;
      break;
    default:
      break;
  }
}

static inline processor_tc_prescale_t PROCESSOR_TC_Prescaler_Get(
    processor_tc_instance_t  timer
  )
{
  switch( timer )
  {
    case PROCESSOR_TC_INSTANCE_TC3:
      return TC3->COUNT32.CTRLA.bit.PRESCALER;
    case PROCESSOR_TC_INSTANCE_TC4:
      return TC4->COUNT32.CTRLA.bit.PRESCALER;
    case PROCESSOR_TC_INSTANCE_TC5:
      return TC5->COUNT32.CTRLA.bit.PRESCALER;
    default:
      return PROCESSOR_TC_PRESCALE_DIV1;
  }
}

static inline uint16_t PROCESSOR_TC_PrescalerDivisorValue_Get(
    processor_tc_instance_t  timer
  )
{
  switch( PROCESSOR_TC_Prescaler_Get(timer) )
  {
    case PROCESSOR_TC_PRESCALE_DIV1:
      return 1;
    case PROCESSOR_TC_PRESCALE_DIV2:
      return 2;
    case PROCESSOR_TC_PRESCALE_DIV4:
      return 4;
    case PROCESSOR_TC_PRESCALE_DIV8:
      return 8;
    case PROCESSOR_TC_PRESCALE_DIV16:
      return 16;
    case PROCESSOR_TC_PRESCALE_DIV64:
      return 64;
    case PROCESSOR_TC_PRESCALE_DIV256:
      return 256;
    case PROCESSOR_TC_PRESCALE_DIV1024:
      return 1024;
    default:
      return 1;
  }
}

static inline uint32_t PROCESSOR_TC_PrescalerDivisorShift_Get(
    processor_tc_instance_t  timer
  )
{
  switch( PROCESSOR_TC_Prescaler_Get(timer) )
  {
    case PROCESSOR_TC_PRESCALE_DIV1:
      return 0;
    case PROCESSOR_TC_PRESCALE_DIV2:
      return 1;
    case PROCESSOR_TC_PRESCALE_DIV4:
      return 2;
    case PROCESSOR_TC_PRESCALE_DIV8:
      return 3;
    case PROCESSOR_TC_PRESCALE_DIV16:
      return 4;
    case PROCESSOR_TC_PRESCALE_DIV64:
      return 6;
    case PROCESSOR_TC_PRESCALE_DIV256:
      return 8;
    case PROCESSOR_TC_PRESCALE_DIV1024:
      return 10;
    default:
      return 0;
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


static inline __IO uint32_t* PROCESSOR_TC_EVCTRL_Register(
    processor_tc_instance_t  timer
  )
{
  switch( timer )
  {
    case PROCESSOR_TC_INSTANCE_TC3:
      return (__IO uint32_t*)TC3->COUNT32.EVCTRL.reg;
    case PROCESSOR_TC_INSTANCE_TC4:
      return (__IO uint32_t*)TC4->COUNT32.EVCTRL.reg;
    case PROCESSOR_TC_INSTANCE_TC5:
      return (__IO uint32_t*)TC5->COUNT32.EVCTRL.reg;
    default:
      return NULL;
  }
}


static inline void PROCESSOR_TC_EVENT_Input_Enable(
    processor_tc_instance_t      timer,
    processor_tc_event_input_t   event
  )
{
  __IO uint32_t* evctrl_reg = PROCESSOR_TC_EVCTRL_Register(timer);

  if( evctrl_reg != NULL )
  {
    switch( event )
    {
      case PROCESSOR_TC_EVENT_INPUT_MC0:
        *evctrl_reg |= TC_EVCTRL_MCEO0;
        break;
      case PROCESSOR_TC_EVENT_INPUT_MC1:
        *evctrl_reg |= TC_EVCTRL_MCEO1;
        break;
      case PROCESSOR_TC_EVENT_INPUT_EV:
        *evctrl_reg &= ~TC_EVCTRL_TCINV;
        *evctrl_reg |= TC_EVCTRL_TCEI;
        break;
      case PROCESSOR_TC_EVENT_INPUT_EV_INVERTED:
        *evctrl_reg |= (TC_EVCTRL_TCEI | TC_EVCTRL_TCINV);
        break;
      default:
        break;
    }
  }
}

static inline void PROCESSOR_TC_EVENT_Input_Disable(
    processor_tc_instance_t      timer,
    processor_tc_event_input_t   event
  )
{
  __IO uint32_t* evctrl_reg = PROCESSOR_TC_EVCTRL_Register(timer);

  if( evctrl_reg != NULL )
  {
    switch( event )
    {
      case PROCESSOR_TC_EVENT_INPUT_MC0:
        *evctrl_reg &= ~TC_EVCTRL_MCEO0;
        break;
      case PROCESSOR_TC_EVENT_INPUT_MC1:
        *evctrl_reg &= ~TC_EVCTRL_MCEO1;
        break;
      case PROCESSOR_TC_EVENT_INPUT_EV:
        *evctrl_reg &= ~TC_EVCTRL_TCEI;
        break;
      case PROCESSOR_TC_EVENT_INPUT_EV_INVERTED:
        *evctrl_reg &= ~TC_EVCTRL_TCEI;
        break;
      default:
        break;
    }
  }
}

static inline void PROCESSOR_TC_EVENT_InputAction_Set(
    processor_tc_instance_t            timer,
    processor_tc_event_input_action_t action
  )
{

}


static inline void PROCESSOR_TC_EVENT_Output_Enable(
    processor_tc_instance_t      timer,
    processor_tc_event_output_t  event
  )
{
  __IO uint32_t* evctrl_reg = PROCESSOR_TC_EVCTRL_Register(timer);

  if( evctrl_reg != NULL )
  {
    switch( event )
    {
      case PROCESSOR_TC_EVENT_OUTPUT_MC0:
        *evctrl_reg |= TC_EVCTRL_MCEO0;
        break;
      case PROCESSOR_TC_EVENT_OUTPUT_MC1:
        *evctrl_reg |= TC_EVCTRL_MCEO1;
        break;
      case PROCESSOR_TC_EVENT_OUTPUT_OVERFLOW:
        *evctrl_reg |= TC_EVCTRL_OVFEO;
        break;
      default:
        break;
    }
  }
}

static inline void PROCESSOR_TC_EVENT_Output_Disable(
    processor_tc_instance_t      timer,
    processor_tc_event_output_t  event
  )
{
  __IO uint32_t* evctrl_reg = PROCESSOR_TC_EVCTRL_Register(timer);

  if( evctrl_reg != NULL )
  {
    switch( event )
    {
      case PROCESSOR_TC_EVENT_OUTPUT_MC0:
        *evctrl_reg &= ~TC_EVCTRL_MCEO0;
        break;
      case PROCESSOR_TC_EVENT_OUTPUT_MC1:
        *evctrl_reg &= ~TC_EVCTRL_MCEO1;
        break;
      case PROCESSOR_TC_EVENT_OUTPUT_OVERFLOW:
        *evctrl_reg &= ~TC_EVCTRL_OVFEO;
        break;
      default:
        break;
    }
  }
}


#ifdef __cplusplus
}
#endif

#endif  // ECLAY_PROCESSOR_TC_H
