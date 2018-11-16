#ifndef INCLUDE_HRI_TCC_INLINE_H
#error hri_tcc_inline.h is not indended for direct use.
#endif


static Tcc* const hri_tcc_instance[TCC_INST_NUM] = TCC_INSTS;


#define HRI_TCC_NO_RETURN_VALUE

#define HRI_TCC_RANGE_CHECK_TIMER(timer, rtnval)  \
  if( timer >= HRI_TCC_NUM_INSTANCES )            \
  {                                              \
    return rtnval;                               \
  }

#define HRI_TCC_RANGE_CHECK_CHANNEL(channel, rtnval)  \
  if( channel >= HRI_TCC_NUM_CHANNELS )               \
  {                                                  \
    return rtnval;                                   \
  }

#define HRI_TCC_RANGE_CHECK_OUTPUT(output, rtnval)  \
  if( output >= HRI_TCC_NUM_OUTPUTS )               \
  {                                                \
    return rtnval;                                 \
  }


#define HRI_TCC_WAIT_FOR_SYNC(timer, sync_bit)  \
  while( hri_tcc_instance[timer]->SYNCBUSY.reg | sync_bit )


static inline void HRI_TCC_SoftwareReset( hri_tcc_instance_t timer )
{
  HRI_TCC_RANGE_CHECK_TIMER( timer, HRI_TCC_NO_RETURN_VALUE );

  hri_tcc_instance[timer]->CTRLA.bit.SWRST = 1;
  HRI_TCC_WAIT_FOR_SYNC( timer, TCC_SYNCBUSY_SWRST );
}

static inline void HRI_TCC_Enable( hri_tcc_instance_t timer )
{
  HRI_TCC_RANGE_CHECK_TIMER( timer, HRI_TCC_NO_RETURN_VALUE );

  hri_tcc_instance[timer]->CTRLA.bit.ENABLE |= 1;
  HRI_TCC_WAIT_FOR_SYNC( timer, TCC_SYNCBUSY_ENABLE );
}

static inline void HRI_TCC_Disable( hri_tcc_instance_t timer )
{
  HRI_TCC_RANGE_CHECK_TIMER( timer, HRI_TCC_NO_RETURN_VALUE );

  hri_tcc_instance[timer]->CTRLA.bit.ENABLE = 0;
  HRI_TCC_WAIT_FOR_SYNC( timer, TCC_SYNCBUSY_ENABLE );
}

static inline void HRI_TCC_Prescaler_Set( hri_tcc_instance_t timer, hri_tcc_prescale_t prescale )
{
  HRI_TCC_RANGE_CHECK_TIMER( timer, HRI_TCC_NO_RETURN_VALUE );
  
  hri_tcc_instance[timer]->CTRLA.bit.PRESCALER = prescale;
}

static inline void HRI_TCC_RunInStandby_Enable( hri_tcc_instance_t timer )
{
  HRI_TCC_RANGE_CHECK_TIMER( timer, HRI_TCC_NO_RETURN_VALUE );

  hri_tcc_instance[timer]->CTRLA.bit.RUNSTDBY = 1;
}

static inline void HRI_TCC_RunInStandby_Disable( hri_tcc_instance_t timer )
{
  HRI_TCC_RANGE_CHECK_TIMER( timer, HRI_TCC_NO_RETURN_VALUE );

  hri_tcc_instance[timer]->CTRLA.bit.RUNSTDBY = 0;
}

static inline void HRI_TCC_Capture_Enable( hri_tcc_instance_t timer, hri_tcc_channel_t channel )
{
  HRI_TCC_RANGE_CHECK_TIMER( timer, HRI_TCC_NO_RETURN_VALUE);
  HRI_TCC_RANGE_CHECK_CHANNEL( channel, HRI_TCC_NO_RETURN_VALUE);

  hri_tcc_instance[timer]->CTRLA.reg |= (TCC_CTRLA_CPTEN0 << channel);
}
static inline void HRI_TCC_Capture_Disable( hri_tcc_instance_t timer, hri_tcc_channel_t channel )
{
  HRI_TCC_RANGE_CHECK_TIMER( timer, HRI_TCC_NO_RETURN_VALUE);
  HRI_TCC_RANGE_CHECK_CHANNEL( channel, HRI_TCC_NO_RETURN_VALUE);

  hri_tcc_instance[timer]->CTRLA.reg &= ~(TCC_CTRLA_CPTEN0 << channel);
}

