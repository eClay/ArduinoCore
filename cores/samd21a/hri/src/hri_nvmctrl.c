#include "hri/nvmctrl.h"


void HRI_NVMCTRL_Initialize( void )
{
  // Disable Automatic NVM writes - see Silicon Errata 1.11.2
  NVMCTRL->CTRLB.bit.MANW = 1;
}
