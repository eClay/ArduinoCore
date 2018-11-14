#ifndef ECLAY_PROCESSOR_TCC_H
#define ECLAY_PROCESSOR_TCC_H

#include "processor/sam.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
  PROCESSOR_TCC_INSTANCE_TCC0 = 0,
  PROCESSOR_TCC_INSTANCE_TCC1,
  PROCESSOR_TCC_INSTANCE_TCC2,
  NUM_PROCESSOR_TCC_INSTANCES,
  NOT_A_PROCESSOR_TCC_INSTANCE = NUM_PROCESSOR_TCC_INSTANCES
} processor_tcc_instance_t;

typedef enum {
  PROCESSOR_TCC_CHANNEL_MC0 = 0,
  PROCESSOR_TCC_CHANNEL_MC1 = 1,
  PROCESSOR_TCC_CHANNEL_MC2 = 2,
  PROCESSOR_TCC_CHANNEL_MC3 = 3,
} processor_tcc_channel_t;

typedef enum {
  PROCESSOR_TCC_WAVEFORM_NORMAL_FREQUENCY    = 0x0,
  PROCESSOR_TCC_WAVEFORM_MATCH_FREQUENCY     = 0x1,
  PROCESSOR_TCC_WAVEFORM_NORMAL_PWM          = 0x2,
  PROCESSOR_TCC_WAVEFORM_DUAL_SLOPE_CRITICAL = 0x4,
  PROCESSOR_TCC_WAVEFORM_DUAL_SLOPE_BOTTOM   = 0x5,
  PROCESSOR_TCC_WAVEFORM_DUAL_SLOPE_BOTH     = 0x6,
  PROCESSOR_TCC_WAVEFORM_DUAL_SLOPE_TOP      = 0x7,
} processor_tcc_waveform_t;

typedef enum {
  PROCESSOR_TCC_INTERRUPT_MC0 = 0,
  PROCESSOR_TCC_INTERRUPT_MC1,
  PROCESSOR_TCC_INTERRUPT_MC2,
  PROCESSOR_TCC_INTERRUPT_MC3,
  PROCESSOR_TCC_INTERRUPT_FAULT0,
  PROCESSOR_TCC_INTERRUPT_FAULT1,
  PROCESSOR_TCC_INTERRUPT_FAULTA,
  PROCESSOR_TCC_INTERRUPT_FAULTB,
  PROCESSOR_TCC_INTERRUPT_FAULT_DEBUG,
  PROCESSOR_TCC_INTERRUPT_FAULT_UPDATE,
  PROCESSOR_TCC_INTERRUPT_ERROR,
  PROCESSOR_TCC_INTERRUPT_COUNTER,
  PROCESSOR_TCC_INTERRUPT_RETRIGGER,
  PROCESSOR_TCC_INTERRUPT_OVERFLOW,
} processor_tcc_interrupt_t;

typedef enum {
  PROCESSOR_TCC_EVENT_INPUT_MC0 = 0,
  PROCESSOR_TCC_EVENT_INPUT_MC1,
  PROCESSOR_TCC_EVENT_INPUT_MC2,
  PROCESSOR_TCC_EVENT_INPUT_MC3,
  PROCESSOR_TCC_EVENT_INPUT_EV0,
  PROCESSOR_TCC_EVENT_INPUT_EV0_INVERTED,
  PROCESSOR_TCC_EVENT_INPUT_EV1,
  PROCESSOR_TCC_EVENT_INPUT_EV1_INVERTED
} processor_tcc_event_input_t;

typedef enum {
  PROCESSOR_TCC_EVENT_INPUT0_ACTION_OFF          = 0x0,
  PROCESSOR_TCC_EVENT_INPUT0_ACTION_RETRIGGER    = 0x1,
  PROCESSOR_TCC_EVENT_INPUT0_ACTION_COUNT_EVENT  = 0x2,
  PROCESSOR_TCC_EVENT_INPUT0_ACTION_START        = 0x3,
  PROCESSOR_TCC_EVENT_INPUT0_ACTION_INCREMENT    = 0x4,
  PROCESSOR_TCC_EVENT_INPUT0_ACTION_COUNT_ASYNC  = 0x5,
  PROCESSOR_TCC_EVENT_INPUT0_ACTION_FAULT        = 0x7,
} processor_tcc_event_input0_action_t;