static inline void HRI_TCC_Direction_Set( hri_tcc_instance_t timer, hri_tcc_direction_t direction )
{
  HRI_TCC_RANGE_CHECK_TIMER( timer, HRI_TCC_NO_RETURN_VALUE );

  switch( direction )
  {
    case HRI_TCC_DIRECTION_UP:
      hri_tcc_instance[timer]->CTRLBCLR.reg = TCC_CTRLBCLR_DIR;
      break;
    case HRI_TCC_DIRECTION_DOWN:
      hri_tcc_instance[timer]->CTRLBSET.reg = TCC_CTRLBSET_DIR;
      break;
    default:
      break;
  }
  HRI_TCC_WAIT_FOR_SYNC( timer, TCC_SYNCBUSY_CTRLB );
}

static inline hri_tcc_direction_t HRI_TCC_Direction_Get( hri_tcc_instance_t timer )
{
  HRI_TCC_RANGE_CHECK_TIMER( timer, HRI_TCC_DIRECTION_UP );

  return (hri_tcc_direction_t)hri_tcc_instance[timer]->CTRLBSET.bit.DIR;
}

static inline void HRI_TCC_Oneshot_Enable( hri_tcc_instance_t timer )
{
  HRI_TCC_RANGE_CHECK_TIMER( timer, HRI_TCC_NO_RETURN_VALUE );

  hri_tcc_instance[timer]->CTRLBSET.reg = TCC_CTRLBSET_ONESHOT;
  HRI_TCC_WAIT_FOR_SYNC( timer, TCC_SYNCBUSY_CTRLB );
}

static inline void HRI_TCC_Oneshot_Disable( hri_tcc_instance_t timer )
{
  HRI_TCC_RANGE_CHECK_TIMER( timer, HRI_TCC_NO_RETURN_VALUE );

  hri_tcc_instance[timer]->CTRLBCLR.reg = TCC_CTRLBCLR_ONESHOT;
  HRI_TCC_WAIT_FOR_SYNC( timer, TCC_SYNCBUSY_CTRLB );
}

static inline void HRI_TCC_Command_Retrigger( hri_tcc_instance_t timer )
{
  HRI_TCC_RANGE_CHECK_TIMER( timer, HRI_TCC_NO_RETURN_VALUE );

  hri_tcc_instance[timer]->CTRLBSET.reg = TCC_CTRLBSET_CMD_RETRIGGER;
  HRI_TCC_WAIT_FOR_SYNC( timer, TCC_SYNCBUSY_CTRLB );
}

static inline void HRI_TCC_Command_Stop( hri_tcc_instance_t timer )
{
  HRI_TCC_RANGE_CHECK_TIMER( timer, HRI_TCC_NO_RETURN_VALUE );

  hri_tcc_instance[timer]->CTRLBSET.reg = TCC_CTRLBSET_CMD_STOP;
  HRI_TCC_WAIT_FOR_SYNC( timer, TCC_SYNCBUSY_CTRLB );
}

static inline void HRI_TCC_Command_Update( hri_tcc_instance_t timer )
{
  HRI_TCC_RANGE_CHECK_TIMER( timer, HRI_TCC_NO_RETURN_VALUE );

  hri_tcc_instance[timer]->CTRLBSET.reg = TCC_CTRLBSET_CMD_UPDATE;
  HRI_TCC_WAIT_FOR_SYNC( timer, TCC_SYNCBUSY_CTRLB );
}

