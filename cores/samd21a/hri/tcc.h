#ifndef ECLAY_HRI_TCC_H
#define ECLAY_HRI_TCC_H

#include "hri/sam.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
  HRI_TCC_INSTANCE_TCC0 = 0,
  HRI_TCC_INSTANCE_TCC1,
  HRI_TCC_INSTANCE_TCC2,
#if (TC_INST_NUM == 4)
  HRI_TCC_INSTANCE_TCC3,
#endif
  NUM_HRI_TCC_INSTANCES,
  NOT_A_HRI_TCC_INSTANCE = NUM_HRI_TCC_INSTANCES
} hri_tcc_instance_t;

typedef enum {
  HRI_TCC_CHANNEL_MC0 = 0,
  HRI_TCC_CHANNEL_MC1 = 1,
  HRI_TCC_CHANNEL_MC2 = 2,
  HRI_TCC_CHANNEL_MC3 = 3,
} hri_tcc_channel_t;

typedef enum {
  HRI_TCC_WAVEFORM_NORMAL_FREQUENCY    = 0x0,
  HRI_TCC_WAVEFORM_MATCH_FREQUENCY     = 0x1,
  HRI_TCC_WAVEFORM_NORMAL_PWM          = 0x2,
  HRI_TCC_WAVEFORM_DUAL_SLOPE_CRITICAL = 0x4,
  HRI_TCC_WAVEFORM_DUAL_SLOPE_BOTTOM   = 0x5,
  HRI_TCC_WAVEFORM_DUAL_SLOPE_BOTH     = 0x6,
  HRI_TCC_WAVEFORM_DUAL_SLOPE_TOP      = 0x7,
} hri_tcc_waveform_t;

typedef enum {
  HRI_TCC_INTERRUPT_MC0 = 0,
  HRI_TCC_INTERRUPT_MC1,
  HRI_TCC_INTERRUPT_MC2,
  HRI_TCC_INTERRUPT_MC3,
  HRI_TCC_INTERRUPT_FAULT0,
  HRI_TCC_INTERRUPT_FAULT1,
  HRI_TCC_INTERRUPT_FAULTA,
  HRI_TCC_INTERRUPT_FAULTB,
  HRI_TCC_INTERRUPT_FAULT_DEBUG,
  HRI_TCC_INTERRUPT_FAULT_UPDATE,
  HRI_TCC_INTERRUPT_ERROR,
  HRI_TCC_INTERRUPT_COUNTER,
  HRI_TCC_INTERRUPT_RETRIGGER,
  HRI_TCC_INTERRUPT_OVERFLOW,
} hri_tcc_interrupt_t;

typedef enum {
  HRI_TCC_EVENT_INPUT_MC0 = 0,
  HRI_TCC_EVENT_INPUT_MC1,
  HRI_TCC_EVENT_INPUT_MC2,
  HRI_TCC_EVENT_INPUT_MC3,
  HRI_TCC_EVENT_INPUT_EV0,
  HRI_TCC_EVENT_INPUT_EV0_INVERTED,
  HRI_TCC_EVENT_INPUT_EV1,
  HRI_TCC_EVENT_INPUT_EV1_INVERTED
} hri_tcc_event_input_t;

typedef enum {
  HRI_TCC_EVENT_INPUT0_ACTION_OFF          = 0x0,
  HRI_TCC_EVENT_INPUT0_ACTION_RETRIGGER    = 0x1,
  HRI_TCC_EVENT_INPUT0_ACTION_COUNT_EVENT  = 0x2,
  HRI_TCC_EVENT_INPUT0_ACTION_START        = 0x3,
  HRI_TCC_EVENT_INPUT0_ACTION_INCREMENT    = 0x4,
  HRI_TCC_EVENT_INPUT0_ACTION_COUNT_ASYNC  = 0x5,
  HRI_TCC_EVENT_INPUT0_ACTION_FAULT        = 0x7,
} hri_tcc_event_input0_action_t;

typedef enum {
  HRI_TCC_EVENT_INPUT1_ACTION_OFF          = 0x0,
  HRI_TCC_EVENT_INPUT1_ACTION_RETRIGGER    = 0x1,
  HRI_TCC_EVENT_INPUT1_ACTION_DIR_ASYNC    = 0x2,
  HRI_TCC_EVENT_INPUT1_ACTION_STOP         = 0x3,
  HRI_TCC_EVENT_INPUT1_ACTION_DECREMENT    = 0x4,
  HRI_TCC_EVENT_INPUT1_ACTION_PPW          = 0x5,
  HRI_TCC_EVENT_INPUT1_ACTION_PWP          = 0x6,
  HRI_TCC_EVENT_INPUT1_ACTION_FAULT        = 0x7,
} hri_tcc_event_input1_action_t;

