#ifndef INCLUDE_HRI_SYSCTRL_INLINE_H
#error hri_sysctrl_inline.h is not indended for direct use.
#endif


#include <stdbool.h>




//**************************************************************
// XOSC32K
//**************************************************************

static inline void HRI_SYSCTRL_XOSC32K_Enable( void )
{
  SYSCTRL->XOSC32K.bit.ENABLE = 1;
}
static inline void HRI_SYSCTRL_XOSC32K_Disable( void )
{
  SYSCTRL->XOSC32K.bit.ENABLE = 0;
}

static inline void HRI_SYSCTRL_XOSC32K_Crystal_Enable( void )
{
  SYSCTRL->XOSC32K.bit.XTALEN = 1;
}
static inline void HRI_SYSCTRL_XOSC32K_Crystal_Disable( void )
{
  SYSCTRL->XOSC32K.bit.XTALEN = 0;
}

static inline void HRI_SYSCTRL_XOSC32K_32K_Output_Enable( void )
{
  SYSCTRL->XOSC32K.bit.EN32K = 1;
}
static inline void HRI_SYSCTRL_XOSC32K_32K_Output_Disable( void )
{
  SYSCTRL->XOSC32K.bit.EN32K = 0;
}

static inline void HRI_SYSCTRL_XOSC32K_AutoAmplitude_Enable( void )
{
  SYSCTRL->XOSC32K.bit.AAMPEN = 1;
}
static inline void HRI_SYSCTRL_XOSC32K_AutoAmplitude_Disable( void )
{
  SYSCTRL->XOSC32K.bit.AAMPEN = 0;
}

static inline void HRI_SYSCTRL_XOSC32K_RunInStandby_Enable( void )
{
  SYSCTRL->XOSC32K.bit.RUNSTDBY = 1;
}
static inline void HRI_SYSCTRL_XOSC32K_RunInStandby_Disable( void )
{
  SYSCTRL->XOSC32K.bit.RUNSTDBY = 0;
}

static inline void HRI_SYSCTRL_XOSC32K_OnDemand_Enable( void )
{
  SYSCTRL->XOSC32K.bit.ONDEMAND = 1;
}
static inline void HRI_SYSCTRL_XOSC32K_OnDemand_Disable( void )
{
  SYSCTRL->XOSC32K.bit.ONDEMAND = 0;
}

static inline void HRI_SYSCTRL_XOSC32K_WriteLock_Enable( void )
{
  SYSCTRL->XOSC32K.bit.WRTLOCK = 1;
}
static inline void HRI_SYSCTRL_XOSC32K_WriteLock_Disable( void )
{
  SYSCTRL->XOSC32K.bit.WRTLOCK = 0;
}

static inline void HRI_SYSCTRL_XOSC32K_StartupTime_Set( hri_sysctrl_xosc32k_startup_time_t startup )
{
  SYSCTRL->XOSC32K.bit.STARTUP = startup;  
}

static inline bool HRI_SYSCTRL_XOSC32K_isReady( void )
{
  return SYSCTRL->PCLKSR.bit.XOSC32KRDY == 1;
}


//**************************************************************
// OSC32K
//**************************************************************

static inline void HRI_SYSCTRL_OSC32K_Enable( void )
{
  SYSCTRL->OSC32K.bit.ENABLE = 1;
}
static inline void HRI_SYSCTRL_OSC32K_Disable( void )
{
  SYSCTRL->OSC32K.bit.ENABLE = 0;
}

static inline void HRI_SYSCTRL_OSC32K_32K_Output_Enable( void )
{
  SYSCTRL->OSC32K.bit.EN32K = 1;
}
static inline void HRI_SYSCTRL_OSC32K_32K_Output_Disable( void )
{
  SYSCTRL->OSC32K.bit.EN32K = 0;
}

static inline void HRI_SYSCTRL_OSC32K_RunInStandby_Enable( void )
{
  SYSCTRL->OSC32K.bit.RUNSTDBY = 1;
}
static inline void HRI_SYSCTRL_OSC32K_RunInStandby_Disable( void )
{
  SYSCTRL->OSC32K.bit.RUNSTDBY = 0;
}