static inline void HRI_TCC_Command_ReadSync( hri_tcc_instance_t timer )
{
  HRI_TCC_RANGE_CHECK_TIMER( timer, HRI_TCC_NO_RETURN_VALUE );

  hri_tcc_instance[timer]->CTRLBSET.reg = TCC_CTRLBSET_CMD_READSYNC;
  HRI_TCC_WAIT_FOR_SYNC( timer, TCC_SYNCBUSY_CTRLB );
}

static inline void HRI_TCC_OutputInvert_Enable( hri_tcc_instance_t timer, hri_tcc_output_t output )
{
  HRI_TCC_RANGE_CHECK_TIMER(timer, HRI_TCC_NO_RETURN_VALUE);
  HRI_TCC_RANGE_CHECK_OUTPUT(output, HRI_TCC_NO_RETURN_VALUE);

  hri_tcc_instance[timer]->DRVCTRL.reg |= (TCC_DRVCTRL_INVEN0 << output);
}

static inline void HRI_TCC_OutputInvert_Disable( hri_tcc_instance_t timer, hri_tcc_output_t output )
{
  HRI_TCC_RANGE_CHECK_TIMER(timer, HRI_TCC_NO_RETURN_VALUE);
  HRI_TCC_RANGE_CHECK_OUTPUT(output, HRI_TCC_NO_RETURN_VALUE);

  hri_tcc_instance[timer]->DRVCTRL.reg &= ~(TCC_DRVCTRL_INVEN0 << output);
}

static inline void HRI_TCC_EventInput_Enable( hri_tcc_instance_t timer, hri_tcc_event_input_t event )
{
  HRI_TCC_RANGE_CHECK_TIMER(timer, HRI_TCC_NO_RETURN_VALUE);

  switch( event )
  {
    case HRI_TCC_EVENT_INPUT_MC0:
      hri_tcc_instance[timer]->EVCTRL.bit.MCEI0 = 1;
      break;
    case HRI_TCC_EVENT_INPUT_MC1:
      hri_tcc_instance[timer]->EVCTRL.bit.MCEI1 = 1;
      break;
    case HRI_TCC_EVENT_INPUT_MC2:
      hri_tcc_instance[timer]->EVCTRL.bit.MCEI2 = 1;
      break;
    case HRI_TCC_EVENT_INPUT_MC3:
      hri_tcc_instance[timer]->EVCTRL.bit.MCEI3 = 1;
      break;
    case HRI_TCC_EVENT_INPUT_EV0:
      hri_tcc_instance[timer]->EVCTRL.bit.TCINV0 = 0;
      hri_tcc_instance[timer]->EVCTRL.bit.TCEI0 = 1;
      break;
    case HRI_TCC_EVENT_INPUT_EV0_INVERTED:
      hri_tcc_instance[timer]->EVCTRL.bit.TCINV0 = 1;
      hri_tcc_instance[timer]->EVCTRL.bit.TCEI0 = 1;
      break;
    case HRI_TCC_EVENT_INPUT_EV1:
      hri_tcc_instance[timer]->EVCTRL.bit.TCINV1 = 0;
      hri_tcc_instance[timer]->EVCTRL.bit.TCEI1 = 1;
      break;
    case HRI_TCC_EVENT_INPUT_EV1_INVERTED:
      hri_tcc_instance[timer]->EVCTRL.bit.TCINV1 = 1;
      hri_tcc_instance[timer]->EVCTRL.bit.TCEI1 = 1;
      break;
    default:
      break;
  }
}

