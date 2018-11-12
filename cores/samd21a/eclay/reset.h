#ifndef ECLAY_CORE_RESET_H
#define ECLAY_CORE_RESET_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

void CORE_RESET_Initiate( uint32_t delay_ms );
void CORE_RESET_Cancel( void );

void CORE_RESET_Task( void );

#ifdef __cplusplus
}
#endif

#endif  // ECLAY_CORE_RESET_H
