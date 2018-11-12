#include "processor/dma.h"

#include "processor/sam.h"
#include "utils/utils.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Section containing first descriptors for all DMAC channels
COMPILER_ALIGNED(16)
static processor_dma_descriptor_t _descriptor_section[PROCESSOR_DMA_NUM_CHANNELS] SECTION_DMAC_DESCRIPTOR;

// Section containing current descriptors for all DMAC channels
COMPILER_ALIGNED(16)
static processor_dma_descriptor_t _write_back_section[PROCESSOR_DMA_NUM_CHANNELS] SECTION_DMAC_DESCRIPTOR;

typedef struct
{
  processor_dma_suspend_callback_t       suspend_callback;
  processor_dma_transfer_done_callback_t transfer_done_callback;
	processor_dma_error_callback_t         error_callback;
} processor_dma_callbacks_t;

static processor_dma_callbacks_t _interrupt_callbacks[PROCESSOR_DMA_NUM_CHANNELS];


void PROCESSOR_DMA_Initialize( void )
{
  uint8_t i = 0;

  // Reset DMAC module
  CRITICAL_SECTION_ENTER();
  DMAC->CTRL.bit.DMAENABLE = 0;
  DMAC->CTRL.bit.CRCENABLE = 0;
  DMAC->CTRL.bit.SWRST = 1;
  while( DMAC->CTRL.bit.SWRST );
  CRITICAL_SECTION_LEAVE();

  // hri_dmac_write_PRICTRL0_reg(
  //     DMAC,
  //     DMAC_PRICTRL0_LVLPRI0(CONF_DMAC_LVLPRI0) | DMAC_PRICTRL0_LVLPRI1(CONF_DMAC_LVLPRI1)
  //         | DMAC_PRICTRL0_LVLPRI2(CONF_DMAC_LVLPRI2) | DMAC_PRICTRL0_LVLPRI3(CONF_DMAC_LVLPRI3)
  //         | (CONF_DMAC_RRLVLEN0 << DMAC_PRICTRL0_RRLVLEN0_Pos) | (CONF_DMAC_RRLVLEN1 << DMAC_PRICTRL0_RRLVLEN1_Pos)
  //         | (CONF_DMAC_RRLVLEN2 << DMAC_PRICTRL0_RRLVLEN2_Pos) | (CONF_DMAC_RRLVLEN3 << DMAC_PRICTRL0_RRLVLEN3_Pos));

  DMAC->BASEADDR.reg = (uint32_t)_descriptor_section;
  DMAC->WRBADDR.reg  = (uint32_t)_write_back_section;

  NVIC_DisableIRQ(DMAC_IRQn);
  NVIC_ClearPendingIRQ(DMAC_IRQn);
  NVIC_EnableIRQ(DMAC_IRQn);

  DMAC->CTRL.bit.DMAENABLE = 1;
}

void PROCESSOR_DMA_Enable( void )
{
  CRITICAL_SECTION_ENTER();
  DMAC->CTRL.bit.DMAENABLE = 1;
  CRITICAL_SECTION_LEAVE();
}

void PROCESSOR_DMA_Disable( void )
{
  CRITICAL_SECTION_ENTER();
  DMAC->CTRL.bit.DMAENABLE = 0;
  CRITICAL_SECTION_LEAVE();
}


void PROCESSOR_DMA_PriorirtLevelEnable_Set(
    processor_dma_priority_level_t  level,
    bool enabled
  )
{
  CRITICAL_SECTION_ENTER();
  switch( level )
  {
    case PROCESSOR_DMA_PRIORITY_LEVEL_0:
      DMAC->CTRL.bit.LVLEN0 = (enabled ? 1 : 0);
      break;

    case PROCESSOR_DMA_PRIORITY_LEVEL_1:
      DMAC->CTRL.bit.LVLEN1 = (enabled ? 1 : 0);
      break;

    case PROCESSOR_DMA_PRIORITY_LEVEL_2:
      DMAC->CTRL.bit.LVLEN2 = (enabled ? 1 : 0);
      break;

    case PROCESSOR_DMA_PRIORITY_LEVEL_3:
      DMAC->CTRL.bit.LVLEN3 = (enabled ? 1 : 0);
      break;

    default:
      break;
  }
  CRITICAL_SECTION_LEAVE();
}