static inline void HRI_TCC_EventInput_Disable( hri_tcc_instance_t timer, hri_tcc_event_input_t event )
{
  HRI_TCC_RANGE_CHECK_TIMER(timer, HRI_TCC_NO_RETURN_VALUE);

  switch( event )
  {
    case HRI_TCC_EVENT_INPUT_MC0:
      hri_tcc_instance[timer]->EVCTRL.bit.MCEI0 = 0;
      break;
    case HRI_TCC_EVENT_INPUT_MC1:
      hri_tcc_instance[timer]->EVCTRL.bit.MCEI1 = 0;
      break;
    case HRI_TCC_EVENT_INPUT_MC2:
      hri_tcc_instance[timer]->EVCTRL.bit.MCEI2 = 0;
      break;
    case HRI_TCC_EVENT_INPUT_MC3:
      hri_tcc_instance[timer]->EVCTRL.bit.MCEI3 = 0;
      break;
    case HRI_TCC_EVENT_INPUT_EV0:
      hri_tcc_instance[timer]->EVCTRL.bit.TCEI0 = 0;
      break;
    case HRI_TCC_EVENT_INPUT_EV0_INVERTED:
      hri_tcc_instance[timer]->EVCTRL.bit.TCEI0 = 0;
      break;
    case HRI_TCC_EVENT_INPUT_EV1:
      hri_tcc_instance[timer]->EVCTRL.bit.TCEI1 = 0;
      break;
    case HRI_TCC_EVENT_INPUT_EV1_INVERTED:
      hri_tcc_instance[timer]->EVCTRL.bit.TCEI1 = 0;
      break;
    default:
      break;
  }
}

static inline void HRI_TCC_EventInput0_Action_Set( hri_tcc_instance_t timer, hri_tcc_event_input_0_action_t action )
{
  HRI_TCC_RANGE_CHECK_TIMER(timer, HRI_TCC_NO_RETURN_VALUE);

  hri_tcc_instance[timer]->EVCTRL.bit.EVACT0 = action;
}

static inline void HRI_TCC_EventInput1_Action_Set( hri_tcc_instance_t timer, hri_tcc_event_input_1_action_t action )
{
  HRI_TCC_RANGE_CHECK_TIMER(timer, HRI_TCC_NO_RETURN_VALUE);

  hri_tcc_instance[timer]->EVCTRL.bit.EVACT1 = action;
}

static inline void HRI_TCC_EventOutput_Enable( hri_tcc_instance_t timer, hri_tcc_event_output_t event )
{
  HRI_TCC_RANGE_CHECK_TIMER(timer, HRI_TCC_NO_RETURN_VALUE);

  switch( event )
  {
    case HRI_TCC_EVENT_OUTPUT_MC0:
      hri_tcc_instance[timer]->EVCTRL.bit.MCEO0 = 1;
      break;
    case HRI_TCC_EVENT_OUTPUT_MC1:
      hri_tcc_instance[timer]->EVCTRL.bit.MCEO1 = 1;
      break;
    case HRI_TCC_EVENT_OUTPUT_MC2:
      hri_tcc_instance[timer]->EVCTRL.bit.MCEO2 = 1;
      break;
    case HRI_TCC_EVENT_OUTPUT_MC3:
      hri_tcc_instance[timer]->EVCTRL.bit.MCEO3 = 1;
      break;
    case HRI_TCC_EVENT_OUTPUT_COUNT:
      hri_tcc_instance[timer]->EVCTRL.bit.CNTEO = 1;
      break;
    case HRI_TCC_EVENT_OUTPUT_RETRIGGER:
      hri_tcc_instance[timer]->EVCTRL.bit.TRGEO = 1;
      break;
    case HRI_TCC_EVENT_OUTPUT_OVERFLOW:
      hri_tcc_instance[timer]->EVCTRL.bit.OVFEO = 1;
      break;
    default:
      break;
  }
}

