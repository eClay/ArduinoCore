#include "hri/gclk.h"

#include <sam.h>


void HRI_GCLK_Initialize( void )
{
  GCLK->CTRL.reg = GCLK_CTRL_SWRST ;

  while( GCLK->CTRL.bit.SWRST || GCLK->STATUS.bit.SYNCBUSY );
}
