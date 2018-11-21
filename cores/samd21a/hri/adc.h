#ifndef ECLAY_HRI_ADC_H
#define ECLAY_HRI_ADC_H

#include <sam.h>

#include <stdbool.h>
#include <stdint.h>


#ifdef __cplusplus
extern "C" {
#endif


void HRI_ADC_Initialize( void );


#define INCLUDE_HRI_ADC_INLINE_H
#include "src/hri_adc_inline.h"
#undef INCLUDE_HRI_ADC_INLINE_H


#ifdef __cplusplus
}
#endif

#endif  // ECLAY_HRI_ADC_H