void PROCESSOR_DMA_CHANNEL_Enable( processor_dma_channel_t channel )
{
  if( channel >= PROCESSOR_DMA_NUM_CHANNELS )  return;

  CRITICAL_SECTION_ENTER();
  DMAC->CHID.reg = channel;
  DMAC->CHCTRLA.bit.ENABLE = 1;
  CRITICAL_SECTION_LEAVE();
}
void PROCESSOR_DMA_CHANNEL_Disable( processor_dma_channel_t channel )
{
  if( channel >= PROCESSOR_DMA_NUM_CHANNELS )  return;

  CRITICAL_SECTION_ENTER();
  DMAC->CHID.reg = channel;
  DMAC->CHCTRLA.bit.ENABLE = 0;
  CRITICAL_SECTION_LEAVE();
}

void PROCESSOR_DMA_CHANNEL_Reset( processor_dma_channel_t channel )
{
  if( channel >= PROCESSOR_DMA_NUM_CHANNELS )  return;

  CRITICAL_SECTION_ENTER();
  DMAC->CHID.reg = channel;
  DMAC->CHCTRLA.bit.ENABLE = 0;
  DMAC->CHCTRLA.bit.SWRST = 1;
  while( DMAC->CHCTRLA.bit.SWRST );
  CRITICAL_SECTION_LEAVE();
}

void PROCESSOR_DMA_CHANNEL_SoftwareTrigger( processor_dma_channel_t channel )
{
  if( channel >= PROCESSOR_DMA_NUM_CHANNELS )  return;

  CRITICAL_SECTION_ENTER();
  DMAC->SWTRIGCTRL.reg |= _U_(1) << channel;
  CRITICAL_SECTION_LEAVE();
}

void PROCESSOR_DMA_CHANNEL_Suspend( processor_dma_channel_t channel )
{
  if( channel >= PROCESSOR_DMA_NUM_CHANNELS )  return;

  CRITICAL_SECTION_ENTER();
  DMAC->CHID.reg = channel;
  DMAC->CHCTRLB.bit.CMD = DMAC_CHCTRLB_CMD_SUSPEND_Val;
  CRITICAL_SECTION_LEAVE();
}

void PROCESSOR_DMA_CHANNEL_Resume( processor_dma_channel_t channel )
{
  if( channel >= PROCESSOR_DMA_NUM_CHANNELS )  return;

  CRITICAL_SECTION_ENTER();
  DMAC->CHID.reg = channel;
  DMAC->CHCTRLB.bit.CMD = DMAC_CHCTRLB_CMD_RESUME_Val;
  CRITICAL_SECTION_LEAVE();
}

void PROCESSOR_DMA_CHANNEL_TriggerAction_Set( 
    processor_dma_channel_t channel,
    processor_dma_trigger_action_t action
  )
{
  if( channel >= PROCESSOR_DMA_NUM_CHANNELS )  return;
  
  CRITICAL_SECTION_ENTER();
  DMAC->CHID.reg = channel;
  DMAC->CHCTRLB.bit.TRIGACT = action;
  CRITICAL_SECTION_LEAVE();
}

void PROCESSOR_DMA_CHANNEL_TriggerSource_Set(
    processor_dma_channel_t channel,
    processor_dma_trigger_source_t source
  )
{
  if( channel >= PROCESSOR_DMA_NUM_CHANNELS )  return;
  
  CRITICAL_SECTION_ENTER();
  DMAC->CHID.reg = channel;
  DMAC->CHCTRLB.bit.TRIGSRC = source;
  CRITICAL_SECTION_LEAVE();
}