static inline void HRI_SYSCTRL_OSC32K_OnDemand_Enable( void )
{
  SYSCTRL->OSC32K.bit.ONDEMAND = 1;
}
static inline void HRI_SYSCTRL_OSC32K_OnDemand_Disable( void )
{
  SYSCTRL->OSC32K.bit.ONDEMAND = 0;
}

static inline void HRI_SYSCTRL_OSC32K_WriteLock_Enable( void )
{
  SYSCTRL->OSC32K.bit.WRTLOCK = 1;
}
static inline void HRI_SYSCTRL_OSC32K_WriteLock_Disable( void )
{
  SYSCTRL->OSC32K.bit.WRTLOCK = 0;
}

static inline void HRI_SYSCTRL_OSC32K_StartupTime_Set( hri_sysctrl_osc32k_startup_time_t startup )
{
  SYSCTRL->OSC32K.bit.STARTUP = startup;  
}

static inline void HRI_SYSCTRL_OSC32K_Calibration_LoadDefault( void )
{
  uint32_t calib = (*((uint32_t *) FUSES_OSC32K_CAL_ADDR) & FUSES_OSC32K_CAL_Msk) >> FUSES_OSC32K_CAL_Pos;

  SYSCTRL->OSC32K.bit.CALIB = calib;
}

static inline bool HRI_SYSCTRL_OSC32K_isReady( void )
{
  return SYSCTRL->PCLKSR.bit.OSC32KRDY == 1;
}


//**************************************************************
// OSC8M
//**************************************************************

static inline void HRI_SYSCTRL_OSC8M_Enable( void )
{
  SYSCTRL->OSC8M.bit.ENABLE = 1;
}
static inline void HRI_SYSCTRL_OSC8M_Disable( void )
{
  SYSCTRL->OSC8M.bit.ENABLE = 0;
}

static inline void HRI_SYSCTRL_OSC8M_RunInStandby_Enable( void )
{
  SYSCTRL->OSC8M.bit.RUNSTDBY = 1;
}
static inline void HRI_SYSCTRL_OSC8M_RunInStandby_Disable( void )
{
  SYSCTRL->OSC8M.bit.RUNSTDBY = 0;
}

static inline void HRI_SYSCTRL_OSC8M_OnDemand_Enable( void )
{
  SYSCTRL->OSC8M.bit.ONDEMAND = 1;
}
static inline void HRI_SYSCTRL_OSC8M_OnDemand_Disable( void )
{
  SYSCTRL->OSC8M.bit.ONDEMAND = 0;
}

static inline void HRI_SYSCTRL_OSC8M_Prescale_Set( hri_sysctrl_osc8m_prescale_t prescale )
{
  SYSCTRL->OSC8M.bit.PRESC = prescale;
}

static inline bool HRI_SYSCTRL_OSC8M_isReady( void )
{
  return SYSCTRL->PCLKSR.bit.OSC8MRDY == 1;
}


//**************************************************************
// DFLL48M
//**************************************************************

static inline void HRI_SYSCTRL_DFLL48M_Enable( void )
{
  SYSCTRL->DFLLCTRL.bit.ENABLE = 1;
  while( SYSCTRL->PCLKSR.reg & SYSCTRL_PCLKSR_DFLLRDY == 0 );
}
static inline void HRI_SYSCTRL_DFLL48M_Disable( void )
{
  SYSCTRL->DFLLCTRL.bit.ENABLE = 0;
  while( SYSCTRL->PCLKSR.reg & SYSCTRL_PCLKSR_DFLLRDY == 0 );
}

static inline void HRI_SYSCTRL_DFLL48M_ClosedLoop_Enable( void )
{
  SYSCTRL->DFLLCTRL.bit.MODE = 1;
  while( SYSCTRL->PCLKSR.reg & SYSCTRL_PCLKSR_DFLLRDY == 0 );
}
static inline void HRI_SYSCTRL_DFLL48M_ClosedLoop_Disable( void )
{
  SYSCTRL->DFLLCTRL.bit.MODE = 0;
  while( SYSCTRL->PCLKSR.reg & SYSCTRL_PCLKSR_DFLLRDY == 0 );
}

