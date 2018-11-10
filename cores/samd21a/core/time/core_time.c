#include "core/time.h"

#include "core/reset.h"

#include "sam.h"


static volatile uint32_t _tickCount_mS = 0;


uint32_t CORE_TIME_Read_mS( void )
{
  return _tickCount_mS;
}

// Interrupt-compatible version of micros
// Theory: repeatedly take readings of SysTick counter, millis counter and SysTick interrupt pending flag.
// When it appears that millis counter and pending is stable and SysTick hasn't rolled over, use these
// values to calculate micros. If there is a pending SysTick, add one to the millis counter in the calculation.
uint32_t CORE_TIME_Read_uS( void )
{
  uint32_t ticks, ticks2;
  uint32_t pend, pend2;
  uint32_t count, count2;

   ticks2  = SysTick->VAL;
   pend2   = !!(SCB->ICSR & SCB_ICSR_PENDSTSET_Msk)  ;
   count2  = _tickCount_mS ;

  do
  {
    ticks=ticks2;
    pend=pend2;
    count=count2;
    ticks2  = SysTick->VAL;
    pend2   = !!(SCB->ICSR & SCB_ICSR_PENDSTSET_Msk)  ;
    count2  = _tickCount_mS ;
  } while ((pend != pend2) || (count != count2) || (ticks < ticks2));

//  return ((count+pend) * 1000) + (((SysTick->LOAD  - ticks)*(1048576/(VARIANT_MCK/1000000)))>>20) ;
  // this is an optimization to turn a runtime division into two compile-time divisions and
  // a runtime multiplication and shift, saving a few cycles
}

void CORE_TIME_Delay_mS( uint32_t mS )
{
  if ( mS == 0 )
  {
    return;
  }

  uint32_t start = _tickCount_mS;

  do
  {
//    yield() ;
  } while ( _tickCount_mS - start < mS ) ;
}

void CORE_TIME_Task(void)
{
  _tickCount_mS++;
  CORE_RESET_Task();
}
