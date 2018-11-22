#include "hri/tcc.h"

#include "hri/gclk.h"
#include "hri/pm.h"


void HRI_TCC_Initialize( hri_tcc_instance_t timer, hri_gclk_generator_t generator )
{
  HRI_TCC_RANGE_CHECK_TIMER(timer, HRI_TCC_NO_RETURN_VALUE);

  // Configure clocks
  switch( timer )
  {
    case HRI_TCC_INSTANCE_TCC0:
      HRI_PM_PeripheralClock_Enable( HRI_PM_PERIPHERAL_CLOCK_APBC_TCC0 );
      HRI_GCLK_PeripheralClock_Enable( generator, HRI_GCLK_PERIPHERAL_TCC0_TCC1, false );
      break;
    case HRI_TCC_INSTANCE_TCC1:
      HRI_PM_PeripheralClock_Enable( HRI_PM_PERIPHERAL_CLOCK_APBC_TCC1 );
      HRI_GCLK_PeripheralClock_Enable( generator, HRI_GCLK_PERIPHERAL_TCC0_TCC1, false );
      break;
    case HRI_TCC_INSTANCE_TCC2:
      HRI_PM_PeripheralClock_Enable( HRI_PM_PERIPHERAL_CLOCK_APBC_TCC2 );
      HRI_GCLK_PeripheralClock_Enable( generator, HRI_GCLK_PERIPHERAL_TCC2_TC3, false );
      break;
#ifdef TCC3
    case HRI_TCC_INSTANCE_TCC3:
      HRI_PM_PeripheralClock_Enable( HRI_PM_PERIPHERAL_CLOCK_APBC_TCC3 );
      HRI_GCLK_PeripheralClock_Enable( generator, HRI_GCLK_PERIPHERAL_TCC3, false );
      break;
#endif
    default:
      break;
  }

  HRI_TCC_SoftwareReset( timer );
}