static inline void HRI_SYSCTRL_DFLL48M_Stable_Enable( void )
{
  SYSCTRL->DFLLCTRL.bit.STABLE = 1;
  while( SYSCTRL->PCLKSR.reg & SYSCTRL_PCLKSR_DFLLRDY == 0 );
}
static inline void HRI_SYSCTRL_DFLL48M_Stable_Disable( void )
{
  SYSCTRL->DFLLCTRL.bit.STABLE = 0;
  while( SYSCTRL->PCLKSR.reg & SYSCTRL_PCLKSR_DFLLRDY == 0 );
}

static inline void HRI_SYSCTRL_DFLL48M_LoseLock_Enable( void )
{
  SYSCTRL->DFLLCTRL.bit.LLAW = 1;
  while( SYSCTRL->PCLKSR.reg & SYSCTRL_PCLKSR_DFLLRDY == 0 );
}
static inline void HRI_SYSCTRL_DFLL48M_LoseLock_Disable( void )
{
  SYSCTRL->DFLLCTRL.bit.LLAW = 0;
  while( SYSCTRL->PCLKSR.reg & SYSCTRL_PCLKSR_DFLLRDY == 0 );
}

static inline void HRI_SYSCTRL_DFLL48M_USBClockRecovery_Enable( void )
{
  SYSCTRL->DFLLCTRL.bit.USBCRM = 1;
  while( SYSCTRL->PCLKSR.reg & SYSCTRL_PCLKSR_DFLLRDY == 0 );
}
static inline void HRI_SYSCTRL_DFLL48M_USBClockRecovery_Disable( void )
{
  SYSCTRL->DFLLCTRL.bit.USBCRM = 0;
  while( SYSCTRL->PCLKSR.reg & SYSCTRL_PCLKSR_DFLLRDY == 0 );
}

static inline void HRI_SYSCTRL_DFLL48M_RunInStandby_Enable( void )
{
  SYSCTRL->DFLLCTRL.bit.RUNSTDBY = 1;
  while( SYSCTRL->PCLKSR.reg & SYSCTRL_PCLKSR_DFLLRDY == 0 );
}
static inline void HRI_SYSCTRL_DFLL48M_RunInStandby_Disable( void )
{
  SYSCTRL->DFLLCTRL.bit.RUNSTDBY = 0;
  while( SYSCTRL->PCLKSR.reg & SYSCTRL_PCLKSR_DFLLRDY == 0 );
}

static inline void HRI_SYSCTRL_DFLL48M_OnDemand_Enable( void )
{
  SYSCTRL->DFLLCTRL.bit.ONDEMAND = 1;
  while( SYSCTRL->PCLKSR.reg & SYSCTRL_PCLKSR_DFLLRDY == 0 );
}
static inline void HRI_SYSCTRL_DFLL48M_OnDemand_Disable( void )
{
  SYSCTRL->DFLLCTRL.bit.ONDEMAND = 0;
  while( SYSCTRL->PCLKSR.reg & SYSCTRL_PCLKSR_DFLLRDY == 0 );
}

static inline void HRI_SYSCTRL_DFLL48M_ChillCycle_Enable( void )
{
  SYSCTRL->DFLLCTRL.bit.CCDIS = 0;
  while( SYSCTRL->PCLKSR.reg & SYSCTRL_PCLKSR_DFLLRDY == 0 );
}
static inline void HRI_SYSCTRL_DFLL48M_ChillCycle_Disable( void )
{
  SYSCTRL->DFLLCTRL.bit.CCDIS = 1;
  while( SYSCTRL->PCLKSR.reg & SYSCTRL_PCLKSR_DFLLRDY == 0 );
}

static inline void HRI_SYSCTRL_DFLL48M_QuickLock_Enable( void )
{
  SYSCTRL->DFLLCTRL.bit.QLDIS = 0;
  while( SYSCTRL->PCLKSR.reg & SYSCTRL_PCLKSR_DFLLRDY == 0 );
}
static inline void HRI_SYSCTRL_DFLL48M_QuickLock_Disable( void )
{
  SYSCTRL->DFLLCTRL.bit.QLDIS = 1;
  while( SYSCTRL->PCLKSR.reg & SYSCTRL_PCLKSR_DFLLRDY == 0 );
}