typedef enum {
  PROCESSOR_TCC_EVENT_INPUT1_ACTION_OFF          = 0x0,
  PROCESSOR_TCC_EVENT_INPUT1_ACTION_RETRIGGER    = 0x1,
  PROCESSOR_TCC_EVENT_INPUT1_ACTION_DIR_ASYNC    = 0x2,
  PROCESSOR_TCC_EVENT_INPUT1_ACTION_STOP         = 0x3,
  PROCESSOR_TCC_EVENT_INPUT1_ACTION_DECREMENT    = 0x4,
  PROCESSOR_TCC_EVENT_INPUT1_ACTION_PPW          = 0x5,
  PROCESSOR_TCC_EVENT_INPUT1_ACTION_PWP          = 0x6,
  PROCESSOR_TCC_EVENT_INPUT1_ACTION_FAULT        = 0x7,
} processor_tcc_event_input1_action_t;

typedef enum {
  PROCESSOR_TCC_EVENT_OUTPUT_MC0 = 0,
  PROCESSOR_TCC_EVENT_OUTPUT_MC1,
  PROCESSOR_TCC_EVENT_OUTPUT_MC2,
  PROCESSOR_TCC_EVENT_OUTPUT_MC3,
  PROCESSOR_TCC_EVENT_OUTPUT_COUNT,
  PROCESSOR_TCC_EVENT_OUTPUT_RETRIGGER,
  PROCESSOR_TCC_EVENT_OUTPUT_OVERFLOW,
} processor_tcc_event_output_t;

typedef enum {
  PROCESSOR_TCC_EVENT_COUNT_MODE_BEGIN    = 0x0,
  PROCESSOR_TCC_EVENT_COUNT_MODE_END      = 0x1,
  PROCESSOR_TCC_EVENT_COUNT_MODE_BETWEEN  = 0x2,
  PROCESSOR_TCC_EVENT_COUNT_MODE_BOUNDARY = 0x3,
} processor_tcc_event_count_mode_t;


void PROCESSOR_TCC_InitializeAll( void );


static inline void PROCESSOR_TCC_SoftwareReset(
    processor_tcc_instance_t  timer
  );


static inline void PROCESSOR_TCC_Enable(
    processor_tcc_instance_t  timer
  );

static inline void PROCESSOR_TCC_Disable(
    processor_tcc_instance_t  timer
  );


static inline void PROCESSOR_TCC_Waveform_Set(
    processor_tcc_instance_t  timer,
    processor_tcc_waveform_t  waveform
  );


static inline void PROCESSOR_TCC_Period_Set(
    processor_tcc_instance_t  timer,
    uint32_t                  period
  );

static inline void PROCESSOR_TCC_Count_Set(
    processor_tcc_instance_t  timer,
    uint32_t                  count
  );

static inline uint32_t PROCESSOR_TCC_Count_Get(
    processor_tcc_instance_t  timer
  );

static inline void PROCESSOR_TCC_Compare_Set(
    processor_tcc_instance_t  timer,
    processor_tcc_channel_t   channel,
    uint32_t                  compare
  );

static inline uint32_t PROCESSOR_TCC_Capture_Get(
    processor_tcc_instance_t  timer,
    processor_tcc_channel_t   channel
  );


static inline void PROCESSOR_TCC_Pattern_Set(
    processor_tcc_instance_t  timer,
    uint8_t                   enable,
    uint8_t                   value
  );

static inline void PROCESSOR_TCC_PatternEnable_Set(
    processor_tcc_instance_t  timer,
    uint8_t                   enable
  );

static inline void PROCESSOR_TCC_PatternValue_Set(
    processor_tcc_instance_t  timer,
    uint8_t                   value
  );

static inline __IO uint16_t* PROCESSOR_TCC_PatternRegister(
    processor_tcc_instance_t  timer
  );

static inline __IO uint8_t* PROCESSOR_TCC_PatternRegisterEnable(
    processor_tcc_instance_t  timer
  );

static inline __IO uint8_t* PROCESSOR_TCC_PatternRegisterValue(
    processor_tcc_instance_t  timer
  );


static inline void PROCESSOR_TCC_CMD_Retrigger(
    processor_tcc_instance_t  timer
  );

static inline void PROCESSOR_TCC_CMD_Stop(
    processor_tcc_instance_t  timer
  );

static inline void PROCESSOR_TCC_CMD_Update(
    processor_tcc_instance_t  timer
  );

static inline void PROCESSOR_TCC_CMD_ReadSync(
    processor_tcc_instance_t  timer
  );


