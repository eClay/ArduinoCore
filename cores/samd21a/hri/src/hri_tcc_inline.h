#ifndef INCLUDE_HRI_TCC_INLINE_H
#error hri_tcc_inline.h is not indended for direct use.
#endif


static Tcc* const hri_tcc_instance[TCC_INST_NUM] = TCC_INSTS;


static inline void HRI_TCC_SoftwareReset(
    hri_tcc_instance_t  timer
  )
{
  switch( timer )
  {
    case HRI_TCC_INSTANCE_TCC0:
      TCC0->CTRLA.bit.SWRST = 1;
      while( TCC0->CTRLA.bit.SWRST );
      break;
    case HRI_TCC_INSTANCE_TCC1:
      TCC1->CTRLA.bit.SWRST = 1;
      while( TCC1->CTRLA.bit.SWRST );
      break;
    case HRI_TCC_INSTANCE_TCC2:
      TCC2->CTRLA.bit.SWRST = 1;
      while( TCC2->CTRLA.bit.SWRST );
      break;
    default:
      break;
  }
}


static inline void HRI_TCC_Enable(
    hri_tcc_instance_t  timer
  )
{
  switch( timer )
  {
    case HRI_TCC_INSTANCE_TCC0:
      TCC0->CTRLA.bit.ENABLE = 1;
      while( TCC0->SYNCBUSY.bit.ENABLE );
      break;
    case HRI_TCC_INSTANCE_TCC1:
      TCC1->CTRLA.bit.ENABLE = 1;
      while( TCC1->SYNCBUSY.bit.ENABLE );
      break;
    case HRI_TCC_INSTANCE_TCC2:
      TCC2->CTRLA.bit.ENABLE = 1;
      while( TCC2->SYNCBUSY.bit.ENABLE );
      break;
    default:
      break;
  }
}

static inline void HRI_TCC_Disable(
    hri_tcc_instance_t  timer
  )
{
  switch( timer )
  {
    case HRI_TCC_INSTANCE_TCC0:
      TCC0->CTRLA.bit.ENABLE = 0;
      while( TCC0->SYNCBUSY.bit.ENABLE );
      break;
    case HRI_TCC_INSTANCE_TCC1:
      TCC1->CTRLA.bit.ENABLE = 0;
      while( TCC1->SYNCBUSY.bit.ENABLE );
      break;
    case HRI_TCC_INSTANCE_TCC2:
      TCC2->CTRLA.bit.ENABLE = 0;
      while( TCC2->SYNCBUSY.bit.ENABLE );
      break;
    default:
      break;
  }
}


static inline void HRI_TCC_Waveform_Set(
    hri_tcc_instance_t  timer,
    hri_tcc_waveform_t  waveform
  )
{
  switch( timer )
  {
    case HRI_TCC_INSTANCE_TCC0:
      TCC0->WAVE.bit.WAVEGEN = waveform;
      break;
    case HRI_TCC_INSTANCE_TCC1:
      TCC1->WAVE.bit.WAVEGEN = waveform;
      break;
    case HRI_TCC_INSTANCE_TCC2:
      TCC2->WAVE.bit.WAVEGEN = waveform;
      break;
    default:
      break;
  }
}


static inline void HRI_TCC_Period_Set(
    hri_tcc_instance_t  timer,
    uint32_t                  period
  )
{
  switch( timer )
  {
    case HRI_TCC_INSTANCE_TCC0:
      TCC0->PER.reg = period;
      while( TCC0->SYNCBUSY.bit.PER );
      break;
    case HRI_TCC_INSTANCE_TCC1:
      TCC1->PER.reg = period;
      while( TCC1->SYNCBUSY.bit.PER );
      break;
    case HRI_TCC_INSTANCE_TCC2:
      TCC2->PER.reg = period;
      while( TCC2->SYNCBUSY.bit.PER );
      break;
    default:
      break;
  }
}

