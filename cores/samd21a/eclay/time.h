#ifndef ECLAY_TIME_H
#define ECLAY_TIME_H

#include <stdint.h>

#ifdef __cplusplus
extern "C"{
#endif

void CORE_TIME_Delay_mS( uint32_t ms );
void CORE_TIME_Delay_uS( uint32_t us );

uint32_t CORE_TIME_Read_mS( void );
uint32_t CORE_TIME_Read_uS( void );

void CORE_TIME_Task( void );

#ifdef __cplusplus
} // extern "C"
#endif

#endif  // ECLAY_TIME_H