static inline void PROCESSOR_TCC_EVENT_Input_Enable(
    processor_tcc_instance_t      timer,
    processor_tcc_event_input_t   event
  );

static inline void PROCESSOR_TCC_EVENT_Input_Disable(
    processor_tcc_instance_t      timer,
    processor_tcc_event_input_t   event
  );

static inline void PROCESSOR_TCC_EVENT_InputAction0_Set(
    processor_tcc_instance_t            timer,
    processor_tcc_event_input0_action_t action
  );

static inline void PROCESSOR_TCC_EVENT_InputAction1_Set(
    processor_tcc_instance_t            timer,
    processor_tcc_event_input1_action_t action
  );


static inline void PROCESSOR_TCC_EVENT_Output_Enable(
    processor_tcc_instance_t      timer,
    processor_tcc_event_output_t  event
  );

static inline void PROCESSOR_TCC_EVENT_Output_Disable(
    processor_tcc_instance_t      timer,
    processor_tcc_event_output_t  event
  );

static inline void PROCESSOR_TCC_EVENT_CountMode_Set(
    processor_tcc_instance_t          timer,
    processor_tcc_event_count_mode_t  mode
  );


//********************************************************
// INLINE FUNCTION DEFINITIONS
//********************************************************

static inline void PROCESSOR_TCC_SoftwareReset(
    processor_tcc_instance_t  timer
  )
{
  switch( timer )
  {
    case PROCESSOR_TCC_INSTANCE_TCC0:
      TCC0->CTRLA.bit.SWRST = 1;
      while( TCC0->CTRLA.bit.SWRST );
      break;
    case PROCESSOR_TCC_INSTANCE_TCC1:
      TCC1->CTRLA.bit.SWRST = 1;
      while( TCC1->CTRLA.bit.SWRST );
      break;
    case PROCESSOR_TCC_INSTANCE_TCC2:
      TCC2->CTRLA.bit.SWRST = 1;
      while( TCC2->CTRLA.bit.SWRST );
      break;
    default:
      break;
  }
}


static inline void PROCESSOR_TCC_Enable(
    processor_tcc_instance_t  timer
  )
{
  switch( timer )
  {
    case PROCESSOR_TCC_INSTANCE_TCC0:
      TCC0->CTRLA.bit.ENABLE = 1;
      while( TCC0->SYNCBUSY.bit.ENABLE );
      break;
    case PROCESSOR_TCC_INSTANCE_TCC1:
      TCC1->CTRLA.bit.ENABLE = 1;
      while( TCC1->SYNCBUSY.bit.ENABLE );
      break;
    case PROCESSOR_TCC_INSTANCE_TCC2:
      TCC2->CTRLA.bit.ENABLE = 1;
      while( TCC2->SYNCBUSY.bit.ENABLE );
      break;
    default:
      break;
  }
}

static inline void PROCESSOR_TCC_Disable(
    processor_tcc_instance_t  timer
  )
{
  switch( timer )
  {
    case PROCESSOR_TCC_INSTANCE_TCC0:
      TCC0->CTRLA.bit.ENABLE = 0;
      while( TCC0->SYNCBUSY.bit.ENABLE );
      break;
    case PROCESSOR_TCC_INSTANCE_TCC1:
      TCC1->CTRLA.bit.ENABLE = 0;
      while( TCC1->SYNCBUSY.bit.ENABLE );
      break;
    case PROCESSOR_TCC_INSTANCE_TCC2:
      TCC2->CTRLA.bit.ENABLE = 0;
      while( TCC2->SYNCBUSY.bit.ENABLE );
      break;
    default:
      break;
  }
}


static inline void PROCESSOR_TCC_Waveform_Set(
    processor_tcc_instance_t  timer,
    processor_tcc_waveform_t  waveform
  )
{
  switch( timer )
  {
    case PROCESSOR_TCC_INSTANCE_TCC0:
      TCC0->WAVE.bit.WAVEGEN = waveform;
      break;
    case PROCESSOR_TCC_INSTANCE_TCC1:
      TCC1->WAVE.bit.WAVEGEN = waveform;
      break;
    case PROCESSOR_TCC_INSTANCE_TCC2:
      TCC2->WAVE.bit.WAVEGEN = waveform;
      break;
    default:
      break;
  }
}


