#ifndef ECLAY_HRI_NVMCTRL_H
#define ECLAY_HRI_NVMCTRL_H

#include <sam.h>

#include <stdbool.h>
#include <stdint.h>


#ifdef __cplusplus
extern "C" {
#endif


void HRI_NVMCTRL_Initialize( void );

static inline void HRI_NVMCTRL_ReadWaitStates_Set( uint8_t wait_states );


#define INCLUDE_HRI_NVMCTRL_INLINE_H
#include "src/hri_nvmctrl_inline.h"
#undef INCLUDE_HRI_NVMCTRL_INLINE_H


#ifdef __cplusplus
}
#endif

#endif  // ECLAY_HRI_NVMCTRL_H