static inline void HRI_SYSCTRL_DFLL48M_BypassCoarseLock_Enable( void )
{
  SYSCTRL->DFLLCTRL.bit.BPLCKC = 1;
  while( SYSCTRL->PCLKSR.reg & SYSCTRL_PCLKSR_DFLLRDY == 0 );
}
static inline void HRI_SYSCTRL_DFLL48M_BypassCoarseLock_Disable( void )
{
  SYSCTRL->DFLLCTRL.bit.BPLCKC = 0;
  while( SYSCTRL->PCLKSR.reg & SYSCTRL_PCLKSR_DFLLRDY == 0 );
}

static inline void HRI_SYSCTRL_DFLL48M_WaitForLock_Enable( void )
{
  SYSCTRL->DFLLCTRL.bit.WAITLOCK = 1;
  while( SYSCTRL->PCLKSR.reg & SYSCTRL_PCLKSR_DFLLRDY == 0 );
}
static inline void HRI_SYSCTRL_DFLL48M_WaitForLock_Disable( void )
{
  SYSCTRL->DFLLCTRL.bit.WAITLOCK = 0;
  while( SYSCTRL->PCLKSR.reg & SYSCTRL_PCLKSR_DFLLRDY == 0 );
}

static inline void HRI_SYSCTRL_DFLL48M_FineCalibration_Set( uint16_t fine )
{
  SYSCTRL->DFLLVAL.bit.FINE = fine;
}
static inline uint16_t HRI_SYSCTRL_DFLL48M_FineCalibration_Get( void )
{
  SYSCTRL->DFLLSYNC.bit.READREQ = 1;
  while( SYSCTRL->PCLKSR.bit.DFLLRDY == 0 );
  return (uint16_t)SYSCTRL->DFLLVAL.bit.FINE;
}

static inline void HRI_SYSCTRL_DFLL48M_CoarseCalibration_LoadFactory( void )
{
  uint32_t coarse = (*((uint32_t *) FUSES_DFLL48M_COARSE_CAL_ADDR) & FUSES_DFLL48M_COARSE_CAL_Msk) >> FUSES_DFLL48M_COARSE_CAL_Pos;
  SYSCTRL->DFLLVAL.bit.COARSE = coarse;
}
static inline void HRI_SYSCTRL_DFLL48M_CoarseCalibration_Set( uint8_t coarse )
{
  SYSCTRL->DFLLVAL.bit.COARSE = coarse;
}
static inline uint8_t HRI_SYSCTRL_DFLL48M_CoarseCalibration_Get( void )
{
  SYSCTRL->DFLLSYNC.bit.READREQ = 1;
  while( SYSCTRL->PCLKSR.bit.DFLLRDY == 0 );
  return (uint8_t)SYSCTRL->DFLLVAL.bit.COARSE;
}

static inline uint16_t HRI_SYSCTRL_DFLL48M_MultiplyDifference_Get( void )
{
  SYSCTRL->DFLLSYNC.bit.READREQ = 1;
  while( SYSCTRL->PCLKSR.bit.DFLLRDY == 0 );
  return (uint16_t)SYSCTRL->DFLLVAL.bit.DIFF;
}

static inline void HRI_SYSCTRL_DFLL48M_MultiplyFactor_Set( uint16_t multiply )
{
  SYSCTRL->DFLLMUL.bit.MUL = multiply;
}
static inline void HRI_SYSCTRL_DFLL48M_FineStep_Set( uint16_t fine )
{
  SYSCTRL->DFLLMUL.bit.FSTEP = fine;
}
static inline void HRI_SYSCTRL_DFLL48M_CoarseStep_Set( uint8_t coarse )
{
  SYSCTRL->DFLLMUL.bit.CSTEP = coarse;
}

static inline bool HRI_SYSCTRL_DFLL48M_isReady( void )
{
  return SYSCTRL->PCLKSR.bit.DFLLRDY == 1;
}