static inline void PROCESSOR_TCC_Period_Set(
    processor_tcc_instance_t  timer,
    uint32_t                  period
  )
{
  switch( timer )
  {
    case PROCESSOR_TCC_INSTANCE_TCC0:
      TCC0->PER.reg = period;
      while( TCC0->SYNCBUSY.bit.PER );
      break;
    case PROCESSOR_TCC_INSTANCE_TCC1:
      TCC1->PER.reg = period;
      while( TCC1->SYNCBUSY.bit.PER );
      break;
    case PROCESSOR_TCC_INSTANCE_TCC2:
      TCC2->PER.reg = period;
      while( TCC2->SYNCBUSY.bit.PER );
      break;
    default:
      break;
  }
}

static inline void PROCESSOR_TCC_Count_Set(
    processor_tcc_instance_t  timer,
    uint32_t                  count
  )
{
  switch( timer )
  {
    case PROCESSOR_TCC_INSTANCE_TCC0:
      TCC0->COUNT.reg = count;
      while( TCC0->SYNCBUSY.bit.COUNT );
      break;
    case PROCESSOR_TCC_INSTANCE_TCC1:
      TCC1->COUNT.reg = count;
      while( TCC1->SYNCBUSY.bit.COUNT );
      break;
    case PROCESSOR_TCC_INSTANCE_TCC2:
      TCC2->COUNT.reg = count;
      while( TCC2->SYNCBUSY.bit.COUNT );
      break;
    default:
      break;
  }
}

static inline uint32_t PROCESSOR_TCC_Count_Get(
    processor_tcc_instance_t  timer
  )
{
  switch( timer )
  {
    case PROCESSOR_TCC_INSTANCE_TCC0:
      TCC0->CTRLBSET.reg = TCC_CTRLBSET_CMD_READSYNC;
      while( TCC0->SYNCBUSY.reg & (TCC_SYNCBUSY_CTRLB | TCC_SYNCBUSY_COUNT) );
      return TCC0->COUNT.reg;
    case PROCESSOR_TCC_INSTANCE_TCC1:
      TCC1->CTRLBSET.reg = TCC_CTRLBSET_CMD_READSYNC;
      while( TCC1->SYNCBUSY.reg & (TCC_SYNCBUSY_CTRLB | TCC_SYNCBUSY_COUNT) );
      return TCC1->COUNT.reg;
    case PROCESSOR_TCC_INSTANCE_TCC2:
      TCC2->CTRLBSET.reg = TCC_CTRLBSET_CMD_READSYNC;
      while( TCC2->SYNCBUSY.reg & (TCC_SYNCBUSY_CTRLB | TCC_SYNCBUSY_COUNT) );
      return TCC2->COUNT.reg;
    default:
      return 0;
  }
}

static inline void PROCESSOR_TCC_Compare_Set(
    processor_tcc_instance_t  timer,
    processor_tcc_channel_t   channel,
    uint32_t                    compare
  )
{
  switch( timer )
  {
    case PROCESSOR_TCC_INSTANCE_TCC0:
      if( channel <= PROCESSOR_TCC_CHANNEL_TCC_MC3 )
      {
        TCC0->CC[channel].reg = compare;
        while( TCC0->SYNCBUSY.reg | (TCC_SYNCBUSY_CC0 << channel) );
      }
      break;
    case PROCESSOR_TCC_INSTANCE_TCC1:
      if( channel <= PROCESSOR_TCC_CHANNEL_TCC_MC1 )
      {
        TCC1->CC[channel].reg = compare;
        while( TCC1->SYNCBUSY.reg | (TCC_SYNCBUSY_CC0 << channel) );
      }
      break;
    case PROCESSOR_TCC_INSTANCE_TCC2:
      if( channel <= PROCESSOR_TCC_CHANNEL_TCC_MC1 )
      {
        TCC2->CC[channel].reg = compare;
        while( TCC2->SYNCBUSY.reg | (TCC_SYNCBUSY_CC0 << channel) );
      }
      break;
    default:
      break;
  }
}

