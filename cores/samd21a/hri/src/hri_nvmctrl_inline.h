#ifndef INCLUDE_HRI_NVMCTRL_INLINE_H
#error hri_nvmctrl_inline.h is not indended for direct use.
#endif

#include <sam.h>


static inline void HRI_NVMCTRL_ReadWaitStates_Set( uint8_t wait_states )
{
  NVMCTRL->CTRLB.bit.RWS = wait_states;
}