typedef enum {
  HRI_TCC_EVENT_OUTPUT_MC0 = 0,
  HRI_TCC_EVENT_OUTPUT_MC1,
  HRI_TCC_EVENT_OUTPUT_MC2,
  HRI_TCC_EVENT_OUTPUT_MC3,
  HRI_TCC_EVENT_OUTPUT_COUNT,
  HRI_TCC_EVENT_OUTPUT_RETRIGGER,
  HRI_TCC_EVENT_OUTPUT_OVERFLOW,
} hri_tcc_event_output_t;

typedef enum {
  HRI_TCC_EVENT_COUNT_MODE_BEGIN    = 0x0,
  HRI_TCC_EVENT_COUNT_MODE_END      = 0x1,
  HRI_TCC_EVENT_COUNT_MODE_BETWEEN  = 0x2,
  HRI_TCC_EVENT_COUNT_MODE_BOUNDARY = 0x3,
} hri_tcc_event_count_mode_t;


void HRI_TCC_InitializeAll( void );


static inline void HRI_TCC_SoftwareReset(
    hri_tcc_instance_t  timer
  );


static inline void HRI_TCC_Enable(
    hri_tcc_instance_t  timer
  );

static inline void HRI_TCC_Disable(
    hri_tcc_instance_t  timer
  );


static inline void HRI_TCC_Waveform_Set(
    hri_tcc_instance_t  timer,
    hri_tcc_waveform_t  waveform
  );


static inline void HRI_TCC_Period_Set(
    hri_tcc_instance_t  timer,
    uint32_t                  period
  );

static inline void HRI_TCC_Count_Set(
    hri_tcc_instance_t  timer,
    uint32_t                  count
  );

static inline uint32_t HRI_TCC_Count_Get(
    hri_tcc_instance_t  timer
  );

static inline void HRI_TCC_Compare_Set(
    hri_tcc_instance_t  timer,
    hri_tcc_channel_t   channel,
    uint32_t                  compare
  );

static inline uint32_t HRI_TCC_Capture_Get(
    hri_tcc_instance_t  timer,
    hri_tcc_channel_t   channel
  );


static inline void HRI_TCC_Pattern_Set(
    hri_tcc_instance_t  timer,
    uint8_t                   enable,
    uint8_t                   value
  );

static inline void HRI_TCC_PatternEnable_Set(
    hri_tcc_instance_t  timer,
    uint8_t                   enable
  );

static inline void HRI_TCC_PatternValue_Set(
    hri_tcc_instance_t  timer,
    uint8_t                   value
  );

static inline __IO uint16_t* HRI_TCC_PatternRegister(
    hri_tcc_instance_t  timer
  );

static inline __IO uint8_t* HRI_TCC_PatternRegisterEnable(
    hri_tcc_instance_t  timer
  );

static inline __IO uint8_t* HRI_TCC_PatternRegisterValue(
    hri_tcc_instance_t  timer
  );


static inline void HRI_TCC_CMD_Retrigger(
    hri_tcc_instance_t  timer
  );

static inline void HRI_TCC_CMD_Stop(
    hri_tcc_instance_t  timer
  );

static inline void HRI_TCC_CMD_Update(
    hri_tcc_instance_t  timer
  );

static inline void HRI_TCC_CMD_ReadSync(
    hri_tcc_instance_t  timer
  );


static inline void HRI_TCC_EVENT_Input_Enable(
    hri_tcc_instance_t      timer,
    hri_tcc_event_input_t   event
  );

static inline void HRI_TCC_EVENT_Input_Disable(
    hri_tcc_instance_t      timer,
    hri_tcc_event_input_t   event
  );

static inline void HRI_TCC_EVENT_InputAction0_Set(
    hri_tcc_instance_t            timer,
    hri_tcc_event_input0_action_t action
  );

static inline void HRI_TCC_EVENT_InputAction1_Set(
    hri_tcc_instance_t            timer,
    hri_tcc_event_input1_action_t action
  );


static inline void HRI_TCC_EVENT_Output_Enable(
    hri_tcc_instance_t      timer,
    hri_tcc_event_output_t  event
  );

static inline void HRI_TCC_EVENT_Output_Disable(
    hri_tcc_instance_t      timer,
    hri_tcc_event_output_t  event
  );

static inline void HRI_TCC_EVENT_CountMode_Set(
    hri_tcc_instance_t          timer,
    hri_tcc_event_count_mode_t  mode
  );


#define INCLUDE_HRI_TCC_INLINE_H
#include "src/hri_tcc_inline.h"
#undef INCLUDE_HRI_TCC_INLINE_H


#ifdef __cplusplus
}
#endif

#endif  // ECLAY_HRI_TCC_H