static inline uint32_t PROCESSOR_TCC_Capture_Get(
    processor_tcc_instance_t  timer,
    processor_tcc_channel_t   channel
  )
{
  switch( timer )
  {
    case PROCESSOR_TCC_INSTANCE_TCC0:
      if( channel <= PROCESSOR_TCC_CHANNEL_TCC_MC3 )
      {
        return TCC0->CC[channel].reg;
      }
      else
      {
        return 0;
      }
    case PROCESSOR_TCC_INSTANCE_TCC1:
      if( channel <= PROCESSOR_TCC_CHANNEL_TCC_MC1 )
      {
        return TCC1->CC[channel].reg;
      }
      else
      {
        return 0;
      }
    case PROCESSOR_TCC_INSTANCE_TCC2:
      if( channel <= PROCESSOR_TCC_CHANNEL_TCC_MC1 )
      {
        return TCC2->CC[channel].reg;
      }
      else
      {
        return 0;
      }
    default:
      return 0;
  }
}


static inline void PROCESSOR_TCC_Pattern_Set(
    processor_tcc_instance_t  timer,
    uint8_t                     enable,
    uint8_t                     value
  )
{
  switch( timer )
  {
    case PROCESSOR_TCC_INSTANCE_TCC0:
      TCC0->PATT.reg = TCC_PATT_PGE(enable) | TCC_PATT_PGV(value);
      while( TCC0->SYNCBUSY.bit.PATT );
      break;
    case PROCESSOR_TCC_INSTANCE_TCC1:
      TCC1->PATT.reg = TCC_PATT_PGE(enable) | TCC_PATT_PGV(value);
      while( TCC1->SYNCBUSY.bit.PATT );
      break;
    case PROCESSOR_TCC_INSTANCE_TCC2:
      break;
    default:
      break;
  }
}

static inline void PROCESSOR_TCC_PatternEnable_Set(
    processor_tcc_instance_t  timer,
    uint8_t                   enable
  )
{
  switch( timer )
  {
    case PROCESSOR_TCC_INSTANCE_TCC0:
      *((__IO uint8_t*)TCC0->PATT.reg) = enable;
      while( TCC0->SYNCBUSY.bit.PATT );
      break;
    case PROCESSOR_TCC_INSTANCE_TCC1:
      *((__IO uint8_t*)TCC1->PATT.reg) = enable;
      while( TCC1->SYNCBUSY.bit.PATT );
      break;
    case PROCESSOR_TCC_INSTANCE_TCC2:
      break;
    default:
      break;
  }
}

static inline void PROCESSOR_TCC_PatternValue_Set(
    processor_tcc_instance_t  timer,
    uint8_t                   value
  )
{
  switch( timer )
  {
    case PROCESSOR_TCC_INSTANCE_TCC0:
      *((__IO uint8_t*)TCC0->PATT.reg + 1) = value;
      while( TCC0->SYNCBUSY.bit.PATT );
      break;
    case PROCESSOR_TCC_INSTANCE_TCC1:
      *((__IO uint8_t*)TCC1->PATT.reg + 1) = value;
      while( TCC1->SYNCBUSY.bit.PATT );
      break;
    case PROCESSOR_TCC_INSTANCE_TCC2:
      break;
    default:
      break;
  }
}

static inline __IO uint16_t* PROCESSOR_TCC_PatternRegister(
    processor_tcc_instance_t  timer
  )
{
  switch( timer )
  {
    case PROCESSOR_TCC_INSTANCE_TCC0:
      return (__IO uint16_t*)TCC0->PATT.reg;
    case PROCESSOR_TCC_INSTANCE_TCC1:
      return (__IO uint16_t*)TCC1->PATT.reg;
    case PROCESSOR_TCC_INSTANCE_TCC2:
      return NULL;
    default:
      return NULL;
  }
}

static inline __IO uint8_t* PROCESSOR_TCC_PatternRegisterEnable(
    processor_tcc_instance_t  timer
  )
{
  switch( timer )
  {
    case PROCESSOR_TCC_INSTANCE_TCC0:
      return (__IO uint8_t*)TCC0->PATT.reg;
    case PROCESSOR_TCC_INSTANCE_TCC1:
      return (__IO uint8_t*)TCC1->PATT.reg;
    case PROCESSOR_TCC_INSTANCE_TCC2:
      return NULL;
    default:
      return NULL;
  }
}

static inline __IO uint8_t* PROCESSOR_TCC_PatternRegisterValue(
    processor_tcc_instance_t  timer
  )
{
  switch( timer )
  {
    case PROCESSOR_TCC_INSTANCE_TCC0:
      return (__IO uint8_t*)TCC0->PATT.reg + 1;
    case PROCESSOR_TCC_INSTANCE_TCC1:
      return (__IO uint8_t*)TCC1->PATT.reg + 1;
    case PROCESSOR_TCC_INSTANCE_TCC2:
      return NULL;
    default:
      return NULL;
  }
}

