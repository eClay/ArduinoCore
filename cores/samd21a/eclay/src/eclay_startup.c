/*
  Copyright (c) 2015 Arduino LLC.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "eclay/time.h"
#include "variant.h"

#include "hri/adc.h"
#include "hri/gclk.h"
#include "hri/nvmctrl.h"
#include "hri/pm.h"
#include "hri/sysctrl.h"

#include <sam.h>


void SystemInit2( void )
{
  HRI_NVMCTRL_Initialize();

  // Set 1 Flash Wait State for 48MHz at 3.3V - see table 37-42 of datasheet
  HRI_NVMCTRL_ReadWaitStates_Set( 1 );

  HRI_PM_SystemClockPrescaler_Set( HRI_PM_SYSTEM_CLOCK_CPU, HRI_PM_CPU_PRESCALE_DIV1 );
  HRI_PM_SystemClockPrescaler_Set( HRI_PM_SYSTEM_CLOCK_APBA, HRI_PM_CPU_PRESCALE_DIV1 );
  HRI_PM_SystemClockPrescaler_Set( HRI_PM_SYSTEM_CLOCK_APBB, HRI_PM_CPU_PRESCALE_DIV1 );
  HRI_PM_SystemClockPrescaler_Set( HRI_PM_SYSTEM_CLOCK_APBC, HRI_PM_CPU_PRESCALE_DIV1 );

  HRI_GCLK_Initialize();

#if !defined(CRYSTALLESS)
  //Enable 32K Oscillator as reference clock for DFLL48M

  HRI_SYSCTRL_XOSC32K_StartupTime_Set( HRI_SYSCTRL_XOSC32K_STARTUP_2000092uS );
  HRI_SYSCTRL_XOSC32K_Crystal_Enable();
  HRI_SYSCTRL_XOSC32K_OnDemand_Disable();
  HRI_SYSCTRL_XOSC32K_32K_Output_Enable();
  HRI_SYSCTRL_XOSC32K_Enable();

  while( !HRI_SYSCTRL_XOSC32K_isReady() );

  // Configure Generator 1 with 32K oscillator as source.  GCLK1 will be used to feed the DFLL.
  HRI_GCLK_Divisor_Set( HRI_GCLK_GENERATOR_1, 1 );
  HRI_GCLK_Source_Enable(
      HRI_GCLK_GENERATOR_1,
      HRI_GCLK_SOURCE_XOSC32K, 
      false,      // IDC - Improve Duty Cycle
      false,      // OOV - Output Off Value
      false,      // OE - Output Enable
      HRI_GCLK_DIVIDE_NORMAL,
      false       // RUNSTBY - Run in Standby
    );

  // Set DFLL48M Generic Clock to use Generator 1
  HRI_GCLK_PeripheralClock_Enable(
    HRI_GCLK_GENERATOR_1,
    HRI_GCLK_PERIPHERAL_DFLL48M_REF,
    false       // WRTLOCK - Write Lock
  );

#endif

  // DFLL48M must be requested before being configured - see Silicon Errata 1.2.1
  HRI_SYSCTRL_DFLL48M_OnDemand_Disable();

  HRI_SYSCTRL_DFLL48M_CoarseCalibration_LoadFactory();
  HRI_SYSCTRL_DFLL48M_FineCalibration_Set(0x200);

#if defined(CRYSTALLESS)

  // Coarse Step not used with USB Clock Recovery
  HRI_SYSCTRL_DFLL48M_FineStep_Set( 0xA );  // Fine step must be set to 0xA per Table 37-64 of datasheet.
  HRI_SYSCTRL_DFLL48M_MultiplyFactor_Set( 48000 );  // USB SOF signal is 1kHz

  HRI_SYSCTRL_DFLL48M_ClosedLoop_Enable();
  HRI_SYSCTRL_DFLL48M_ChillCycle_Disable(); // Chill Cycle must be disabled per section 17.6.7.2.2 of datasheet.
  HRI_SYSCTRL_DFLL48M_QuickLock_Enable();   // Quick Lock must be enabled per section 17.6.7.2.2 of datasheet.
  HRI_SYSCTRL_DFLL48M_USBClockRecovery_Enable();

  HRI_SYSCTRL_DFLL48M_Enable();

#else   // has crystal

  HRI_SYSCTRL_DFLL48M_CoarseStep_Set( 0x1F );  // Coarse step is 0x1F, half of the max value
  HRI_SYSCTRL_DFLL48M_FineStep_Set( 0x1FF );  // Fine step is 0x1FF, half of the max value
  HRI_SYSCTRL_DFLL48M_MultiplyFactor_Set( (VARIANT_MCK + VARIANT_MAINOSC/2) / VARIANT_MAINOSC ) ; // External 32KHz is the reference

  HRI_SYSCTRL_DFLL48M_ClosedLoop_Enable();
  HRI_SYSCTRL_DFLL48M_WaitLock_Enable();
  HRI_SYSCTRL_DFLL48M_QuickLock_Disable();

  HRI_SYSCTRL_DFLL48M_Enable();

  // TODO: Implement HRI function(s) to check locks or wait for lock
  while ( (SYSCTRL->PCLKSR.reg & SYSCTRL_PCLKSR_DFLLLCKC) == 0 ||
          (SYSCTRL->PCLKSR.reg & SYSCTRL_PCLKSR_DFLLLCKF) == 0 )
  {
    /* Wait for locks flags */
  }

#endif

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

