#ifndef INCLUDE_HRI_GCLK_INLINE_H
#error hri_gclk_inline.h is not indended for direct use.
#endif


static inline void HRI_GCLK_Divisor_Set( 
    hri_gclk_generator_t generator,
    hri_gclk_divisor_t divisor
  )
{
  GCLK->GENDIV.reg = GCLK_GENDIV_ID(generator) | GCLK_GENDIV_DIV(divisor);

  while( GCLK->STATUS.reg & GCLK_STATUS_SYNCBUSY );
}

static inline void HRI_GCLK_Source_Enable( 
    hri_gclk_generator_t generator,
    hri_gclk_source_t source,
    bool improve_duty_cycle,
    bool output_off_value,
    bool output_enable,
    hri_gclk_divide_selection_t divide_selection,
    bool run_in_standby
  )
{
  GCLK->GENCTRL.reg =
    GCLK_GENCTRL_ID(generator) |
    GCLK_GENCTRL_SRC(source) |
    (improve_duty_cycle ? GCLK_GENCTRL_IDC : 0) |
    (output_off_value ? GCLK_GENCTRL_OOV: 0) |
    (output_enable ? GCLK_GENCTRL_OE : 0) |
    (divide_selection ? GCLK_GENCTRL_DIVSEL : 0) |
    (run_in_standby ? GCLK_GENCTRL_RUNSTDBY : 0) |
    GCLK_GENCTRL_GENEN;

  while( GCLK->STATUS.reg & GCLK_STATUS_SYNCBUSY );
}

static inline void HRI_GCLK_Source_Disable( 
    hri_gclk_generator_t generator
  )
{
  GCLK->GENCTRL.reg = GCLK_GENCTRL_ID(generator);

  while( GCLK->STATUS.reg & GCLK_STATUS_SYNCBUSY );
}

static inline void HRI_GCLK_PeripheralClock_Enable(
    hri_gclk_generator_t generator,
    hri_gclk_peripheral_t peripheral,
    bool write_lock
  )
{
  GCLK->CLKCTRL.reg =
    GCLK_CLKCTRL_GEN(generator) |
    GCLK_CLKCTRL_ID(peripheral) |
    (write_lock ? GCLK_CLKCTRL_WRTLOCK : 0) |
    GCLK_CLKCTRL_CLKEN;
  
  while( GCLK->STATUS.reg & GCLK_STATUS_SYNCBUSY );
}

static inline void HRI_GCLK_PeripheralClock_Disable(
    hri_gclk_peripheral_t peripheral
  )
{
  GCLK->CLKCTRL.reg = GCLK_CLKCTRL_ID(peripheral);
  
  while( GCLK->STATUS.reg & GCLK_STATUS_SYNCBUSY );
}