static inline void PROCESSOR_TCC_CMD_Retrigger(
    processor_tcc_instance_t  timer
  )
{
  switch( timer )
  {
    case PROCESSOR_TCC_INSTANCE_TCC0:
      TCC0->CTRLBSET.reg = TCC_CTRLBSET_CMD_RETRIGGER;
      while( TCC0->SYNCBUSY.bit.CTRLB );
      break;
    case PROCESSOR_TCC_INSTANCE_TCC1:
      TCC1->CTRLBSET.reg = TCC_CTRLBSET_CMD_RETRIGGER;
      while( TCC1->SYNCBUSY.bit.CTRLB );
      break;
    case PROCESSOR_TCC_INSTANCE_TCC2:
      TCC2->CTRLBSET.reg = TCC_CTRLBSET_CMD_RETRIGGER;
      while( TCC2->SYNCBUSY.bit.CTRLB );
      break;
    default:
      break;
  }
}

static inline void PROCESSOR_TCC_CMD_Stop(
    processor_tcc_instance_t  timer
  )
{
  switch( timer )
  {
    case PROCESSOR_TCC_INSTANCE_TCC0:
      TCC0->CTRLBSET.reg = TCC_CTRLBSET_CMD_STOP;
      while( TCC0->SYNCBUSY.bit.CTRLB );
      break;
    case PROCESSOR_TCC_INSTANCE_TCC1:
      TCC1->CTRLBSET.reg = TCC_CTRLBSET_CMD_STOP;
      while( TCC1->SYNCBUSY.bit.CTRLB );
      break;
    case PROCESSOR_TCC_INSTANCE_TCC2:
      TCC2->CTRLBSET.reg = TCC_CTRLBSET_CMD_STOP;
      while( TCC2->SYNCBUSY.bit.CTRLB );
      break;
    default:
      break;
  }
}

static inline void PROCESSOR_TCC_CMD_Update(
    processor_tcc_instance_t  timer
  )
{
  switch( timer )
  {
    case PROCESSOR_TCC_INSTANCE_TCC0:
      TCC0->CTRLBSET.reg = TCC_CTRLBSET_CMD_UPDATE;
      while( TCC0->SYNCBUSY.bit.CTRLB );
      break;
    case PROCESSOR_TCC_INSTANCE_TCC1:
      TCC1->CTRLBSET.reg = TCC_CTRLBSET_CMD_UPDATE;
      while( TCC1->SYNCBUSY.bit.CTRLB );
      break;
    case PROCESSOR_TCC_INSTANCE_TCC2:
      TCC2->CTRLBSET.reg = TCC_CTRLBSET_CMD_UPDATE;
      while( TCC2->SYNCBUSY.bit.CTRLB );
      break;
    default:
      break;
  }
}

static inline void PROCESSOR_TCC_CMD_ReadSync(
    processor_tcc_instance_t  timer
  )
{
  switch( timer )
  {
    case PROCESSOR_TCC_INSTANCE_TCC0:
      TCC0->CTRLBSET.reg = TCC_CTRLBSET_CMD_READSYNC;
      while( TCC0->SYNCBUSY.bit.CTRLB );
      break;
    case PROCESSOR_TCC_INSTANCE_TCC1:
      TCC1->CTRLBSET.reg = TCC_CTRLBSET_CMD_READSYNC;
      while( TCC1->SYNCBUSY.bit.CTRLB );
      break;
    case PROCESSOR_TCC_INSTANCE_TCC2:
      TCC2->CTRLBSET.reg = TCC_CTRLBSET_CMD_READSYNC;
      while( TCC2->SYNCBUSY.bit.CTRLB );
      break;
    default:
      break;
  }
}


static inline __IO uint32_t* PROCESSOR_TCC_EVCTRL_Register(
    processor_tcc_instance_t  timer
  )
{
  switch( timer )
  {
    case PROCESSOR_TCC_INSTANCE_TCC0:
      return (__IO uint32_t*)TCC0->EVCTRL.reg;
    case PROCESSOR_TCC_INSTANCE_TCC1:
      return (__IO uint32_t*)TCC1->EVCTRL.reg;
    case PROCESSOR_TCC_INSTANCE_TCC2:
      return (__IO uint32_t*)TCC2->EVCTRL.reg;
    default:
      return NULL;
  }
}