void PROCESSOR_DMA_CHANNEL_ArbitrationLevel_Set(
    processor_dma_channel_t channel,
    processor_dma_priority_level_t level
  )
{
  if( channel >= PROCESSOR_DMA_NUM_CHANNELS )  return;
  
  CRITICAL_SECTION_ENTER();
  DMAC->CHID.reg = channel;
  DMAC->CHCTRLB.bit.LVL = level;
  CRITICAL_SECTION_LEAVE();
}

void PROCESSOR_DMA_CHANNEL_EventOutputEnable_Set(
    processor_dma_channel_t channel,
    bool enable
  )
{
  if( channel >= PROCESSOR_DMA_NUM_CHANNELS )  return;
  
  CRITICAL_SECTION_ENTER();
  DMAC->CHID.reg = channel;
  DMAC->CHCTRLB.bit.EVOE = (enable ? 1 : 0);
  CRITICAL_SECTION_LEAVE();
}

void PROCESSOR_DMA_CHANNEL_EventInputEnable_Set(
    processor_dma_channel_t channel,
    bool enable
  )
{
  if( channel >= PROCESSOR_DMA_NUM_CHANNELS )  return;
  
  CRITICAL_SECTION_ENTER();
  DMAC->CHID.reg = channel;
  DMAC->CHCTRLB.bit.EVIE = (enable ? 1 : 0);
  CRITICAL_SECTION_LEAVE();
}

void PROCESSOR_DMA_CHANNEL_EventInputAction_Set(
    processor_dma_channel_t channel,
    processor_dma_event_input_action_t action
  )
{
  if( channel >= PROCESSOR_DMA_NUM_CHANNELS )  return;
  
  CRITICAL_SECTION_ENTER();
  DMAC->CHID.reg = channel;
  DMAC->CHCTRLB.bit.EVACT = action;
  CRITICAL_SECTION_LEAVE();
}

void PROCESSOR_DMA_CHANNEL_ChannelSuspendCallback_Set(
    processor_dma_channel_t channel,
    processor_dma_transfer_done_callback_t callback
  )
{
  if( channel >= PROCESSOR_DMA_NUM_CHANNELS )  return;
  
  _interrupt_callbacks[channel].suspend_callback = callback;
}

void PROCESSOR_DMA_CHANNEL_TransferDoneCallback_Set(
    processor_dma_channel_t channel,
    processor_dma_transfer_done_callback_t callback
  )
{
  if( channel >= PROCESSOR_DMA_NUM_CHANNELS )  return;
  
  _interrupt_callbacks[channel].transfer_done_callback = callback;
}

void PROCESSOR_DMA_CHANNEL_ErrorCallback_Set(
    processor_dma_channel_t channel,
    processor_dma_error_callback_t callback
  )
{
  if( channel >= PROCESSOR_DMA_NUM_CHANNELS )  return;
  
  _interrupt_callbacks[channel].error_callback = callback;
}

void PROCESSOR_DMA_CHANNEL_ChannelSuspendInterruptEnable_Set(
    processor_dma_channel_t channel,
    bool enable
  )
{
  if( channel >= PROCESSOR_DMA_NUM_CHANNELS )  return;
  
  CRITICAL_SECTION_ENTER();
  DMAC->CHID.reg = channel;
  if( enable )
  {
    DMAC->CHINTENSET.reg = DMAC_CHINTENSET_SUSP;
  }
  else
  {
    DMAC->CHINTENCLR.reg = DMAC_CHINTENSET_SUSP;
  }
  CRITICAL_SECTION_LEAVE();
}

void PROCESSOR_DMA_CHANNEL_TransferDoneInterruptEnable_Set(
    processor_dma_channel_t channel,
    bool enable
  )
{
  if( channel >= PROCESSOR_DMA_NUM_CHANNELS )  return;
  
  CRITICAL_SECTION_ENTER();
  DMAC->CHID.reg = channel;
  if( enable )
  {
    DMAC->CHINTENSET.reg = DMAC_CHINTENSET_TCMPL;
  }
  else
  {
    DMAC->CHINTENCLR.reg = DMAC_CHINTENCLR_TCMPL;
  }
  CRITICAL_SECTION_LEAVE();
}