static inline void HRI_TCC_EventOutput_Disable( hri_tcc_instance_t timer, hri_tcc_event_output_t event )
{
  HRI_TCC_RANGE_CHECK_TIMER(timer, HRI_TCC_NO_RETURN_VALUE);

  switch( event )
  {
    case HRI_TCC_EVENT_OUTPUT_MC0:
      hri_tcc_instance[timer]->EVCTRL.bit.MCEO0 = 1;
      break;
    case HRI_TCC_EVENT_OUTPUT_MC1:
      hri_tcc_instance[timer]->EVCTRL.bit.MCEO1 = 1;
      break;
    case HRI_TCC_EVENT_OUTPUT_MC2:
      hri_tcc_instance[timer]->EVCTRL.bit.MCEO2 = 1;
      break;
    case HRI_TCC_EVENT_OUTPUT_MC3:
      hri_tcc_instance[timer]->EVCTRL.bit.MCEO3 = 1;
      break;
    case HRI_TCC_EVENT_OUTPUT_COUNT:
      hri_tcc_instance[timer]->EVCTRL.bit.CNTEO = 1;
      break;
    case HRI_TCC_EVENT_OUTPUT_RETRIGGER:
      hri_tcc_instance[timer]->EVCTRL.bit.TRGEO = 1;
      break;
    case HRI_TCC_EVENT_OUTPUT_OVERFLOW:
      hri_tcc_instance[timer]->EVCTRL.bit.OVFEO = 1;
      break;
    default:
      break;
  }
}

static inline void HRI_TCC_EventCountMode_Set( hri_tcc_instance_t timer, hri_tcc_event_count_mode_t mode )
{
  HRI_TCC_RANGE_CHECK_TIMER(timer, HRI_TCC_NO_RETURN_VALUE);

  hri_tcc_instance[timer]->EVCTRL.bit.CNTSEL = mode;
}




static inline void HRI_TCC_Interrupt_Enable( hri_tcc_instance_t timer, hri_tcc_interrupt_t interrupt )
{
  HRI_TCC_RANGE_CHECK_TIMER(timer, HRI_TCC_NO_RETURN_VALUE);

  switch( interrupt )
  {
    case HRI_TCC_INTERRUPT_MC0:
      hri_tcc_instance[timer]->INTENSET.reg = TCC_INTENSET_MC0;
      break;
    case HRI_TCC_INTERRUPT_MC1:
      hri_tcc_instance[timer]->INTENSET.reg = TCC_INTENSET_MC1;
      break;
    case HRI_TCC_INTERRUPT_MC2:
      hri_tcc_instance[timer]->INTENSET.reg = TCC_INTENSET_MC2;
      break;
    case HRI_TCC_INTERRUPT_MC3:
      hri_tcc_instance[timer]->INTENSET.reg = TCC_INTENSET_MC3;
      break;
    case HRI_TCC_INTERRUPT_FAULT_0:
      hri_tcc_instance[timer]->INTENSET.reg = TCC_INTENSET_FAULT0;
      break;
    case HRI_TCC_INTERRUPT_FAULT_1:
      hri_tcc_instance[timer]->INTENSET.reg = TCC_INTENSET_FAULT1;
      break;
    case HRI_TCC_INTERRUPT_FAULT_A:
      hri_tcc_instance[timer]->INTENSET.reg = TCC_INTENSET_FAULTA;
      break;
    case HRI_TCC_INTERRUPT_FAULT_B:
      hri_tcc_instance[timer]->INTENSET.reg = TCC_INTENSET_FAULTB;
      break;
    case HRI_TCC_INTERRUPT_FAULT_DEBUG:
      hri_tcc_instance[timer]->INTENSET.reg = TCC_INTENSET_DFS;
      break;
    case HRI_TCC_INTERRUPT_ERROR:
      hri_tcc_instance[timer]->INTENSET.reg = TCC_INTENSET_ERR;
      break;
    case HRI_TCC_INTERRUPT_COUNTER:
      hri_tcc_instance[timer]->INTENSET.reg = TCC_INTENSET_CNT;
      break;
    case HRI_TCC_INTERRUPT_RETRIGGER:
      hri_tcc_instance[timer]->INTENSET.reg = TCC_INTENSET_TRG;
      break;
    case HRI_TCC_INTERRUPT_OVERFLOW:
      hri_tcc_instance[timer]->INTENSET.reg = TCC_INTENSET_OVF;
      break;
    default:
      break;
  }
}