static inline void HRI_TCC_Count_Set(
    hri_tcc_instance_t  timer,
    uint32_t                  count
  )
{
  switch( timer )
  {
    case HRI_TCC_INSTANCE_TCC0:
      TCC0->COUNT.reg = count;
      while( TCC0->SYNCBUSY.bit.COUNT );
      break;
    case HRI_TCC_INSTANCE_TCC1:
      TCC1->COUNT.reg = count;
      while( TCC1->SYNCBUSY.bit.COUNT );
      break;
    case HRI_TCC_INSTANCE_TCC2:
      TCC2->COUNT.reg = count;
      while( TCC2->SYNCBUSY.bit.COUNT );
      break;
    default:
      break;
  }
}

static inline uint32_t HRI_TCC_Count_Get(
    hri_tcc_instance_t  timer
  )
{
  switch( timer )
  {
    case HRI_TCC_INSTANCE_TCC0:
      TCC0->CTRLBSET.reg = TCC_CTRLBSET_CMD_READSYNC;
      while( TCC0->SYNCBUSY.reg & (TCC_SYNCBUSY_CTRLB | TCC_SYNCBUSY_COUNT) );
      return TCC0->COUNT.reg;
    case HRI_TCC_INSTANCE_TCC1:
      TCC1->CTRLBSET.reg = TCC_CTRLBSET_CMD_READSYNC;
      while( TCC1->SYNCBUSY.reg & (TCC_SYNCBUSY_CTRLB | TCC_SYNCBUSY_COUNT) );
      return TCC1->COUNT.reg;
    case HRI_TCC_INSTANCE_TCC2:
      TCC2->CTRLBSET.reg = TCC_CTRLBSET_CMD_READSYNC;
      while( TCC2->SYNCBUSY.reg & (TCC_SYNCBUSY_CTRLB | TCC_SYNCBUSY_COUNT) );
      return TCC2->COUNT.reg;
    default:
      return 0;
  }
}

static inline void HRI_TCC_Compare_Set(
    hri_tcc_instance_t  timer,
    hri_tcc_channel_t   channel,
    uint32_t                    compare
  )
{
  switch( timer )
  {
    case HRI_TCC_INSTANCE_TCC0:
      if( channel <= HRI_TCC_CHANNEL_MC3 )
      {
        TCC0->CC[channel].reg = compare;
        while( TCC0->SYNCBUSY.reg | (TCC_SYNCBUSY_CC0 << channel) );
      }
      break;
    case HRI_TCC_INSTANCE_TCC1:
      if( channel <= HRI_TCC_CHANNEL_MC1 )
      {
        TCC1->CC[channel].reg = compare;
        while( TCC1->SYNCBUSY.reg | (TCC_SYNCBUSY_CC0 << channel) );
      }
      break;
    case HRI_TCC_INSTANCE_TCC2:
      if( channel <= HRI_TCC_CHANNEL_MC1 )
      {
        TCC2->CC[channel].reg = compare;
        while( TCC2->SYNCBUSY.reg | (TCC_SYNCBUSY_CC0 << channel) );
      }
      break;
    default:
      break;
  }
}