void PROCESSOR_DMA_CHANNEL_ErrorInterruptEnable_Set(
    processor_dma_channel_t channel,
    bool enable
  )
{
  if( channel >= PROCESSOR_DMA_NUM_CHANNELS )  return;
  
  CRITICAL_SECTION_ENTER();
  DMAC->CHID.reg = channel;
  if( enable )
  {
    DMAC->CHINTENSET.reg = DMAC_CHINTENSET_TERR;
  }
  else
  {
    DMAC->CHINTENCLR.reg = DMAC_CHINTENCLR_TERR;
  }
  CRITICAL_SECTION_LEAVE();
}

void PROCESSOR_DMA_CHANNEL_ChannelSuspendInterruptFlag_Clear(
    processor_dma_channel_t channel
  )
{
  if( channel >= PROCESSOR_DMA_NUM_CHANNELS )  return;
  
  CRITICAL_SECTION_ENTER();
  DMAC->CHID.reg = channel;
  DMAC->CHINTFLAG.bit.SUSP = 1;
  CRITICAL_SECTION_LEAVE();
}

void PROCESSOR_DMA_CHANNEL_TransferDoneInterruptFlag_Clear(
    processor_dma_channel_t channel
  )
{
  if( channel >= PROCESSOR_DMA_NUM_CHANNELS )  return;
  
  CRITICAL_SECTION_ENTER();
  DMAC->CHID.reg = channel;
  DMAC->CHINTFLAG.bit.TCMPL = 1;
  CRITICAL_SECTION_LEAVE();
}

void PROCESSOR_DMA_CHANNEL_ErrorInterruptFlag_Clear(
    processor_dma_channel_t channel
  )
{
  if( channel >= PROCESSOR_DMA_NUM_CHANNELS )  return;

  CRITICAL_SECTION_ENTER();
  DMAC->CHID.reg = channel;
  DMAC->CHINTFLAG.bit.TERR = 1;
  CRITICAL_SECTION_LEAVE();
}

bool PROCESSOR_DMA_CHANNEL_isBusy(
    processor_dma_channel_t channel
  )
{
  if( channel >= PROCESSOR_DMA_NUM_CHANNELS )  return false;

  return (DMAC->BUSYCH.reg | (_U_(1) << channel)) != 0;
}

bool PROCESSOR_DMA_CHANNEL_isPending(
    processor_dma_channel_t channel
  )
{
  if( channel >= PROCESSOR_DMA_NUM_CHANNELS )  return false;

  return (DMAC->PENDCH.reg | (_U_(1) << channel)) != 0;
}


processor_dma_descriptor_t* PROCESSOR_DMA_CHANNEL_Descriptor_Get( 
    processor_dma_channel_t channel
  )
{
  if( channel >= PROCESSOR_DMA_NUM_CHANNELS )  return NULL;

  return &_descriptor_section[channel];
}

processor_dma_descriptor_t* PROCESSOR_DMA_CHANNEL_Writeback_Get( 
    processor_dma_channel_t channel
  )
{
  if( channel >= PROCESSOR_DMA_NUM_CHANNELS )  return NULL;

  return &_write_back_section[channel];
}


void PROCESSOR_DMA_DESCRIPTOR_SourceAddress_Set(
    processor_dma_descriptor_t* descriptor,
    const void* address 
  )
{
  if( descriptor == NULL )  return;

  descriptor->SRCADDR.reg = (uint32_t)address;
}

void PROCESSOR_DMA_DESCRIPTOR_DestinationAddress_Set(
    processor_dma_descriptor_t* descriptor,
    const void* address
  )
{
  if( descriptor == NULL )  return;

  descriptor->DSTADDR.reg = (uint32_t)address;
}

void PROCESSOR_DMA_DESCRIPTOR_SourceIncrement_Set(
    processor_dma_descriptor_t* descriptor,
    bool enable
  )
{
  if( descriptor == NULL )  return;

  descriptor->BTCTRL.bit.SRCINC = (enable ? 1 : 0);
}

