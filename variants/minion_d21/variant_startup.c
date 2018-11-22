#include "eclay/time.h"
#include "variant.h"

#include "hri/adc.h"
#include "hri/gclk.h"
#include "hri/nvmctrl.h"
#include "hri/pm.h"
#include "hri/port.h"
#include "hri/sysctrl.h"

#include <sam.h>

#include <stdbool.h>
#include <stdint.h>


void VARIANT_Initialize( void )
{
  HRI_NVMCTRL_Initialize();

  // Set 1 Flash Wait State for 48MHz at 3.3V - see table 37-42 of datasheet
  HRI_NVMCTRL_ReadWaitStates_Set( 1 );

  HRI_PM_SystemClockPrescale_Set( HRI_PM_SYSTEM_CLOCK_CPU, HRI_PM_CPU_PRESCALE_DIV1 );
  HRI_PM_SystemClockPrescale_Set( HRI_PM_SYSTEM_CLOCK_APBA, HRI_PM_CPU_PRESCALE_DIV1 );
  HRI_PM_SystemClockPrescale_Set( HRI_PM_SYSTEM_CLOCK_APBB, HRI_PM_CPU_PRESCALE_DIV1 );
  HRI_PM_SystemClockPrescale_Set( HRI_PM_SYSTEM_CLOCK_APBC, HRI_PM_CPU_PRESCALE_DIV1 );

  HRI_GCLK_Initialize();

  // DFLL48M must be requested before being configured - see Silicon Errata 1.2.1
  HRI_SYSCTRL_DFLL48M_OnDemand_Disable();

  HRI_SYSCTRL_DFLL48M_CoarseCalibration_LoadFactory();
  HRI_SYSCTRL_DFLL48M_FineCalibration_Set(0x200);

  // Coarse Step not used with USB Clock Recovery
  HRI_SYSCTRL_DFLL48M_FineStep_Set( 0xA );  // Fine step must be set to 0xA per Table 37-64 of datasheet.
  HRI_SYSCTRL_DFLL48M_MultiplyFactor_Set( 48000 );  // USB SOF signal is 1kHz

  HRI_SYSCTRL_DFLL48M_ClosedLoop_Enable();
  HRI_SYSCTRL_DFLL48M_ChillCycle_Disable(); // Chill Cycle must be disabled per section 17.6.7.2.2 of datasheet.
  HRI_SYSCTRL_DFLL48M_QuickLock_Enable();   // Quick Lock must be enabled per section 17.6.7.2.2 of datasheet.
  HRI_SYSCTRL_DFLL48M_USBClockRecovery_Enable();

  HRI_SYSCTRL_DFLL48M_Enable();

  // Switch Generic Clock Generator 0 to DFLL48M.
  HRI_GCLK_Divisor_Set( HRI_GCLK_GENERATOR_0, 1 );
  HRI_GCLK_Source_Enable(
      HRI_GCLK_GENERATOR_0,
      HRI_GCLK_SOURCE_DFLL48M, 
      true,       // IDC - Improve Duty Cycle
      false,      // OOV - Output Off Value
      false,      // OE - Output Enable
      HRI_GCLK_DIVIDE_NORMAL,
      false       // RUNSTBY - Run in Standby
    );

  // Switch Generic Clock Generator 1 to DFLL48M / 48.
  HRI_GCLK_Divisor_Set( HRI_GCLK_GENERATOR_1, 48 );
  HRI_GCLK_Source_Enable(
      HRI_GCLK_GENERATOR_1,
      HRI_GCLK_SOURCE_DFLL48M, 
      true,       // IDC - Improve Duty Cycle
      false,      // OOV - Output Off Value
      true,      // OE - Output Enable
      HRI_GCLK_DIVIDE_NORMAL,
      false       // RUNSTBY - Run in Standby
    );

  HRI_PORT_PinMuxSet( HRI_PORT_GROUP_PB, 23, HRI_PORT_PINMUX_H );

  // Set up OSC8M for 8MHz on Clock Generator 3
  HRI_SYSCTRL_OSC8M_Prescale_Set( HRI_SYSCTRL_OSC8M_PRESCALE_DIV1 );
  HRI_SYSCTRL_OSC8M_OnDemand_Disable();

  HRI_GCLK_Divisor_Set( HRI_GCLK_GENERATOR_3, 1 );
  HRI_GCLK_Source_Enable(
      HRI_GCLK_GENERATOR_3,
      HRI_GCLK_SOURCE_OSC8M,
      false,      // IDC - Improve Duty Cycle
      false,      // OOV - Output Off Value
      false,      // OE - Output Enable
      HRI_GCLK_DIVIDE_NORMAL,
      false       // RUNSTBY - Run in Standby
    );

  // TODO: Better way to manage SystemCoreClock
  SystemCoreClock=VARIANT_MCK ;

  // TODO: This shouldn't be here - belongs in higher level ADC initialization
  // HRI_ADC_Initialize();
}

void SysTick_Handler(void)
{
//   if (sysTickHook())
//     return;
  // TODO: Set up callback mechanism to higher level
  CORE_TIME_Task();
}