static inline uint32_t HRI_TCC_Capture_Get(
    hri_tcc_instance_t  timer,
    hri_tcc_channel_t   channel
  )
{
  switch( timer )
  {
    case HRI_TCC_INSTANCE_TCC0:
      if( channel <= HRI_TCC_CHANNEL_MC3 )
      {
        return TCC0->CC[channel].reg;
      }
      else
      {
        return 0;
      }
    case HRI_TCC_INSTANCE_TCC1:
      if( channel <= HRI_TCC_CHANNEL_MC1 )
      {
        return TCC1->CC[channel].reg;
      }
      else
      {
        return 0;
      }
    case HRI_TCC_INSTANCE_TCC2:
      if( channel <= HRI_TCC_CHANNEL_MC1 )
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


static inline void HRI_TCC_Pattern_Set(
    hri_tcc_instance_t  timer,
    uint8_t                     enable,
    uint8_t                     value
  )
{
  switch( timer )
  {
    case HRI_TCC_INSTANCE_TCC0:
      TCC0->PATT.reg = TCC_PATT_PGE(enable) | TCC_PATT_PGV(value);
      while( TCC0->SYNCBUSY.bit.PATT );
      break;
    case HRI_TCC_INSTANCE_TCC1:
      TCC1->PATT.reg = TCC_PATT_PGE(enable) | TCC_PATT_PGV(value);
      while( TCC1->SYNCBUSY.bit.PATT );
      break;
    case HRI_TCC_INSTANCE_TCC2:
      break;
    default:
      break;
  }
}

static inline void HRI_TCC_PatternEnable_Set(
    hri_tcc_instance_t  timer,
    uint8_t                   enable
  )
{
  switch( timer )
  {
    case HRI_TCC_INSTANCE_TCC0:
      *((__IO uint8_t*)TCC0->PATT.reg) = enable;
      while( TCC0->SYNCBUSY.bit.PATT );
      break;
    case HRI_TCC_INSTANCE_TCC1:
      *((__IO uint8_t*)TCC1->PATT.reg) = enable;
      while( TCC1->SYNCBUSY.bit.PATT );
      break;
    case HRI_TCC_INSTANCE_TCC2:
      break;
    default:
      break;
  }
}

static inline void HRI_TCC_PatternValue_Set(
    hri_tcc_instance_t  timer,
    uint8_t                   value
  )
{
  switch( timer )
  {
    case HRI_TCC_INSTANCE_TCC0:
      *((__IO uint8_t*)TCC0->PATT.reg + 1) = value;
      while( TCC0->SYNCBUSY.bit.PATT );
      break;
    case HRI_TCC_INSTANCE_TCC1:
      *((__IO uint8_t*)TCC1->PATT.reg + 1) = value;
      while( TCC1->SYNCBUSY.bit.PATT );
      break;
    case HRI_TCC_INSTANCE_TCC2:
      break;
    default:
      break;
  }
}

static inline __IO uint16_t* HRI_TCC_PatternRegister(
    hri_tcc_instance_t  timer
  )
{
  switch( timer )
  {
    case HRI_TCC_INSTANCE_TCC0:
      return (__IO uint16_t*)TCC0->PATT.reg;
    case HRI_TCC_INSTANCE_TCC1:
      return (__IO uint16_t*)TCC1->PATT.reg;
    case HRI_TCC_INSTANCE_TCC2:
      return NULL;
    default:
      return NULL;
  }
}

static inline __IO uint8_t* HRI_TCC_PatternRegisterEnable(
    hri_tcc_instance_t  timer
  )
{
  switch( timer )
  {
    case HRI_TCC_INSTANCE_TCC0:
      return (__IO uint8_t*)TCC0->PATT.reg;
    case HRI_TCC_INSTANCE_TCC1:
      return (__IO uint8_t*)TCC1->PATT.reg;
    case HRI_TCC_INSTANCE_TCC2:
      return NULL;
    default:
      return NULL;
  }
}

static inline __IO uint8_t* HRI_TCC_PatternRegisterValue(
    hri_tcc_instance_t  timer
  )
{
  switch( timer )
  {
    case HRI_TCC_INSTANCE_TCC0:
      return (__IO uint8_t*)TCC0->PATT.reg + 1;
    case HRI_TCC_INSTANCE_TCC1:
      return (__IO uint8_t*)TCC1->PATT.reg + 1;
    case HRI_TCC_INSTANCE_TCC2:
      return NULL;
    default:
      return NULL;
  }
}

static inline void HRI_TCC_CMD_Retrigger(
    hri_tcc_instance_t  timer
  )
{
  switch( timer )
  {
    case HRI_TCC_INSTANCE_TCC0:
      TCC0->CTRLBSET.reg = TCC_CTRLBSET_CMD_RETRIGGER;
      while( TCC0->SYNCBUSY.bit.CTRLB );
      break;
    case HRI_TCC_INSTANCE_TCC1:
      TCC1->CTRLBSET.reg = TCC_CTRLBSET_CMD_RETRIGGER;
      while( TCC1->SYNCBUSY.bit.CTRLB );
      break;
    case HRI_TCC_INSTANCE_TCC2:
      TCC2->CTRLBSET.reg = TCC_CTRLBSET_CMD_RETRIGGER;
      while( TCC2->SYNCBUSY.bit.CTRLB );
      break;
    default:
      break;
  }
}

static inline void HRI_TCC_CMD_Stop(
    hri_tcc_instance_t  timer
  )
{
  switch( timer )
  {
    case HRI_TCC_INSTANCE_TCC0:
      TCC0->CTRLBSET.reg = TCC_CTRLBSET_CMD_STOP;
      while( TCC0->SYNCBUSY.bit.CTRLB );
      break;
    case HRI_TCC_INSTANCE_TCC1:
      TCC1->CTRLBSET.reg = TCC_CTRLBSET_CMD_STOP;
      while( TCC1->SYNCBUSY.bit.CTRLB );
      break;
    case HRI_TCC_INSTANCE_TCC2:
      TCC2->CTRLBSET.reg = TCC_CTRLBSET_CMD_STOP;
      while( TCC2->SYNCBUSY.bit.CTRLB );
      break;
    default:
      break;
  }
}

static inline void HRI_TCC_CMD_Update(
    hri_tcc_instance_t  timer
  )
{
  switch( timer )
  {
    case HRI_TCC_INSTANCE_TCC0:
      TCC0->CTRLBSET.reg = TCC_CTRLBSET_CMD_UPDATE;
      while( TCC0->SYNCBUSY.bit.CTRLB );
      break;
    case HRI_TCC_INSTANCE_TCC1:
      TCC1->CTRLBSET.reg = TCC_CTRLBSET_CMD_UPDATE;
      while( TCC1->SYNCBUSY.bit.CTRLB );
      break;
    case HRI_TCC_INSTANCE_TCC2:
      TCC2->CTRLBSET.reg = TCC_CTRLBSET_CMD_UPDATE;
      while( TCC2->SYNCBUSY.bit.CTRLB );
      break;
    default:
      break;
  }
}

static inline void HRI_TCC_CMD_ReadSync(
    hri_tcc_instance_t  timer
  )
{
  switch( timer )
  {
    case HRI_TCC_INSTANCE_TCC0:
      TCC0->CTRLBSET.reg = TCC_CTRLBSET_CMD_READSYNC;
      while( TCC0->SYNCBUSY.bit.CTRLB );
      break;
    case HRI_TCC_INSTANCE_TCC1:
      TCC1->CTRLBSET.reg = TCC_CTRLBSET_CMD_READSYNC;
      while( TCC1->SYNCBUSY.bit.CTRLB );
      break;
    case HRI_TCC_INSTANCE_TCC2:
      TCC2->CTRLBSET.reg = TCC_CTRLBSET_CMD_READSYNC;
      while( TCC2->SYNCBUSY.bit.CTRLB );
      break;
    default:
      break;
  }
}


static inline __IO uint32_t* HRI_TCC_EVCTRL_Register(
    hri_tcc_instance_t  timer
  )
{
  switch( timer )
  {
    case HRI_TCC_INSTANCE_TCC0:
      return (__IO uint32_t*)TCC0->EVCTRL.reg;
    case HRI_TCC_INSTANCE_TCC1:
      return (__IO uint32_t*)TCC1->EVCTRL.reg;
    case HRI_TCC_INSTANCE_TCC2:
      return (__IO uint32_t*)TCC2->EVCTRL.reg;
    default:
      return NULL;
  }
}


static inline void HRI_TCC_EVENT_Input_Enable(
    hri_tcc_instance_t      timer,
    hri_tcc_event_input_t   event
  )
{
  __IO uint32_t* evctrl_reg = HRI_TCC_EVCTRL_Register(timer);

  if( evctrl_reg != NULL )
  {
    switch( event )
    {
      case HRI_TCC_EVENT_INPUT_MC0:
        *evctrl_reg |= TCC_EVCTRL_MCEI0;
        break;
      case HRI_TCC_EVENT_INPUT_MC1:
        *evctrl_reg |= TCC_EVCTRL_MCEI1;
        break;
      case HRI_TCC_EVENT_INPUT_MC2:
        *evctrl_reg |= TCC_EVCTRL_MCEI2;
        break;
      case HRI_TCC_EVENT_INPUT_MC3:
        *evctrl_reg |= TCC_EVCTRL_MCEI3;
        break;
      case HRI_TCC_EVENT_INPUT_EV0:
        *evctrl_reg &= ~TCC_EVCTRL_TCINV0;
        *evctrl_reg |= TCC_EVCTRL_TCEI0;
        break;
      case HRI_TCC_EVENT_INPUT_EV0_INVERTED:
        *evctrl_reg |= (TCC_EVCTRL_TCEI0 | TCC_EVCTRL_TCINV0);
        break;
      case HRI_TCC_EVENT_INPUT_EV1:
        *evctrl_reg &= ~TCC_EVCTRL_TCINV1;
        *evctrl_reg |= TCC_EVCTRL_TCEI1;
        break;
      case HRI_TCC_EVENT_INPUT_EV1_INVERTED:
        *evctrl_reg |= (TCC_EVCTRL_TCEI1 | TCC_EVCTRL_TCINV1);
        break;
      default:
        break;
    }
  }
}

static inline void HRI_TCC_EVENT_Input_Disable(
    hri_tcc_instance_t      timer,
    hri_tcc_event_input_t   event
  )
{
  __IO uint32_t* evctrl_reg = HRI_TCC_EVCTRL_Register(timer);

  if( evctrl_reg != NULL )
  {
    switch( event )
    {
      case HRI_TCC_EVENT_INPUT_MC0:
        *evctrl_reg &= ~TCC_EVCTRL_MCEI0;
        break;
      case HRI_TCC_EVENT_INPUT_MC1:
        *evctrl_reg &= ~TCC_EVCTRL_MCEI1;
        break;
      case HRI_TCC_EVENT_INPUT_MC2:
        *evctrl_reg &= ~TCC_EVCTRL_MCEI2;
        break;
      case HRI_TCC_EVENT_INPUT_MC3:
        *evctrl_reg &= ~TCC_EVCTRL_MCEI3;
        break;
      case HRI_TCC_EVENT_INPUT_EV0:
        *evctrl_reg &= ~TCC_EVCTRL_TCEI0;
        break;
      case HRI_TCC_EVENT_INPUT_EV0_INVERTED:
        *evctrl_reg &= ~TCC_EVCTRL_TCEI0;
        break;
      case HRI_TCC_EVENT_INPUT_EV1:
        *evctrl_reg &= ~TCC_EVCTRL_TCEI1;
        break;
      case HRI_TCC_EVENT_INPUT_EV1_INVERTED:
        *evctrl_reg &= ~TCC_EVCTRL_TCEI1;
        break;
      default:
        break;
    }
  }
}

static inline void HRI_TCC_EVENT_InputAction0_Set(
    hri_tcc_instance_t            timer,
    hri_tcc_event_input0_action_t action
  )
{
  switch( timer )
  {
    case HRI_TCC_INSTANCE_TCC0:
      TCC0->EVCTRL.bit.EVACT0 = action;
      break;
    case HRI_TCC_INSTANCE_TCC1:
      TCC1->EVCTRL.bit.EVACT0 = action;
      break;
    case HRI_TCC_INSTANCE_TCC2:
      TCC2->EVCTRL.bit.EVACT0 = action;
      break;
    default:
      break;
  }
}

static inline void HRI_TCC_EVENT_InputAction1_Set(
    hri_tcc_instance_t            timer,
    hri_tcc_event_input1_action_t action
  )
{
  switch( timer )
  {
    case HRI_TCC_INSTANCE_TCC0:
      TCC0->EVCTRL.bit.EVACT1 = action;
      break;
    case HRI_TCC_INSTANCE_TCC1:
      TCC1->EVCTRL.bit.EVACT1 = action;
      break;
    case HRI_TCC_INSTANCE_TCC2:
      TCC2->EVCTRL.bit.EVACT1 = action;
      break;
    default:
      break;
  }
}


static inline void HRI_TCC_EVENT_Output_Enable(
    hri_tcc_instance_t      timer,
    hri_tcc_event_output_t  event
  )
{
  __IO uint32_t* evctrl_reg = HRI_TCC_EVCTRL_Register(timer);

  if( evctrl_reg != NULL )
  {
    switch( event )
    {
      case HRI_TCC_EVENT_OUTPUT_MC0:
        *evctrl_reg |= TCC_EVCTRL_MCEO0;
        break;
      case HRI_TCC_EVENT_OUTPUT_MC1:
        *evctrl_reg |= TCC_EVCTRL_MCEO1;
        break;
      case HRI_TCC_EVENT_OUTPUT_MC2:
        *evctrl_reg |= TCC_EVCTRL_MCEO2;
        break;
      case HRI_TCC_EVENT_OUTPUT_MC3:
        *evctrl_reg |= TCC_EVCTRL_MCEO3;
        break;
      case HRI_TCC_EVENT_OUTPUT_COUNT:
        *evctrl_reg |= TCC_EVCTRL_CNTEO;
        break;
      case HRI_TCC_EVENT_OUTPUT_RETRIGGER:
        *evctrl_reg |= TCC_EVCTRL_TRGEO;
        break;
      case HRI_TCC_EVENT_OUTPUT_OVERFLOW:
        *evctrl_reg |= TCC_EVCTRL_OVFEO;
        break;
      default:
        break;
    }
  }
}

static inline void HRI_TCC_EVENT_Output_Disable(
    hri_tcc_instance_t      timer,
    hri_tcc_event_output_t  event
  )
{
  __IO uint32_t* evctrl_reg = HRI_TCC_EVCTRL_Register(timer);

  if( evctrl_reg != NULL )
  {
    switch( event )
    {
      case HRI_TCC_EVENT_OUTPUT_MC0:
        *evctrl_reg &= ~TCC_EVCTRL_MCEO0;
        break;
      case HRI_TCC_EVENT_OUTPUT_MC1:
        *evctrl_reg &= ~TCC_EVCTRL_MCEO1;
        break;
      case HRI_TCC_EVENT_OUTPUT_MC2:
        *evctrl_reg &= ~TCC_EVCTRL_MCEO2;
        break;
      case HRI_TCC_EVENT_OUTPUT_MC3:
        *evctrl_reg &= ~TCC_EVCTRL_MCEO3;
        break;
      case HRI_TCC_EVENT_OUTPUT_COUNT:
        *evctrl_reg &= ~TCC_EVCTRL_CNTEO;
        break;
      case HRI_TCC_EVENT_OUTPUT_RETRIGGER:
        *evctrl_reg &= ~TCC_EVCTRL_TRGEO;
        break;
      case HRI_TCC_EVENT_OUTPUT_OVERFLOW:
        *evctrl_reg &= ~TCC_EVCTRL_OVFEO;
        break;
      default:
        break;
    }
  }
}

static inline void HRI_TCC_EVENT_CountMode_Set(
    hri_tcc_instance_t          timer,
    hri_tcc_event_count_mode_t  mode
  )
{
  switch( timer )
  {
    case HRI_TCC_INSTANCE_TCC0:
      TCC0->EVCTRL.bit.CNTSEL = mode;
      break;
    case HRI_TCC_INSTANCE_TCC1:
      TCC1->EVCTRL.bit.CNTSEL = mode;
      break;
    case HRI_TCC_INSTANCE_TCC2:
      TCC2->EVCTRL.bit.CNTSEL = mode;
      break;
    default:
      break;
  }
}