void PROCESSOR_DMA_DESCRIPTOR_DestinationIncrement_Set(
    processor_dma_descriptor_t* descriptor,
    bool enable
  )
{
  if( descriptor == NULL )  return;

  descriptor->BTCTRL.bit.DSTINC = (enable ? 1 : 0);
}

void PROCESSOR_DMA_DESCRIPTOR_IncrementStepSize_Set( 
    processor_dma_descriptor_t* descriptor,
    processor_dma_step_selection_t selection,
    processor_dma_addr_inc_step_size_t size
  )
{
  if( descriptor == NULL )  return;

  switch( selection )
  {
    case PROCESSOR_DMA_STEP_SELECTION_DESTINATION:
    default:
      descriptor->BTCTRL.bit.STEPSEL = DMAC_BTCTRL_STEPSEL_DST_Val;
      break;

    case PROCESSOR_DMA_STEP_SELECTION_SOURCE:
      descriptor->BTCTRL.bit.STEPSEL = DMAC_BTCTRL_STEPSEL_SRC_Val;
      break;
  }

  descriptor->BTCTRL.bit.STEPSIZE = size;
}

void PROCESSOR_DMA_DESCRIPTOR_BeatSize_Set(
    processor_dma_descriptor_t* descriptor,
    processor_dma_beat_size_t size
  )
{
  if( descriptor == NULL )  return;

  descriptor->BTCTRL.bit.BEATSIZE = size;
}

void PROCESSOR_DMA_DESCRIPTOR_BlockAction_Set(
    processor_dma_descriptor_t* descriptor,
    processor_dma_block_action_t action
  )
{
  if( descriptor == NULL )  return;

  descriptor->BTCTRL.bit.BLOCKACT = action;
}

void PROCESSOR_DMA_DESCRIPTOR_EventOutput_Set(
    processor_dma_descriptor_t* descriptor,
    processor_dma_event_output_selection_t output
  )
{
  if( descriptor == NULL )  return;

  descriptor->BTCTRL.bit.EVOSEL = output;
}

void PROCESSOR_DMA_DESCRIPTOR_BlockSize_Set(
    processor_dma_descriptor_t* descriptor,
    uint32_t size 
  )
{  
  if( descriptor == NULL )  return;

  uint32_t address;
  uint8_t  beat_size = descriptor->BTCTRL.bit.BEATSIZE;

  if( descriptor->BTCTRL.bit.DSTINC )
  {
    address = descriptor->DSTADDR.reg;
    address = address + (size * (1 << beat_size));
    descriptor->DSTADDR.reg = address;
  }

  if( descriptor->BTCTRL.bit.SRCINC )
  {
    address = descriptor->SRCADDR.reg;
    address = address + (size * (1 << beat_size));
    descriptor->SRCADDR.reg = address;
  }

	descriptor->BTCNT.reg = size;
}

void PROCESSOR_DMA_DESCRIPTOR_NextDescriptor_Set(
    processor_dma_descriptor_t* descriptor,
    const processor_dma_descriptor_t* next
  )
{
  if( descriptor == NULL )  return;

  descriptor->DESCADDR.reg = (uint32_t)next;
}

/**
 * \internal DMAC interrupt handler
 */
static inline void _dmac_handler(void)
{
// 	uint8_t               channel      = hri_dmac_read_INTPEND_ID_bf(DMAC);
// 	struct _dma_resource *tmp_resource = &_resources[channel];

// 	hri_dmac_write_CHID_reg(DMAC, channel);

// 	if (hri_dmac_get_CHINTFLAG_TERR_bit(DMAC)) {
// 		hri_dmac_clear_CHINTFLAG_TERR_bit(DMAC);
// 		tmp_resource->dma_cb.error(tmp_resource);
// 	} else if (hri_dmac_get_CHINTFLAG_TCMPL_bit(DMAC)) {
// 		hri_dmac_clear_CHINTFLAG_TCMPL_bit(DMAC);
// 		tmp_resource->dma_cb.transfer_done(tmp_resource);
// 	}
}

/**
 * \brief DMAC interrupt handler
 */
void DMAC_Handler(void)
{
	_dmac_handler();
}
