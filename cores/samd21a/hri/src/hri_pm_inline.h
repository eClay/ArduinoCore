#ifndef INCLUDE_HRI_PM_INLINE_H
#error hri_pm_inline.h is not indended for direct use.
#endif

#include <sam.h>


static inline void HRI_PM_SystemClockPrescaler_Set( hri_pm_system_clock_t clock, hri_pm_cpu_prescale_t prescale )
{
  switch( clock )
  {
    case HRI_PM_SYSTEM_CLOCK_CPU:
      PM->CPUSEL.bit.CPUDIV = prescale;
      break;
    case HRI_PM_SYSTEM_CLOCK_APBA:
      PM->APBASEL.bit.APBADIV = prescale;
      break;
    case HRI_PM_SYSTEM_CLOCK_APBB:
      PM->APBBSEL.bit.APBBDIV = prescale;
      break;
    case HRI_PM_SYSTEM_CLOCK_APBC:
      PM->APBCSEL.bit.APBCDIV = prescale;
      break;
    case HRI_PM_SYSTEM_CLOCK_AHB:
    default:
      break;
  }
}

static inline HRI_PM_PeripheralClockEnable_Set( hri_pm_peripheral_clock_t clock, bool enable )
{
  switch( clock )
  {
    case HRI_PM_PERIPHERAL_CLOCK_AHB_HPB0:
      PM->AHBMASK.bit.HPB0_ = (enable ? 1 : 0);
      break;
    case HRI_PM_PERIPHERAL_CLOCK_AHB_HPB1:
      PM->AHBMASK.bit.HPB1_ = (enable ? 1 : 0);
      break;
    case HRI_PM_PERIPHERAL_CLOCK_AHB_HPB2:
      PM->AHBMASK.bit.HPB2_ = (enable ? 1 : 0);
      break;
    case HRI_PM_PERIPHERAL_CLOCK_AHB_DSU:
      PM->AHBMASK.bit.DSU_ = (enable ? 1 : 0);
      break;
    case HRI_PM_PERIPHERAL_CLOCK_AHB_NVMCTRL:
      PM->AHBMASK.bit.NVMCTRL_ = (enable ? 1 : 0);
      break;
    case HRI_PM_PERIPHERAL_CLOCK_AHB_DMAC:
      PM->AHBMASK.bit.DMAC_ = (enable ? 1 : 0);
      break;
    case HRI_PM_PERIPHERAL_CLOCK_AHB_USB:
      PM->AHBMASK.bit.USB_ = (enable ? 1 : 0);
      break;

    case HRI_PM_PERIPHERAL_CLOCK_APBA_PAC0:
      PM->APBAMASK.bit.PAC0_ = (enable ? 1 : 0);
      break;
    case HRI_PM_PERIPHERAL_CLOCK_APBA_PM:
      PM->APBAMASK.bit.PM_ = (enable ? 1 : 0);
      break;
    case HRI_PM_PERIPHERAL_CLOCK_APBA_SYSCTRL:
      PM->APBAMASK.bit.SYSCTRL_ = (enable ? 1 : 0);
      break;
    case HRI_PM_PERIPHERAL_CLOCK_APBA_GCLK:
      PM->APBAMASK.bit.GCLK_ = (enable ? 1 : 0);
      break;
    case HRI_PM_PERIPHERAL_CLOCK_APBA_WDT:
      PM->APBAMASK.bit.WDT_ = (enable ? 1 : 0);
      break;
    case HRI_PM_PERIPHERAL_CLOCK_APBA_RTC:
      PM->APBAMASK.bit.RTC_ = (enable ? 1 : 0);
      break;
    case HRI_PM_PERIPHERAL_CLOCK_APBA_EIC:
      PM->APBAMASK.bit.EIC_ = (enable ? 1 : 0);
      break;

    case HRI_PM_PERIPHERAL_CLOCK_APBB_PAC1:
      PM->APBBMASK.bit.PAC1_ = (enable ? 1 : 0);
      break;
    case HRI_PM_PERIPHERAL_CLOCK_APBB_DSU:
      PM->APBBMASK.bit.DSU_ = (enable ? 1 : 0);
      break;
    case HRI_PM_PERIPHERAL_CLOCK_APBB_NVMCTRL:
      PM->APBBMASK.bit.NVMCTRL_ = (enable ? 1 : 0);
      break;
    case HRI_PM_PERIPHERAL_CLOCK_APBB_PORT:
      PM->APBBMASK.bit.PORT_ = (enable ? 1 : 0);
      break;
    case HRI_PM_PERIPHERAL_CLOCK_APBB_DMAC:
      PM->APBBMASK.bit.DMAC_ = (enable ? 1 : 0);
      break;
    case HRI_PM_PERIPHERAL_CLOCK_APBB_USB:
      PM->APBBMASK.bit.USB_ = (enable ? 1 : 0);
      break;

    case HRI_PM_PERIPHERAL_CLOCK_APBC_PAC2:
      PM->APBCMASK.bit.PAC2_ = (enable ? 1 : 0);
      break;
    case HRI_PM_PERIPHERAL_CLOCK_APBC_EVSYS:
      PM->APBCMASK.bit.EVSYS_ = (enable ? 1 : 0);
      break;
    case HRI_PM_PERIPHERAL_CLOCK_APBC_SERCOM0:
      PM->APBCMASK.bit.SERCOM0_ = (enable ? 1 : 0);
      break;
    case HRI_PM_PERIPHERAL_CLOCK_APBC_SERCOM1:
      PM->APBCMASK.bit.SERCOM1_ = (enable ? 1 : 0);
      break;
    case HRI_PM_PERIPHERAL_CLOCK_APBC_SERCOM2:
      PM->APBCMASK.bit.SERCOM2_ = (enable ? 1 : 0);
      break;
    case HRI_PM_PERIPHERAL_CLOCK_APBC_SERCOM3:
      PM->APBCMASK.bit.SERCOM3_ = (enable ? 1 : 0);
      break;
    case HRI_PM_PERIPHERAL_CLOCK_APBC_SERCOM4:
      PM->APBCMASK.bit.SERCOM4_ = (enable ? 1 : 0);
      break;
    case HRI_PM_PERIPHERAL_CLOCK_APBC_SERCOM5:
      PM->APBCMASK.bit.SERCOM5_ = (enable ? 1 : 0);
      break;
    case HRI_PM_PERIPHERAL_CLOCK_APBC_TCC0:
      PM->APBCMASK.bit.TCC0_ = (enable ? 1 : 0);
      break;
    case HRI_PM_PERIPHERAL_CLOCK_APBC_TCC1:
      PM->APBCMASK.bit.TCC1_ = (enable ? 1 : 0);
      break;
    case HRI_PM_PERIPHERAL_CLOCK_APBC_TCC2:
      PM->APBCMASK.bit.TCC2_ = (enable ? 1 : 0);
      break;
    case HRI_PM_PERIPHERAL_CLOCK_APBC_TC3:
      PM->APBCMASK.bit.TC3_ = (enable ? 1 : 0);
      break;
    case HRI_PM_PERIPHERAL_CLOCK_APBC_TC4:
      PM->APBCMASK.bit.TC4_ = (enable ? 1 : 0);
      break;
    case HRI_PM_PERIPHERAL_CLOCK_APBC_TC5:
      PM->APBCMASK.bit.TC5_ = (enable ? 1 : 0);
      break;
#ifdef TC6
    case HRI_PM_PERIPHERAL_CLOCK_APBC_TC6:
      PM->APBCMASK.bit.TC6_ = (enable ? 1 : 0);
      break;
#endif
#ifdef TC7
    case HRI_PM_PERIPHERAL_CLOCK_APBC_TC7:
      PM->APBCMASK.bit.TC7_ = (enable ? 1 : 0);
      break;
#endif
    case HRI_PM_PERIPHERAL_CLOCK_APBC_ADC:
      PM->APBCMASK.bit.ADC_ = (enable ? 1 : 0);
      break;
    case HRI_PM_PERIPHERAL_CLOCK_APBC_AC:
      PM->APBCMASK.bit.AC_ = (enable ? 1 : 0);
      break;
    case HRI_PM_PERIPHERAL_CLOCK_APBC_DAC:
      PM->APBCMASK.bit.DAC_ = (enable ? 1 : 0);
      break;
    case HRI_PM_PERIPHERAL_CLOCK_APBC_PTC:
      PM->APBCMASK.bit.PTC_ = (enable ? 1 : 0);
      break;
    case HRI_PM_PERIPHERAL_CLOCK_APBC_I2S:
      PM->APBCMASK.bit.I2S_ = (enable ? 1 : 0);
      break;
#ifdef AC1
    case HRI_PM_PERIPHERAL_CLOCK_APBC_AC1:
      PM->APBCMASK.bit.AC1_ = (enable ? 1 : 0);
      break;
#endif
#ifdef TCC3
    case HRI_PM_PERIPHERAL_CLOCK_APBC_TCC3:
      PM->APBCMASK.bit.TCC3_ = (enable ? 1 : 0);
      break;
#endif

    default:
      break;
  }
}

static inline void HRI_PM_PeripheralClock_Enable( hri_pm_peripheral_clock_t clock )
{
  HRI_PM_PeripheralClockEnable_Set( clock, true );
}

static inline void HRI_PM_PeripheralClock_Disable( hri_pm_peripheral_clock_t clock )
{
  HRI_PM_PeripheralClockEnable_Set( clock, false );
}

static inline void HRI_PM_SleepMode_Set( hri_pm_sleep_mode_t mode )
{
  PM->SLEEP.bit.IDLE = mode;
}