static inline void PROCESSOR_TCC_EVENT_Input_Enable(
    processor_tcc_instance_t      timer,
    processor_tcc_event_input_t   event
  )
{
  __IO uint32_t* evctrl_reg = PROCESSOR_TCC_EVCTRL_Register(timer);

  if( evctrl_reg != NULL )
  {
    switch( event )
    {
      case PROCESSOR_TCC_EVENT_INPUT_MC0:
        *evctrl_reg |= TCC_EVCTRL_MCEI0;
        break;
      case PROCESSOR_TCC_EVENT_INPUT_MC1:
        *evctrl_reg |= TCC_EVCTRL_MCEI1;
        break;
      case PROCESSOR_TCC_EVENT_INPUT_MC2:
        *evctrl_reg |= TCC_EVCTRL_MCEI2;
        break;
      case PROCESSOR_TCC_EVENT_INPUT_MC3:
        *evctrl_reg |= TCC_EVCTRL_MCEI3;
        break;
      case PROCESSOR_TCC_EVENT_INPUT_EV0:
        *evctrl_reg &= ~TCC_EVCTRL_TCINV0;
        *evctrl_reg |= TCC_EVCTRL_TCEI0;
        break;
      case PROCESSOR_TCC_EVENT_INPUT_EV0_INVERTED:
        *evctrl_reg |= (TCC_EVCTRL_TCEI0 | TCC_EVCTRL_TCINV0);
        break;
      case PROCESSOR_TCC_EVENT_INPUT_EV1:
        *evctrl_reg &= ~TCC_EVCTRL_TCINV1;
        *evctrl_reg |= TCC_EVCTRL_TCEI1;
        break;
      case PROCESSOR_TCC_EVENT_INPUT_EV1_INVERTED:
        *evctrl_reg |= (TCC_EVCTRL_TCEI1 | TCC_EVCTRL_TCINV1);
        break;
      default:
        break;
    }
  }
}

static inline void PROCESSOR_TCC_EVENT_Input_Disable(
    processor_tcc_instance_t      timer,
    processor_tcc_event_input_t   event
  )
{
  __IO uint32_t* evctrl_reg = PROCESSOR_TCC_EVCTRL_Register(timer);

  if( evctrl_reg != NULL )
  {
    switch( event )
    {
      case PROCESSOR_TCC_EVENT_INPUT_MC0:
        *evctrl_reg &= ~TCC_EVCTRL_MCEI0;
        break;
      case PROCESSOR_TCC_EVENT_INPUT_MC1:
        *evctrl_reg &= ~TCC_EVCTRL_MCEI1;
        break;
      case PROCESSOR_TCC_EVENT_INPUT_MC2:
        *evctrl_reg &= ~TCC_EVCTRL_MCEI2;
        break;
      case PROCESSOR_TCC_EVENT_INPUT_MC3:
        *evctrl_reg &= ~TCC_EVCTRL_MCEI3;
        break;
      case PROCESSOR_TCC_EVENT_INPUT_EV0:
        *evctrl_reg &= ~TCC_EVCTRL_TCEI0;
        break;
      case PROCESSOR_TCC_EVENT_INPUT_EV0_INVERTED:
        *evctrl_reg &= ~TCC_EVCTRL_TCEI0;
        break;
      case PROCESSOR_TCC_EVENT_INPUT_EV1:
        *evctrl_reg &= ~TCC_EVCTRL_TCEI1;
        break;
      case PROCESSOR_TCC_EVENT_INPUT_EV1_INVERTED:
        *evctrl_reg &= ~TCC_EVCTRL_TCEI1;
        break;
      default:
        break;
    }
  }
}

static inline void PROCESSOR_TCC_EVENT_InputAction0_Set(
    processor_tcc_instance_t            timer,
    processor_tcc_event_input0_action_t action
  )
{
  switch( timer )
  {
    case PROCESSOR_TCC_INSTANCE_TCC0:
      TCC0->EVCTRL.bit.EVACT0 = action;
      break;
    case PROCESSOR_TCC_INSTANCE_TCC1:
      TCC1->EVCTRL.bit.EVACT0 = action;
      break;
    case PROCESSOR_TCC_INSTANCE_TCC2:
      TCC2->EVCTRL.bit.EVACT0 = action;
      break;
    default:
      break;
  }
}