static inline void HRI_TCC_Interrupt_Disable( hri_tcc_instance_t timer, hri_tcc_interrupt_t interrupt )
{
  HRI_TCC_RANGE_CHECK_TIMER(timer, HRI_TCC_NO_RETURN_VALUE);

  switch( interrupt )
  {
    case HRI_TCC_INTERRUPT_MC0:
      hri_tcc_instance[timer]->INTENCLR.reg = TCC_INTENCLR_MC0;
      break;
    case HRI_TCC_INTERRUPT_MC1:
      hri_tcc_instance[timer]->INTENCLR.reg = TCC_INTENCLR_MC1;
      break;
    case HRI_TCC_INTERRUPT_MC2:
      hri_tcc_instance[timer]->INTENCLR.reg = TCC_INTENCLR_MC2;
      break;
    case HRI_TCC_INTERRUPT_MC3:
      hri_tcc_instance[timer]->INTENCLR.reg = TCC_INTENCLR_MC3;
      break;
    case HRI_TCC_INTERRUPT_FAULT_0:
      hri_tcc_instance[timer]->INTENCLR.reg = TCC_INTENCLR_FAULT0;
      break;
    case HRI_TCC_INTERRUPT_FAULT_1:
      hri_tcc_instance[timer]->INTENCLR.reg = TCC_INTENCLR_FAULT1;
      break;
    case HRI_TCC_INTERRUPT_FAULT_A:
      hri_tcc_instance[timer]->INTENCLR.reg = TCC_INTENCLR_FAULTA;
      break;
    case HRI_TCC_INTERRUPT_FAULT_B:
      hri_tcc_instance[timer]->INTENCLR.reg = TCC_INTENCLR_FAULTB;
      break;
    case HRI_TCC_INTERRUPT_FAULT_DEBUG:
      hri_tcc_instance[timer]->INTENCLR.reg = TCC_INTENCLR_DFS;
      break;
    case HRI_TCC_INTERRUPT_ERROR:
      hri_tcc_instance[timer]->INTENCLR.reg = TCC_INTENCLR_ERR;
      break;
    case HRI_TCC_INTERRUPT_COUNTER:
      hri_tcc_instance[timer]->INTENCLR.reg = TCC_INTENCLR_CNT;
      break;
    case HRI_TCC_INTERRUPT_RETRIGGER:
      hri_tcc_instance[timer]->INTENCLR.reg = TCC_INTENCLR_TRG;
      break;
    case HRI_TCC_INTERRUPT_OVERFLOW:
      hri_tcc_instance[timer]->INTENCLR.reg = TCC_INTENCLR_OVF;
      break;
    default:
      break;
  }
}

static inline bool HRI_TCC_InterruptFlag_Get( hri_tcc_instance_t timer, hri_tcc_interrupt_t interrupt )
{
  HRI_TCC_RANGE_CHECK_TIMER(timer, false);

  switch( interrupt )
  {
    case HRI_TCC_INTERRUPT_MC0:
      return hri_tcc_instance[timer]->INTFLAG.bit.MC0;
    case HRI_TCC_INTERRUPT_MC1:
      return hri_tcc_instance[timer]->INTFLAG.bit.MC1;
    case HRI_TCC_INTERRUPT_MC2:
      return hri_tcc_instance[timer]->INTFLAG.bit.MC2;
    case HRI_TCC_INTERRUPT_MC3:
      return hri_tcc_instance[timer]->INTFLAG.bit.MC3;
    case HRI_TCC_INTERRUPT_FAULT_0:
      return hri_tcc_instance[timer]->INTFLAG.bit.FAULT0;
    case HRI_TCC_INTERRUPT_FAULT_1:
      return hri_tcc_instance[timer]->INTFLAG.bit.FAULT1;
    case HRI_TCC_INTERRUPT_FAULT_A:
      return hri_tcc_instance[timer]->INTFLAG.bit.FAULTA;
    case HRI_TCC_INTERRUPT_FAULT_B:
      return hri_tcc_instance[timer]->INTFLAG.bit.FAULTB;
    case HRI_TCC_INTERRUPT_FAULT_DEBUG:
      return hri_tcc_instance[timer]->INTFLAG.bit.DFS;
    case HRI_TCC_INTERRUPT_ERROR:
      return hri_tcc_instance[timer]->INTFLAG.bit.ERR;
    case HRI_TCC_INTERRUPT_COUNTER:
      return hri_tcc_instance[timer]->INTFLAG.bit.CNT;
    case HRI_TCC_INTERRUPT_RETRIGGER:
      return hri_tcc_instance[timer]->INTFLAG.bit.TRG;
    case HRI_TCC_INTERRUPT_OVERFLOW:
      return hri_tcc_instance[timer]->INTFLAG.bit.OVF;
    default:
      return false;
  }  
}

