#ifndef ECLAY_PROCESSOR_DMAC_H
#define ECLAY_PROCESSOR_DMAC_H

#include "processor/sam.h"

#include <stdbool.h>
#include <stdint.h>


#ifdef __cplusplus
extern "C" {
#endif


#define PROCESSOR_DMAC_NUM_CHANNELS    DMAC_CH_NUM
typedef uint8_t  processor_dmac_channel_t;

typedef DmacDescriptor  processor_dmac_descriptor_t;


typedef enum
{
  PROCESSOR_DMAC_COMMAND_NO_ACTION = DMAC_CHCTRLB_CMD_NOACT_Val,
  PROCESSOR_DMAC_COMMAND_SUSPEND   = DMAC_CHCTRLB_CMD_SUSPEND_Val,
  PROCESSOR_DMAC_COMMAND_RESUME    = DMAC_CHCTRLB_CMD_RESUME_Val
} processor_dmac_command_t;

typedef enum
{
  PROCESSOR_DMAC_TRIGGER_ACTION_BLOCK       = DMAC_CHCTRLB_TRIGACT_BLOCK_Val,
  PROCESSOR_DMAC_TRIGGER_ACTION_BEAT        = DMAC_CHCTRLB_TRIGACT_BEAT_Val,
  PROCESSOR_DMAC_TRIGGER_ACTION_TRANSACTION = DMAC_CHCTRLB_TRIGACT_TRANSACTION_Val
} processor_dmac_trigger_action_t;

typedef enum
{
  PROCESSOR_DMAC_TRIGGER_SOURCE_DISABLE     = 0x00,
  PROCESSOR_DMAC_TRIGGER_SOURCE_SERCOM0_RX  = 0x01,
  PROCESSOR_DMAC_TRIGGER_SOURCE_SERCOM0_TX  = 0x02,
  PROCESSOR_DMAC_TRIGGER_SOURCE_SERCOM1_RX  = 0x03,
  PROCESSOR_DMAC_TRIGGER_SOURCE_SERCOM1_TX  = 0x04,
  PROCESSOR_DMAC_TRIGGER_SOURCE_SERCOM2_RX  = 0x05,
  PROCESSOR_DMAC_TRIGGER_SOURCE_SERCOM2_TX  = 0x06,
  PROCESSOR_DMAC_TRIGGER_SOURCE_SERCOM3_RX  = 0x07,
  PROCESSOR_DMAC_TRIGGER_SOURCE_SERCOM3_TX  = 0x08,
  PROCESSOR_DMAC_TRIGGER_SOURCE_SERCOM4_RX  = 0x09,
  PROCESSOR_DMAC_TRIGGER_SOURCE_SERCOM4_TX  = 0x0A,
  PROCESSOR_DMAC_TRIGGER_SOURCE_SERCOM5_RX  = 0x0B,
  PROCESSOR_DMAC_TRIGGER_SOURCE_SERCOM5_TX  = 0x0C,
  PROCESSOR_DMAC_TRIGGER_SOURCE_TCC0_OVF    = 0x0D,
  PROCESSOR_DMAC_TRIGGER_SOURCE_TCC0_MC0    = 0x0E,
  PROCESSOR_DMAC_TRIGGER_SOURCE_TCC0_MC1    = 0x0F,
  PROCESSOR_DMAC_TRIGGER_SOURCE_TCC0_MC2    = 0x10,
  PROCESSOR_DMAC_TRIGGER_SOURCE_TCC0_MC3    = 0x11,
  PROCESSOR_DMAC_TRIGGER_SOURCE_TCC1_OVF    = 0x12,
  PROCESSOR_DMAC_TRIGGER_SOURCE_TCC1_MC0    = 0x13,
  PROCESSOR_DMAC_TRIGGER_SOURCE_TCC1_MC1    = 0x14,
  PROCESSOR_DMAC_TRIGGER_SOURCE_TCC2_OVF    = 0x15,
  PROCESSOR_DMAC_TRIGGER_SOURCE_TCC2_MC0    = 0x16,
  PROCESSOR_DMAC_TRIGGER_SOURCE_TCC2_MC1    = 0x17,
  PROCESSOR_DMAC_TRIGGER_SOURCE_TC3_OVF     = 0x18,
  PROCESSOR_DMAC_TRIGGER_SOURCE_TC3_MC0     = 0x19,
  PROCESSOR_DMAC_TRIGGER_SOURCE_TC3_MC1     = 0x1A,
  PROCESSOR_DMAC_TRIGGER_SOURCE_TC4_OVF     = 0x1B,
  PROCESSOR_DMAC_TRIGGER_SOURCE_TC4_MC0     = 0x1C,
  PROCESSOR_DMAC_TRIGGER_SOURCE_TC4_MC1     = 0x1D,
  PROCESSOR_DMAC_TRIGGER_SOURCE_TC5_OVF     = 0x1E,
  PROCESSOR_DMAC_TRIGGER_SOURCE_TC5_MC0     = 0x1F,
  PROCESSOR_DMAC_TRIGGER_SOURCE_TC5_MC1     = 0x20,
  PROCESSOR_DMAC_TRIGGER_SOURCE_TC6_OVF     = 0x21,
  PROCESSOR_DMAC_TRIGGER_SOURCE_TC6_MC0     = 0x22,
  PROCESSOR_DMAC_TRIGGER_SOURCE_TC6_MC1     = 0x23,
  PROCESSOR_DMAC_TRIGGER_SOURCE_TC7_OVF     = 0x24,
  PROCESSOR_DMAC_TRIGGER_SOURCE_TC7_MC0     = 0x25,
  PROCESSOR_DMAC_TRIGGER_SOURCE_TC7_MC1     = 0x26,
  PROCESSOR_DMAC_TRIGGER_SOURCE_ADC_RESRDY  = 0x27,
  PROCESSOR_DMAC_TRIGGER_SOURCE_DAC_EMPTY   = 0x28,
  PROCESSOR_DMAC_TRIGGER_SOURCE_I2S_RX0     = 0x29,
  PROCESSOR_DMAC_TRIGGER_SOURCE_I2S_RX1     = 0x2A,
  PROCESSOR_DMAC_TRIGGER_SOURCE_I2S_TX0     = 0x2B,
  PROCESSOR_DMAC_TRIGGER_SOURCE_I2S_TX1     = 0x2C,
} processor_dmac_trigger_source_t;

typedef enum
{
  PROCESSOR_DMAC_PRIORITY_LEVEL_0 = DMAC_CHCTRLB_LVL_LVL0_Val,
  PROCESSOR_DMAC_PRIORITY_LEVEL_1 = DMAC_CHCTRLB_LVL_LVL1_Val,
  PROCESSOR_DMAC_PRIORITY_LEVEL_2 = DMAC_CHCTRLB_LVL_LVL2_Val,
  PROCESSOR_DMAC_PRIORITY_LEVEL_3 = DMAC_CHCTRLB_LVL_LVL3_Val,
} processor_dmac_priority_level_t;

typedef enum
{
  PROCESSOR_DMAC_EVENT_INPUT_ACTION_NOACT   = DMAC_CHCTRLB_EVACT_NOACT_Val,
  PROCESSOR_DMAC_EVENT_INPUT_ACTION_TRIG    = DMAC_CHCTRLB_EVACT_TRIG_Val,
  PROCESSOR_DMAC_EVENT_INPUT_ACTION_CTRIG   = DMAC_CHCTRLB_EVACT_CTRIG_Val,
  PROCESSOR_DMAC_EVENT_INPUT_ACTION_CBLOCK  = DMAC_CHCTRLB_EVACT_CBLOCK_Val,
  PROCESSOR_DMAC_EVENT_INPUT_ACTION_SUSPEND = DMAC_CHCTRLB_EVACT_SUSPEND_Val,
  PROCESSOR_DMAC_EVENT_INPUT_ACTION_RESUME  = DMAC_CHCTRLB_EVACT_RESUME_Val,
  PROCESSOR_DMAC_EVENT_INPUT_ACTION_SSKIP   = DMAC_CHCTRLB_EVACT_SSKIP_Val,
} processor_dmac_event_input_action_t;

typedef enum
{
  PROCESSOR_DMAC_BEAT_SIZE_1BYTE = DMAC_BTCTRL_BEATSIZE_BYTE_Val,
  PROCESSOR_DMAC_BEAT_SIZE_2BYTE = DMAC_BTCTRL_BEATSIZE_HWORD_Val,
  PROCESSOR_DMAC_BEAT_SIZE_4BYTE = DMAC_BTCTRL_BEATSIZE_WORD_Val
} processor_dmac_beat_size_t;

typedef enum
{
	PROCESSOR_DMAC_STEP_SELECTION_DESTINATION = DMAC_BTCTRL_STEPSEL_DST_Val,
	PROCESSOR_DMAC_STEP_SELECTION_SOURCE      = DMAC_BTCTRL_STEPSEL_SRC_Val,
} processor_dmac_step_selection_t;

typedef enum
{
	PROCESSOR_DMAC_ADDR_INC_STEP_SIZE_X1   = DMAC_BTCTRL_STEPSIZE_X1_Val,
	PROCESSOR_DMAC_ADDR_INC_STEP_SIZE_X2   = DMAC_BTCTRL_STEPSIZE_X2_Val,
	PROCESSOR_DMAC_ADDR_INC_STEP_SIZE_X4   = DMAC_BTCTRL_STEPSIZE_X4_Val,
	PROCESSOR_DMAC_ADDR_INC_STEP_SIZE_X8   = DMAC_BTCTRL_STEPSIZE_X8_Val,
	PROCESSOR_DMAC_ADDR_INC_STEP_SIZE_X16  = DMAC_BTCTRL_STEPSIZE_X16_Val,
	PROCESSOR_DMAC_ADDR_INC_STEP_SIZE_X32  = DMAC_BTCTRL_STEPSIZE_X32_Val,
	PROCESSOR_DMAC_ADDR_INC_STEP_SIZE_X64  = DMAC_BTCTRL_STEPSIZE_X64_Val,
	PROCESSOR_DMAC_ADDR_INC_STEP_SIZE_X128 = DMAC_BTCTRL_STEPSIZE_X128_Val,
} processor_dmac_addr_inc_step_size_t;

typedef enum
{
  PROCESSOR_DMAC_BLOCK_ACTION_NONE      = DMAC_BTCTRL_BLOCKACT_NOACT_Val,
  PROCESSOR_DMAC_BLOCK_ACTION_INTERRUPT = DMAC_BTCTRL_BLOCKACT_INT_Val,
  PROCESSOR_DMAC_BLOCK_ACTION_SUSPEND   = DMAC_BTCTRL_BLOCKACT_SUSPEND_Val,
  PROCESSOR_DMAC_BLOCK_ACTION_BOTH      = DMAC_BTCTRL_BLOCKACT_BOTH_Val
} processor_dmac_block_action_t;

typedef enum
{
  PROCESSOR_DMAC_EVENT_OUTPUT_DISABLE = DMAC_BTCTRL_EVOSEL_DISABLE_Val,
  PROCESSOR_DMAC_EVENT_OUTPUT_BLOCK   = DMAC_BTCTRL_EVOSEL_BLOCK_Val,
  PROCESSOR_DMAC_EVENT_OUTPUT_BEAT    = DMAC_BTCTRL_EVOSEL_BEAT_Val
} processor_dmac_event_output_selection_t;

typedef enum
{
  PROCESSOR_DMAC_INTERRUPT_SUSPEND,
  PROCESSOR_DMAC_INTERRUPT_TRANSFER_DONE,
  PROCESSOR_DMAC_INTERRUPT_ERROR,
} processor_dmac_interrupt_t;

typedef void (*processor_dmac_interrupt_callback_t)( processor_dmac_channel_t channel, processor_dmac_interrupt_t interrupt );


void PROCESSOR_DMAC_Initialize( void );


void PROCESSOR_DMAC_Enable( void );
void PROCESSOR_DMAC_Disable( void );

void PROCESSOR_DMAC_PriorityLevelEnable_Set(
    processor_dmac_priority_level_t  level,
    bool enabled
  );

void PROCESSOR_DMAC_PriorityLevelRoundRobinEnable_Set(
    processor_dmac_priority_level_t  level,
    bool enabled
  );

void PROCESSOR_DMAC_CHANNEL_Enable( processor_dmac_channel_t channel );
void PROCESSOR_DMAC_CHANNEL_Disable( processor_dmac_channel_t channel );

void PROCESSOR_DMAC_CHANNEL_Reset( processor_dmac_channel_t channel );

void PROCESSOR_DMAC_CHANNEL_SoftwareTrigger( processor_dmac_channel_t channel );
void PROCESSOR_DMAC_CHANNEL_Suspend( processor_dmac_channel_t channel );
void PROCESSOR_DMAC_CHANNEL_Resume( processor_dmac_channel_t channel );

void PROCESSOR_DMAC_CHANNEL_TriggerAction_Set( 
    processor_dmac_channel_t channel,
    processor_dmac_trigger_action_t action
  );

void PROCESSOR_DMAC_CHANNEL_TriggerSource_Set(
    processor_dmac_channel_t channel,
    processor_dmac_trigger_source_t source
  );

void PROCESSOR_DMAC_CHANNEL_ArbitrationLevel_Set(
    processor_dmac_channel_t channel,
    processor_dmac_priority_level_t level
  );

void PROCESSOR_DMAC_CHANNEL_EventOutputEnable_Set(
    processor_dmac_channel_t channel,
    bool enable
  );

void PROCESSOR_DMAC_CHANNEL_EventInputEnable_Set(
    processor_dmac_channel_t channel,
    bool enable
  );

void PROCESSOR_DMAC_CHANNEL_EventInputAction_Set(
    processor_dmac_channel_t channel,
    processor_dmac_event_input_action_t action
  );
  

void PROCESSOR_DMAC_CHANNEL_InterruptCallback_Set(
    processor_dmac_channel_t channel,
    processor_dmac_interrupt_callback_t callback
  );

void PROCESSOR_DMAC_CHANNEL_Interrupt_Enable(
    processor_dmac_channel_t channel,
    processor_dmac_interrupt_t interrupt
  );

void PROCESSOR_DMAC_CHANNEL_Interrupt_Disable(
    processor_dmac_channel_t channel,
    processor_dmac_interrupt_t interrupt
  );

void PROCESSOR_DMAC_CHANNEL_InterruptFlag_Clear(
    processor_dmac_channel_t channel,
    processor_dmac_interrupt_t interrupt
  );
  

bool PROCESSOR_DMAC_CHANNEL_isBusy(
    processor_dmac_channel_t channel
  );

bool PROCESSOR_DMAC_CHANNEL_isPending(
    processor_dmac_channel_t channel
  );


processor_dmac_descriptor_t* PROCESSOR_DMAC_CHANNEL_Descriptor_Get( 
    processor_dmac_channel_t channel
  );

processor_dmac_descriptor_t* PROCESSOR_DMAC_CHANNEL_Writeback_Get( 
    processor_dmac_channel_t channel
  );

void PROCESSOR_DMAC_DESCRIPTOR_SourceAddress_Set(
    processor_dmac_descriptor_t* descriptor,
    const void* address 
  );

void PROCESSOR_DMAC_DESCRIPTOR_DestinationAddress_Set(
    processor_dmac_descriptor_t* descriptor,
    const void* address
  );

void PROCESSOR_DMAC_DESCRIPTOR_SourceIncrement_Set(
    processor_dmac_descriptor_t* descriptor,
    bool enable
  );

void PROCESSOR_DMAC_DESCRIPTOR_DestinationIncrement_Set(
    processor_dmac_descriptor_t* descriptor,
    bool enable
  );

void PROCESSOR_DMAC_DESCRIPTOR_IncrementStepSize_Set( 
    processor_dmac_descriptor_t* descriptor,
    processor_dmac_step_selection_t selection,
    processor_dmac_addr_inc_step_size_t size
  );

void PROCESSOR_DMAC_DESCRIPTOR_BeatSize_Set(
    processor_dmac_descriptor_t* descriptor,
    processor_dmac_beat_size_t size
  );

void PROCESSOR_DMAC_DESCRIPTOR_BlockAction_Set(
    processor_dmac_descriptor_t* descriptor,
    processor_dmac_block_action_t action
  );

void PROCESSOR_DMAC_DESCRIPTOR_EventOutput_Set(
    processor_dmac_descriptor_t* descriptor,
    processor_dmac_event_output_selection_t output
  );

// BlockSize_Set MUST be called after setting Source Address, Destination
//   Address and Beat Size as it may need to modify address based on
//   increment settings, beat size, and block size.
void PROCESSOR_DMAC_DESCRIPTOR_BlockSize_Set(
    processor_dmac_descriptor_t* descriptor,
    uint32_t size 
  );

void PROCESSOR_DMAC_DESCRIPTOR_NextDescriptor_Set(
    processor_dmac_descriptor_t* descriptor,
    const processor_dmac_descriptor_t* next
  );


//********************************************************
// INLINE FUNCTION DEFINITIONS
//********************************************************


#endif  // ECLAY_PROCESSOR_DMAC_H