static inline void PROCESSOR_TCC_EVENT_InputAction1_Set(
    processor_tcc_instance_t            timer,
    processor_tcc_event_input1_action_t action
  )
{
  switch( timer )
  {
    case PROCESSOR_TCC_INSTANCE_TCC0:
      TCC0->EVCTRL.bit.EVACT1 = action;
      break;
    case PROCESSOR_TCC_INSTANCE_TCC1:
      TCC1->EVCTRL.bit.EVACT1 = action;
      break;
    case PROCESSOR_TCC_INSTANCE_TCC2:
      TCC2->EVCTRL.bit.EVACT1 = action;
      break;
    default:
      break;
  }
}


static inline void PROCESSOR_TCC_EVENT_Output_Enable(
    processor_tcc_instance_t      timer,
    processor_tcc_event_output_t  event
  )
{
  __IO uint32_t* evctrl_reg = PROCESSOR_TCC_EVCTRL_Register(timer);

  if( evctrl_reg != NULL )
  {
    switch( event )
    {
      case PROCESSOR_TCC_EVENT_OUTPUT_MC0:
        *evctrl_reg |= TCC_EVCTRL_MCEO0;
        break;
      case PROCESSOR_TCC_EVENT_OUTPUT_MC1:
        *evctrl_reg |= TCC_EVCTRL_MCEO1;
        break;
      case PROCESSOR_TCC_EVENT_OUTPUT_MC2:
        *evctrl_reg |= TCC_EVCTRL_MCEO2;
        break;
      case PROCESSOR_TCC_EVENT_OUTPUT_MC3:
        *evctrl_reg |= TCC_EVCTRL_MCEO3;
        break;
      case PROCESSOR_TCC_EVENT_OUTPUT_COUNT:
        *evctrl_reg |= TCC_EVCTRL_CNTEO;
        break;
      case PROCESSOR_TCC_EVENT_OUTPUT_RETRIGGER:
        *evctrl_reg |= TCC_EVCTRL_TRGEO;
        break;
      case PROCESSOR_TCC_EVENT_OUTPUT_OVERFLOW:
        *evctrl_reg |= TCC_EVCTRL_OVFEO;
        break;
      default:
        break;
    }
  }
}

static inline void PROCESSOR_TCC_EVENT_Output_Disable(
    processor_tcc_instance_t      timer,
    processor_tcc_event_output_t  event
  )
{
  __IO uint32_t* evctrl_reg = PROCESSOR_TCC_EVCTRL_Register(timer);

  if( evctrl_reg != NULL )
  {
    switch( event )
    {
      case PROCESSOR_TCC_EVENT_OUTPUT_MC0:
        *evctrl_reg &= ~TCC_EVCTRL_MCEO0;
        break;
      case PROCESSOR_TCC_EVENT_OUTPUT_MC1:
        *evctrl_reg &= ~TCC_EVCTRL_MCEO1;
        break;
      case PROCESSOR_TCC_EVENT_OUTPUT_MC2:
        *evctrl_reg &= ~TCC_EVCTRL_MCEO2;
        break;
      case PROCESSOR_TCC_EVENT_OUTPUT_MC3:
        *evctrl_reg &= ~TCC_EVCTRL_MCEO3;
        break;
      case PROCESSOR_TCC_EVENT_OUTPUT_COUNT:
        *evctrl_reg &= ~TCC_EVCTRL_CNTEO;
        break;
      case PROCESSOR_TCC_EVENT_OUTPUT_RETRIGGER:
        *evctrl_reg &= ~TCC_EVCTRL_TRGEO;
        break;
      case PROCESSOR_TCC_EVENT_OUTPUT_OVERFLOW:
        *evctrl_reg &= ~TCC_EVCTRL_OVFEO;
        break;
      default:
        break;
    }
  }
}

static inline void PROCESSOR_TCC_EVENT_CountMode_Set(
    processor_tcc_instance_t          timer,
    processor_tcc_event_count_mode_t  mode
  )
{
  switch( timer )
  {
    case PROCESSOR_TCC_INSTANCE_TCC0:
      TCC0->EVCTRL.bit.CNTSEL = mode;
      break;
    case PROCESSOR_TCC_INSTANCE_TCC1:
      TCC1->EVCTRL.bit.CNTSEL = mode;
      break;
    case PROCESSOR_TCC_INSTANCE_TCC2:
      TCC2->EVCTRL.bit.CNTSEL = mode;
      break;
    default:
      break;
  }
}


#ifdef __cplusplus
}
#endif

#endif  // ECLAY_PROCESSOR_TCC_H