static inline void HRI_TCC_InterruptFlag_Clear( hri_tcc_instance_t timer, hri_tcc_interrupt_t interrupt )
{
  HRI_TCC_RANGE_CHECK_TIMER(timer, HRI_TCC_NO_RETURN_VALUE);

  switch( interrupt )
  {
    case HRI_TCC_INTERRUPT_MC0:
      hri_tcc_instance[timer]->INTFLAG.reg = TCC_INTFLAG_MC0;
      break;
    case HRI_TCC_INTERRUPT_MC1:
      hri_tcc_instance[timer]->INTFLAG.reg = TCC_INTFLAG_MC1;
      break;
    case HRI_TCC_INTERRUPT_MC2:
      hri_tcc_instance[timer]->INTFLAG.reg = TCC_INTFLAG_MC2;
      break;
    case HRI_TCC_INTERRUPT_MC3:
      hri_tcc_instance[timer]->INTFLAG.reg = TCC_INTFLAG_MC3;
      break;
    case HRI_TCC_INTERRUPT_FAULT_0:
      hri_tcc_instance[timer]->INTFLAG.reg = TCC_INTFLAG_FAULT0;
      break;
    case HRI_TCC_INTERRUPT_FAULT_1:
      hri_tcc_instance[timer]->INTFLAG.reg = TCC_INTFLAG_FAULT1;
      break;
    case HRI_TCC_INTERRUPT_FAULT_A:
      hri_tcc_instance[timer]->INTFLAG.reg = TCC_INTFLAG_FAULTA;
      break;
    case HRI_TCC_INTERRUPT_FAULT_B:
      hri_tcc_instance[timer]->INTFLAG.reg = TCC_INTFLAG_FAULTB;
      break;
    case HRI_TCC_INTERRUPT_FAULT_DEBUG:
      hri_tcc_instance[timer]->INTFLAG.reg = TCC_INTFLAG_DFS;
      break;
    case HRI_TCC_INTERRUPT_ERROR:
      hri_tcc_instance[timer]->INTFLAG.reg = TCC_INTFLAG_ERR;
      break;
    case HRI_TCC_INTERRUPT_COUNTER:
      hri_tcc_instance[timer]->INTFLAG.reg = TCC_INTFLAG_CNT;
      break;
    case HRI_TCC_INTERRUPT_RETRIGGER:
      hri_tcc_instance[timer]->INTFLAG.reg = TCC_INTFLAG_TRG;
      break;
    case HRI_TCC_INTERRUPT_OVERFLOW:
      hri_tcc_instance[timer]->INTFLAG.reg = TCC_INTFLAG_OVF;
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


#define HRI_TCC_INTERRUPT_HANDLER_FLAG(timer,interrupt,flag,callback)  \
  if( (flags | TCC_INTFLAG_##flag) && (enable | TCC_INTENSET_##flag) )  \
  { \
    hri_tcc_instance[timer]->INTFLAG.bit.flag = 1;  \
    callback( timer, interrupt ); \
    return; \
  }
