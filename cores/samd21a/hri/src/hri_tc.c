#include "hri/tc.h"

#include "hri/gclk.h"
#include "hri/pm.h"


void HRI_TC_Initialize( hri_tc_instance_t timer, hri_gclk_generator_t generator )
{
  HRI_TC_RANGE_CHECK_TIMER(timer, HRI_TC_NO_RETURN_VALUE);

  // Configure clocks
  switch( timer )
  {
    case HRI_TC_INSTANCE_TC3:
      HRI_PM_PeripheralClock_Enable( HRI_PM_PERIPHERAL_CLOCK_APBC_TC3 );
      HRI_GCLK_PeripheralClock_Enable( generator, HRI_GCLK_PERIPHERAL_TCC2_TC3, false );
      break;
    case HRI_TC_INSTANCE_TC4:
      HRI_PM_PeripheralClock_Enable( HRI_PM_PERIPHERAL_CLOCK_APBC_TC4 );
      HRI_GCLK_PeripheralClock_Enable( generator, HRI_GCLK_PERIPHERAL_TC4_TC5, false );
      break;
    case HRI_TC_INSTANCE_TC5:
      HRI_PM_PeripheralClock_Enable( HRI_PM_PERIPHERAL_CLOCK_APBC_TC5 );
      HRI_GCLK_PeripheralClock_Enable( generator, HRI_GCLK_PERIPHERAL_TC4_TC5, false );
      break;
#ifdef TC6
    case HRI_TCC_INSTANCE_TC6:
      HRI_PM_PeripheralClock_Enable( HRI_PM_PERIPHERAL_CLOCK_APBC_TC6 );
      HRI_GCLK_PeripheralClock_Enable( generator, HRI_GCLK_PERIPHERAL_TC6_TC7, false );
      break;
#endif
#ifdef TC7
    case HRI_TCC_INSTANCE_TC7:
      HRI_PM_PeripheralClock_Enable( HRI_PM_PERIPHERAL_CLOCK_APBC_TC7 );
      HRI_GCLK_PeripheralClock_Enable( generator, HRI_GCLK_PERIPHERAL_TC6_TC7, false );
      break;
#endif
    default:
      break;
  }

  HRI_TC_SoftwareReset( timer );
}
