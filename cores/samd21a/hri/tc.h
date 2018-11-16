#ifndef ECLAY_HRI_TC_H
#define ECLAY_HRI_TC_H

#include "hri/sam.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


#ifdef __cplusplus
extern "C" {
#endif


typedef enum {
  HRI_TC_INSTANCE_TC3 = 0,
  HRI_TC_INSTANCE_TC4,
  HRI_TC_INSTANCE_TC5,
#if (TC_INST_NUM == 5)
  HRI_TC_INSTANCE_TC6,
  HRI_TC_INSTANCE_TC7,
#endif
  HRI_TC_NUM_INSTANCES,
  HRI_TC_NOT_A_INSTANCE = HRI_TC_NUM_INSTANCES
} hri_tc_instance_t;

typedef enum {
  HRI_TC_CHANNEL_MC0 = 0,
  HRI_TC_CHANNEL_MC1,
  HRI_TC_NUM_CHANNELS,
  HRI_TC_NOT_A_CHANNEL = HRI_TC_NUM_CHANNELS
} hri_tc_channel_t;

typedef enum {
  HRI_TC_OUTPUT_WO0 = 0,
  HRI_TC_OUTPUT_WO1,
  HRI_TC_NUM_OUTPUTS,
  HRI_TC_NOT_A_OUTPUT = HRI_TC_NUM_OUTPUTS
} hri_tc_output_t;

typedef enum {
  HRI_TC_MODE_8BIT  = 0x1,
  HRI_TC_MODE_16BIT = 0x0,
  HRI_TC_MODE_32BIT = 0x2,
} hri_tc_mode_t;

typedef enum {
  HRI_TC_PRESCALE_DIV1    = 0x0,
  HRI_TC_PRESCALE_DIV2    = 0x1,
  HRI_TC_PRESCALE_DIV4    = 0x2,
  HRI_TC_PRESCALE_DIV8    = 0x3,
  HRI_TC_PRESCALE_DIV16   = 0x4,
  HRI_TC_PRESCALE_DIV64   = 0x5,
  HRI_TC_PRESCALE_DIV256  = 0x6,
  HRI_TC_PRESCALE_DIV1024 = 0x7,
} hri_tc_prescale_t;

typedef enum {
  HRI_TC_WAVEFORM_NORMAL_FREQUENCY = 0x0,
  HRI_TC_WAVEFORM_MATCH_FREQUENCY  = 0x1,
  HRI_TC_WAVEFORM_NORMAL_PWM       = 0x2,
  HRI_TC_WAVEFORM_MATCH_PWM        = 0x3,
} hri_tc_waveform_t;

typedef enum {
  HRI_TC_DIRECTION_UP   = 0x0,
  HRI_TC_DIRECTION_DOWN = 0x1,
} hri_tc_direction_t;

typedef enum {
  HRI_TC_INTERRUPT_MC0,
  HRI_TC_INTERRUPT_MC1,
  HRI_TC_INTERRUPT_SYNC_READY,
  HRI_TC_INTERRUPT_ERROR,
  HRI_TC_INTERRUPT_OVERFLOW,
} hri_tc_interrupt_t;

typedef enum {
  HRI_TC_EVENT_INPUT,
  HRI_TC_EVENT_INPUT_INVERTED,
} hri_tc_event_input_t;

typedef enum {
  HRI_TC_EVENT_INPUT_ACTION_OFF            = 0x0,
  HRI_TC_EVENT_INPUT_ACTION_RETRIGGER      = 0x1,
  HRI_TC_EVENT_INPUT_ACTION_COUNT          = 0x2,
  HRI_TC_EVENT_INPUT_ACTION_START          = 0x3,
  HRI_TC_EVENT_INPUT_ACTION_PPW            = 0x5,
  HRI_TC_EVENT_INPUT_ACTION_PWP            = 0x6,
} hri_tc_event_input_action_t;

typedef enum {
  HRI_TC_EVENT_OUTPUT_MC0,
  HRI_TC_EVENT_OUTPUT_MC1,
  HRI_TC_EVENT_OUTPUT_OVERFLOW,
} hri_tc_event_output_t;


typedef void (*hri_tc_interrupt_callback_t)( hri_tc_instance_t timer, hri_tc_interrupt_t interrupt );


void HRI_TC_Initialize( void );

static inline void HRI_TC_SoftwareReset( hri_tc_instance_t timer );

static inline void HRI_TC_Enable( hri_tc_instance_t timer );
static inline void HRI_TC_Disable( hri_tc_instance_t timer );

static inline void HRI_TC_Mode_Set( hri_tc_instance_t timer, hri_tc_mode_t mode );

static inline void HRI_TC_Waveform_Set( hri_tc_instance_t timer, hri_tc_waveform_t waveform );

static inline void HRI_TC_Prescaler_Set( hri_tc_instance_t timer, hri_tc_prescale_t prescale );

static inline void HRI_TC_RunInStandby_Enable( hri_tc_instance_t timer );
static inline void HRI_TC_RunInStandby_Disable( hri_tc_instance_t timer );

static inline void HRI_TC_Direction_Set( hri_tc_instance_t timer, hri_tc_direction_t direction );
static inline hri_tc_direction_t HRI_TC_Direction_Get( hri_tc_instance_t timer );

static inline void HRI_TC_Oneshot_Enable( hri_tc_instance_t timer );
static inline void HRI_TC_Oneshot_Disable( hri_tc_instance_t timer );

static inline void HRI_TC_Command_Retrigger( hri_tc_instance_t timer );
static inline void HRI_TC_Command_Stop( hri_tc_instance_t timer );

static inline void HRI_TC_OutputInvert_Enable( hri_tc_instance_t timer, hri_tc_output_t output );
static inline void HRI_TC_OutputInvert_Disable( hri_tc_instance_t timer, hri_tc_output_t output );

static inline void HRI_TC_Capture_Enable( hri_tc_instance_t timer, hri_tc_channel_t channel );
static inline void HRI_TC_Capture_Disable( hri_tc_instance_t timer, hri_tc_channel_t channel );

static inline void HRI_TC_EventInput_Enable( hri_tc_instance_t timer, hri_tc_event_input_t event );
static inline void HRI_TC_EventInput_Disable( hri_tc_instance_t timer, hri_tc_event_input_t event );
static inline void HRI_TC_EventInputAction_Set( hri_tc_instance_t timer, hri_tc_event_input_action_t action );

static inline void HRI_TC_EventOutput_Enable( hri_tc_instance_t timer, hri_tc_event_output_t event );
static inline void HRI_TC_EventOutput_Disable( hri_tc_instance_t timer, hri_tc_event_output_t event );

void HRI_TC_Interrupt_Callback_Set( hri_tc_instance_t timer, hri_tc_interrupt_callback_t callback );
static inline void HRI_TC_Interrupt_Enable( hri_tc_instance_t timer, hri_tc_interrupt_t interrupt );
static inline void HRI_TC_Interrupt_Disable( hri_tc_instance_t timer, hri_tc_interrupt_t interrupt );
static inline bool HRI_TC_InterruptFlag_Get( hri_tc_instance_t timer, hri_tc_interrupt_t interrupt );
static inline void HRI_TC_InterruptFlag_Clear( hri_tc_instance_t timer, hri_tc_interrupt_t interrupt );

static inline bool HRI_TC_isStopped( hri_tc_instance_t timer );
static inline bool HRI_TC_isRunning( hri_tc_instance_t timer );

static inline void HRI_TC_Count8_Set( hri_tc_instance_t timer, uint8_t count );
static inline void HRI_TC_Count16_Set( hri_tc_instance_t timer, uint16_t count );
static inline void HRI_TC_Count32_Set( hri_tc_instance_t timer, uint32_t count );
static inline uint8_t HRI_TC_Count8_Get( hri_tc_instance_t timer );
static inline uint16_t HRI_TC_Count16_Get( hri_tc_instance_t timer );
static inline uint32_t HRI_TC_Count32_Get( hri_tc_instance_t timer );

static inline void HRI_TC_Period8_Set( hri_tc_instance_t timer, uint8_t period );
static inline uint8_t HRI_TC_Period8_Get( hri_tc_instance_t timer );

static inline void HRI_TC_Compare8_Set( hri_tc_instance_t timer, hri_tc_channel_t channel, uint8_t compare );
static inline void HRI_TC_Compare16_Set( hri_tc_instance_t timer, hri_tc_channel_t channel, uint16_t compare );
static inline void HRI_TC_Compare32_Set( hri_tc_instance_t timer, hri_tc_channel_t channel, uint32_t compare );
static inline uint8_t HRI_TC_Compare8_Get( hri_tc_instance_t timer, hri_tc_channel_t channel );
static inline uint16_t HRI_TC_Compare16_Get( hri_tc_instance_t timer, hri_tc_channel_t channel );
static inline uint32_t HRI_TC_Compare32_Get( hri_tc_instance_t timer, hri_tc_channel_t channel );

static inline uint8_t HRI_TC_Capture8_Get( hri_tc_instance_t timer, hri_tc_channel_t channel );
static inline uint16_t HRI_TC_Capture16_Get( hri_tc_instance_t timer, hri_tc_channel_t channel );
static inline uint32_t HRI_TC_Capture32_Get( hri_tc_instance_t timer, hri_tc_channel_t channel );


#define INCLUDE_HRI_TC_INLINE_H
#include "src/hri_tc_inline.h"
#undef INCLUDE_HRI_TC_INLINE_H


#ifdef __cplusplus
}
#endif

#endif  // ECLAY_HRI_TC_H
