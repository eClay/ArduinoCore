#ifndef ECLAY_HRI_SYSCTRL_H
#define ECLAY_HRI_SYSCTRL_H

#include <sam.h>

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


#ifdef __cplusplus
extern "C" {
#endif


//**************************************************************
// XOSC32K
//**************************************************************

typedef enum {
  HRI_SYSCTRL_XOSC32K_STARTUP_122uS = 0x0,
  HRI_SYSCTRL_XOSC32K_STARTUP_1068uS = 0x1,
  HRI_SYSCTRL_XOSC32K_STARTUP_62592uS = 0x2,
  HRI_SYSCTRL_XOSC32K_STARTUP_125092uS = 0x3,
  HRI_SYSCTRL_XOSC32K_STARTUP_500092uS = 0x4,
  HRI_SYSCTRL_XOSC32K_STARTUP_1000092uS = 0x5,
  HRI_SYSCTRL_XOSC32K_STARTUP_2000092uS = 0x6,
  HRI_SYSCTRL_XOSC32K_STARTUP_4000092uS = 0x7,
} hri_sysctrl_xosc32k_startup_time_t;

static inline void HRI_SYSCTRL_XOSC32K_Enable( void );
static inline void HRI_SYSCTRL_XOSC32K_Disable( void );
static inline void HRI_SYSCTRL_XOSC32K_Crystal_Enable( void );
static inline void HRI_SYSCTRL_XOSC32K_Crystal_Disable( void );
static inline void HRI_SYSCTRL_XOSC32K_32K_Output_Enable( void );
static inline void HRI_SYSCTRL_XOSC32K_32K_Output_Disable( void );
static inline void HRI_SYSCTRL_XOSC32K_AutoAmplitude_Enable( void );
static inline void HRI_SYSCTRL_XOSC32K_AutoAmplitude_Disable( void );
static inline void HRI_SYSCTRL_XOSC32K_RunInStandby_Enable( void );
static inline void HRI_SYSCTRL_XOSC32K_RunInStandby_Disable( void );
static inline void HRI_SYSCTRL_XOSC32K_OnDemand_Enable( void );
static inline void HRI_SYSCTRL_XOSC32K_OnDemand_Disable( void );
static inline void HRI_SYSCTRL_XOSC32K_StartupTime_Set( hri_sysctrl_xosc32k_startup_time_t startup );
static inline void HRI_SYSCTRL_XOSC32K_WriteLock_Enable( void );
static inline void HRI_SYSCTRL_XOSC32K_WriteLock_Disable( void );
static inline bool HRI_SYSCTRL_XOSC32K_isReady( void );


//**************************************************************
// OSC32K
//**************************************************************

typedef enum {
  HRI_SYSCTRL_OSC32K_STARTUP_92uS = 0x0,
  HRI_SYSCTRL_OSC32K_STARTUP_122uS = 0x1,
  HRI_SYSCTRL_OSC32K_STARTUP_183uS = 0x2,
  HRI_SYSCTRL_OSC32K_STARTUP_305uS = 0x3,
  HRI_SYSCTRL_OSC32K_STARTUP_549uS = 0x4,
  HRI_SYSCTRL_OSC32K_STARTUP_1038uS = 0x5,
  HRI_SYSCTRL_OSC32K_STARTUP_2014uS = 0x6,
  HRI_SYSCTRL_OSC32K_STARTUP_3967uS = 0x7,
} hri_sysctrl_osc32k_startup_time_t;

static inline void HRI_SYSCTRL_OSC32K_Enable( void );
static inline void HRI_SYSCTRL_OSC32K_Disable( void );
static inline void HRI_SYSCTRL_OSC32K_32K_Output_Enable( void );
static inline void HRI_SYSCTRL_OSC32K_32K_Output_Disable( void );
static inline void HRI_SYSCTRL_OSC32K_RunInStandby_Enable( void );
static inline void HRI_SYSCTRL_OSC32K_RunInStandby_Disable( void );
static inline void HRI_SYSCTRL_OSC32K_OnDemand_Enable( void );
static inline void HRI_SYSCTRL_OSC32K_OnDemand_Disable( void );
static inline void HRI_SYSCTRL_OSC32K_WriteLock_Enable( void );
static inline void HRI_SYSCTRL_OSC32K_WriteLock_Disable( void );
static inline void HRI_SYSCTRL_OSC32K_StartupTime_Set( hri_sysctrl_osc32k_startup_time_t startup );
static inline void HRI_SYSCTRL_OSC32K_Calibration_LoadFactory( void );
static inline bool HRI_SYSCTRL_OSC32K_isReady( void );


//**************************************************************
// OSC8M
//**************************************************************

typedef enum {
  HRI_SYSCTRL_OSC8M_PRESCALE_DIV1 = 0x0,
  HRI_SYSCTRL_OSC8M_PRESCALE_DIV2 = 0x1,
  HRI_SYSCTRL_OSC8M_PRESCALE_DIV4 = 0x2,
  HRI_SYSCTRL_OSC8M_PRESCALE_DIV8 = 0x3,
} hri_sysctrl_osc8m_prescale_t;

static inline void HRI_SYSCTRL_OSC8M_Enable( void );
static inline void HRI_SYSCTRL_OSC8M_Disable( void );
static inline void HRI_SYSCTRL_OSC8M_RunInStandby_Enable( void );
static inline void HRI_SYSCTRL_OSC8M_RunInStandby_Disable( void );
static inline void HRI_SYSCTRL_OSC8M_OnDemand_Enable( void );
static inline void HRI_SYSCTRL_OSC8M_OnDemand_Disable( void );
static inline void HRI_SYSCTRL_OSC8M_Prescale_Set( hri_sysctrl_osc8m_prescale_t prescale );
static inline bool HRI_SYSCTRL_OSC8M_isReady( void );


//**************************************************************
// DFLL48M
//**************************************************************

static inline void HRI_SYSCTRL_DFLL48M_Enable( void );
static inline void HRI_SYSCTRL_DFLL48M_Disable( void );
static inline void HRI_SYSCTRL_DFLL48M_ClosedLoop_Enable( void );
static inline void HRI_SYSCTRL_DFLL48M_ClosedLoop_Disable( void );
static inline void HRI_SYSCTRL_DFLL48M_Stable_Enable( void );
static inline void HRI_SYSCTRL_DFLL48M_Stable_Disable( void );
static inline void HRI_SYSCTRL_DFLL48M_LoseLock_Enable( void );
static inline void HRI_SYSCTRL_DFLL48M_LoseLock_Disable( void );
static inline void HRI_SYSCTRL_DFLL48M_USBClockRecovery_Enable( void );
static inline void HRI_SYSCTRL_DFLL48M_USBClockRecovery_Disable( void );
static inline void HRI_SYSCTRL_DFLL48M_RunInStandby_Enable( void );
static inline void HRI_SYSCTRL_DFLL48M_RunInStandby_Disable( void );
static inline void HRI_SYSCTRL_DFLL48M_OnDemand_Enable( void );
static inline void HRI_SYSCTRL_DFLL48M_OnDemand_Disable( void );
static inline void HRI_SYSCTRL_DFLL48M_ChillCycle_Enable( void );
static inline void HRI_SYSCTRL_DFLL48M_ChillCycle_Disable( void );
static inline void HRI_SYSCTRL_DFLL48M_QuickLock_Enable( void );
static inline void HRI_SYSCTRL_DFLL48M_QuickLock_Disable( void );
static inline void HRI_SYSCTRL_DFLL48M_BypassCoarseLock_Enable( void );
static inline void HRI_SYSCTRL_DFLL48M_BypassCoarseLock_Disable( void );
static inline void HRI_SYSCTRL_DFLL48M_WaitForLock_Enable( void );
static inline void HRI_SYSCTRL_DFLL48M_WaitForLock_Disable( void );
static inline void HRI_SYSCTRL_DFLL48M_FineCalibration_Set( uint16_t fine );
static inline uint16_t HRI_SYSCTRL_DFLL48M_FineCalibration_Get( void );
static inline void HRI_SYSCTRL_DFLL48M_CoarseCalibration_LoadFactory( void );
static inline void HRI_SYSCTRL_DFLL48M_CoarseCalibration_Set( uint8_t coarse );
static inline uint8_t HRI_SYSCTRL_DFLL48M_CoarseCalibration_Get( void );
static inline uint16_t HRI_SYSCTRL_DFLL48M_MultiplyDifference_Get( void );
static inline void HRI_SYSCTRL_DFLL48M_CoarseStep_Set( uint8_t coarse );
static inline void HRI_SYSCTRL_DFLL48M_FineStep_Set( uint16_t fine );
static inline void HRI_SYSCTRL_DFLL48M_MultiplyFactor_Set( uint16_t multiply );
static inline bool HRI_SYSCTRL_DFLL48M_isReady( void );



#define INCLUDE_HRI_SYSCTRL_INLINE_H
#include "src/hri_sysctrl_inline.h"
#undef INCLUDE_HRI_SYSCTRL_INLINE_H


#ifdef __cplusplus
}
#endif

#endif  // ECLAY_HRI_SYSCTRL_H
