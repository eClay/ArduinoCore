#include "hri/dmac.h"

#include "hri/sam.h"
#include "utils/utils.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Section containing first descriptors for all DMAC channels
COMPILER_ALIGNED(16)
static processor_dmac_descriptor_t _descriptor_section[PROCESSOR_DMAC_NUM_CHANNELS] SECTION_DMAC_DESCRIPTOR;

// Section containing current descriptors for all DMAC channels
COMPILER_ALIGNED(16)
static processor_dmac_descriptor_t _write_back_section[PROCESSOR_DMAC_NUM_CHANNELS] SECTION_DMAC_DESCRIPTOR;

static processor_dmac_interrupt_callback_t _interrupt_callback[PROCESSOR_DMAC_NUM_CHANNELS];


void PROCESSOR_DMAC_Initialize( void )
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

void PROCESSOR_DMAC_Enable( void )
{
  CRITICAL_SECTION_ENTER();
  DMAC->CTRL.bit.DMAENABLE = 1;
  CRITICAL_SECTION_LEAVE();
}

void PROCESSOR_DMAC_Disable( void )
{
  CRITICAL_SECTION_ENTER();
  DMAC->CTRL.bit.DMAENABLE = 0;
  CRITICAL_SECTION_LEAVE();
}


void PROCESSOR_DMAC_PriorirtLevelEnable_Set(
    processor_dmac_priority_level_t  level,
    bool enabled
  )
{
  CRITICAL_SECTION_ENTER();
  switch( level )
  {
    case PROCESSOR_DMAC_PRIORITY_LEVEL_0:
      DMAC->CTRL.bit.LVLEN0 = (enabled ? 1 : 0);
      break;

    case PROCESSOR_DMAC_PRIORITY_LEVEL_1:
      DMAC->CTRL.bit.LVLEN1 = (enabled ? 1 : 0);
      break;

    case PROCESSOR_DMAC_PRIORITY_LEVEL_2:
      DMAC->CTRL.bit.LVLEN2 = (enabled ? 1 : 0);
      break;

    case PROCESSOR_DMAC_PRIORITY_LEVEL_3:
      DMAC->CTRL.bit.LVLEN3 = (enabled ? 1 : 0);
      break;

    default:
      break;
  }
  CRITICAL_SECTION_LEAVE();
}

void PROCESSOR_DMAC_PriorityLevelRoundRobinEnable_Set(
    processor_dmac_priority_level_t  level,
    bool enabled
  )
{
  CRITICAL_SECTION_ENTER();
  switch( level )
  {
    case PROCESSOR_DMAC_PRIORITY_LEVEL_0:
      DMAC->PRICTRL0.bit.RRLVLEN0 = (enabled ? 1 : 0);
      break;

    case PROCESSOR_DMAC_PRIORITY_LEVEL_1:
      DMAC->PRICTRL0.bit.RRLVLEN1 = (enabled ? 1 : 0);
      break;

    case PROCESSOR_DMAC_PRIORITY_LEVEL_2:
      DMAC->PRICTRL0.bit.RRLVLEN2 = (enabled ? 1 : 0);
      break;

    case PROCESSOR_DMAC_PRIORITY_LEVEL_3:
      DMAC->PRICTRL0.bit.RRLVLEN3 = (enabled ? 1 : 0);
      break;

    default:
      break;
  }
  CRITICAL_SECTION_LEAVE();
}

void PROCESSOR_DMAC_CHANNEL_Enable( processor_dmac_channel_t channel )
{
  if( channel >= PROCESSOR_DMAC_NUM_CHANNELS )  return;

  CRITICAL_SECTION_ENTER();
  DMAC->CHID.reg = channel;
  DMAC->CHCTRLA.bit.ENABLE = 1;
  CRITICAL_SECTION_LEAVE();
}
void PROCESSOR_DMAC_CHANNEL_Disable( processor_dmac_channel_t channel )
{
  if( channel >= PROCESSOR_DMAC_NUM_CHANNELS )  return;

  CRITICAL_SECTION_ENTER();
  DMAC->CHID.reg = channel;
  DMAC->CHCTRLA.bit.ENABLE = 0;
  CRITICAL_SECTION_LEAVE();
}

void PROCESSOR_DMAC_CHANNEL_Reset( processor_dmac_channel_t channel )
{
  if( channel >= PROCESSOR_DMAC_NUM_CHANNELS )  return;

  CRITICAL_SECTION_ENTER();
  DMAC->CHID.reg = channel;
  DMAC->CHCTRLA.bit.ENABLE = 0;
  DMAC->CHCTRLA.bit.SWRST = 1;
  while( DMAC->CHCTRLA.bit.SWRST );
  CRITICAL_SECTION_LEAVE();
}

void PROCESSOR_DMAC_CHANNEL_SoftwareTrigger( processor_dmac_channel_t channel )
{
  if( channel >= PROCESSOR_DMAC_NUM_CHANNELS )  return;

  CRITICAL_SECTION_ENTER();
  DMAC->SWTRIGCTRL.reg |= _U_(1) << channel;
  CRITICAL_SECTION_LEAVE();
}

void PROCESSOR_DMAC_CHANNEL_Suspend( processor_dmac_channel_t channel )
{
  if( channel >= PROCESSOR_DMAC_NUM_CHANNELS )  return;

  CRITICAL_SECTION_ENTER();
  DMAC->CHID.reg = channel;
  DMAC->CHCTRLB.bit.CMD = DMAC_CHCTRLB_CMD_SUSPEND_Val;
  CRITICAL_SECTION_LEAVE();
}

void PROCESSOR_DMAC_CHANNEL_Resume( processor_dmac_channel_t channel )
{
  if( channel >= PROCESSOR_DMAC_NUM_CHANNELS )  return;

  CRITICAL_SECTION_ENTER();
  DMAC->CHID.reg = channel;
  DMAC->CHCTRLB.bit.CMD = DMAC_CHCTRLB_CMD_RESUME_Val;
  CRITICAL_SECTION_LEAVE();
}

void PROCESSOR_DMAC_CHANNEL_TriggerAction_Set( 
    processor_dmac_channel_t channel,
    processor_dmac_trigger_action_t action
  )
{
  if( channel >= PROCESSOR_DMAC_NUM_CHANNELS )  return;
  
  CRITICAL_SECTION_ENTER();
  DMAC->CHID.reg = channel;
  DMAC->CHCTRLB.bit.TRIGACT = action;
  CRITICAL_SECTION_LEAVE();
}

void PROCESSOR_DMAC_CHANNEL_TriggerSource_Set(
    processor_dmac_channel_t channel,
    processor_dmac_trigger_source_t source
  )
{
  if( channel >= PROCESSOR_DMAC_NUM_CHANNELS )  return;
  
  CRITICAL_SECTION_ENTER();
  DMAC->CHID.reg = channel;
  DMAC->CHCTRLB.bit.TRIGSRC = source;
  CRITICAL_SECTION_LEAVE();
}

void PROCESSOR_DMAC_CHANNEL_ArbitrationLevel_Set(
    processor_dmac_channel_t channel,
    processor_dmac_priority_level_t level
  )
{
  if( channel >= PROCESSOR_DMAC_NUM_CHANNELS )  return;
  
  CRITICAL_SECTION_ENTER();
  DMAC->CHID.reg = channel;
  DMAC->CHCTRLB.bit.LVL = level;
  CRITICAL_SECTION_LEAVE();
}

void PROCESSOR_DMAC_CHANNEL_EventOutputEnable_Set(
    processor_dmac_channel_t channel,
    bool enable
  )
{
  if( channel >= PROCESSOR_DMAC_NUM_CHANNELS )  return;
  
  CRITICAL_SECTION_ENTER();
  DMAC->CHID.reg = channel;
  DMAC->CHCTRLB.bit.EVOE = (enable ? 1 : 0);
  CRITICAL_SECTION_LEAVE();
}

void PROCESSOR_DMAC_CHANNEL_EventInputEnable_Set(
    processor_dmac_channel_t channel,
    bool enable
  )
{
  if( channel >= PROCESSOR_DMAC_NUM_CHANNELS )  return;
  
  CRITICAL_SECTION_ENTER();
  DMAC->CHID.reg = channel;
  DMAC->CHCTRLB.bit.EVIE = (enable ? 1 : 0);
  CRITICAL_SECTION_LEAVE();
}

void PROCESSOR_DMAC_CHANNEL_EventInputAction_Set(
    processor_dmac_channel_t channel,
    processor_dmac_event_input_action_t action
  )
{
  if( channel >= PROCESSOR_DMAC_NUM_CHANNELS )  return;
  
  CRITICAL_SECTION_ENTER();
  DMAC->CHID.reg = channel;
  DMAC->CHCTRLB.bit.EVACT = action;
  CRITICAL_SECTION_LEAVE();
}


void PROCESSOR_DMAC_CHANNEL_InterruptCallback_Set(
    processor_dmac_channel_t channel,
    processor_dmac_interrupt_callback_t callback
  )
{
  if( channel >= PROCESSOR_DMAC_NUM_CHANNELS )  return;
  
  _interrupt_callback[channel] = callback;
}

void PROCESSOR_DMAC_CHANNEL_Interrupt_Enable(
    processor_dmac_channel_t channel,
    processor_dmac_interrupt_t interrupt
  )
{
  if( channel >= PROCESSOR_DMAC_NUM_CHANNELS )  return;

  CRITICAL_SECTION_ENTER();
  DMAC->CHID.reg = channel;
  switch( interrupt )
  {
    case PROCESSOR_DMAC_INTERRUPT_SUSPEND:
      DMAC->CHINTENSET.reg = DMAC_CHINTENSET_SUSP;
      break;
    case PROCESSOR_DMAC_INTERRUPT_TRANSFER_DONE:
      DMAC->CHINTENSET.reg = DMAC_CHINTENSET_TCMPL;
      break;
    case PROCESSOR_DMAC_INTERRUPT_ERROR:
      DMAC->CHINTENSET.reg = DMAC_CHINTENSET_TERR;
      break;
    default:
      break;
  }
  CRITICAL_SECTION_LEAVE();
}

void PROCESSOR_DMAC_CHANNEL_Interrupt_Disable(
    processor_dmac_channel_t channel,
    processor_dmac_interrupt_t interrupt
  )
{
  if( channel >= PROCESSOR_DMAC_NUM_CHANNELS )  return;

  CRITICAL_SECTION_ENTER();
  DMAC->CHID.reg = channel;
  switch( interrupt )
  {
    case PROCESSOR_DMAC_INTERRUPT_SUSPEND:
      DMAC->CHINTENCLR.reg = DMAC_CHINTENCLR_SUSP;
      break;
    case PROCESSOR_DMAC_INTERRUPT_TRANSFER_DONE:
      DMAC->CHINTENCLR.reg = DMAC_CHINTENCLR_TCMPL;
      break;
    case PROCESSOR_DMAC_INTERRUPT_ERROR:
      DMAC->CHINTENCLR.reg = DMAC_CHINTENCLR_TERR;
      break;
    default:
      break;
  }
  CRITICAL_SECTION_LEAVE();
}

void PROCESSOR_DMAC_CHANNEL_InterruptFlag_Clear(
    processor_dmac_channel_t channel,
    processor_dmac_interrupt_t interrupt
  )
{
  if( channel >= PROCESSOR_DMAC_NUM_CHANNELS )  return;

  CRITICAL_SECTION_ENTER();
  DMAC->CHID.reg = channel;
  switch( interrupt )
  {
    case PROCESSOR_DMAC_INTERRUPT_SUSPEND:
      DMAC->CHINTFLAG.bit.SUSP = 1;
      break;
    case PROCESSOR_DMAC_INTERRUPT_TRANSFER_DONE:
      DMAC->CHINTFLAG.bit.TCMPL = 1;
      break;
    case PROCESSOR_DMAC_INTERRUPT_ERROR:
      DMAC->CHINTFLAG.bit.TERR = 1;
      break;
    default:
      break;
  }
  CRITICAL_SECTION_LEAVE();
}


bool PROCESSOR_DMAC_CHANNEL_isBusy(
    processor_dmac_channel_t channel
  )
{
  if( channel >= PROCESSOR_DMAC_NUM_CHANNELS )  return false;

  return (DMAC->BUSYCH.reg | (_U_(1) << channel)) != 0;
}

bool PROCESSOR_DMAC_CHANNEL_isPending(
    processor_dmac_channel_t channel
  )
{
  if( channel >= PROCESSOR_DMAC_NUM_CHANNELS )  return false;

  return (DMAC->PENDCH.reg | (_U_(1) << channel)) != 0;
}


processor_dmac_descriptor_t* PROCESSOR_DMAC_CHANNEL_Descriptor_Get( 
    processor_dmac_channel_t channel
  )
{
  if( channel >= PROCESSOR_DMAC_NUM_CHANNELS )  return NULL;

  return &_descriptor_section[channel];
}

processor_dmac_descriptor_t* PROCESSOR_DMAC_CHANNEL_Writeback_Get( 
    processor_dmac_channel_t channel
  )
{
  if( channel >= PROCESSOR_DMAC_NUM_CHANNELS )  return NULL;

  return &_write_back_section[channel];
}


void PROCESSOR_DMAC_DESCRIPTOR_SourceAddress_Set(
    processor_dmac_descriptor_t* descriptor,
    const void* address 
  )
{
  if( descriptor == NULL )  return;

  descriptor->SRCADDR.reg = (uint32_t)address;
}

void PROCESSOR_DMAC_DESCRIPTOR_DestinationAddress_Set(
    processor_dmac_descriptor_t* descriptor,
    const void* address
  )
{
  if( descriptor == NULL )  return;

  descriptor->DSTADDR.reg = (uint32_t)address;
}

void PROCESSOR_DMAC_DESCRIPTOR_SourceIncrement_Set(
    processor_dmac_descriptor_t* descriptor,
    bool enable
  )
{
  if( descriptor == NULL )  return;

  descriptor->BTCTRL.bit.SRCINC = (enable ? 1 : 0);
}

void PROCESSOR_DMAC_DESCRIPTOR_DestinationIncrement_Set(
    processor_dmac_descriptor_t* descriptor,
    bool enable
  )
{
  if( descriptor == NULL )  return;

  descriptor->BTCTRL.bit.DSTINC = (enable ? 1 : 0);
}

void PROCESSOR_DMAC_DESCRIPTOR_IncrementStepSize_Set( 
    processor_dmac_descriptor_t* descriptor,
    processor_dmac_step_selection_t selection,
    processor_dmac_addr_inc_step_size_t size
  )
{
  if( descriptor == NULL )  return;

  switch( selection )
  {
    case PROCESSOR_DMAC_STEP_SELECTION_DESTINATION:
    default:
      descriptor->BTCTRL.bit.STEPSEL = DMAC_BTCTRL_STEPSEL_DST_Val;
      break;

    case PROCESSOR_DMAC_STEP_SELECTION_SOURCE:
      descriptor->BTCTRL.bit.STEPSEL = DMAC_BTCTRL_STEPSEL_SRC_Val;
      break;
  }

  descriptor->BTCTRL.bit.STEPSIZE = size;
}

void PROCESSOR_DMAC_DESCRIPTOR_BeatSize_Set(
    processor_dmac_descriptor_t* descriptor,
    processor_dmac_beat_size_t size
  )
{
  if( descriptor == NULL )  return;

  descriptor->BTCTRL.bit.BEATSIZE = size;
}

void PROCESSOR_DMAC_DESCRIPTOR_BlockAction_Set(
    processor_dmac_descriptor_t* descriptor,
    processor_dmac_block_action_t action
  )
{
  if( descriptor == NULL )  return;

  descriptor->BTCTRL.bit.BLOCKACT = action;
}

void PROCESSOR_DMAC_DESCRIPTOR_EventOutput_Set(
    processor_dmac_descriptor_t* descriptor,
    processor_dmac_event_output_selection_t output
  )
{
  if( descriptor == NULL )  return;

  descriptor->BTCTRL.bit.EVOSEL = output;
}

void PROCESSOR_DMAC_DESCRIPTOR_BlockSize_Set(
    processor_dmac_descriptor_t* descriptor,
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

void PROCESSOR_DMAC_DESCRIPTOR_NextDescriptor_Set(
    processor_dmac_descriptor_t* descriptor,
    const processor_dmac_descriptor_t* next
  )
{
  if( descriptor == NULL )  return;

  descriptor->DESCADDR.reg = (uint32_t)next;
}


void DMAC_Handler(void)
{
  processor_dmac_channel_t channel;
  uint8_t enable;
  uint8_t flags;

  // Enter critical section to ensure that we have complete control of 
  //   CHID register while processing the interrupt flags.
  // Logic that checks the flags will limit processing to only one case
  //   for each pass through the dmac handler.
  CRITICAL_SECTION_ENTER();
    // Get ID of lowest channel with pending interrupt
    channel = DMAC->INTPEND.bit.ID;

    // Select the channel and make copy of the flags for processing.
    DMAC->CHID.reg = channel;
    enable = DMAC->CHINTENSET.reg;
    flags = DMAC->CHINTFLAG.reg;

    // Run through the interrupt flags and clear / keep only one flag to
    //   be processed after leaving critical section.
    if( (flags | DMAC_CHINTFLAG_TERR) && (enable | DMAC_CHINTENSET_TERR) )
    {
      flags = DMAC_CHINTFLAG_TERR;    // keep only one flag to be processed
      DMAC->CHINTFLAG.bit.TERR = 1;   // clear interrupt flag
    }
    else if( flags | DMAC_CHINTFLAG_TCMPL && (enable | DMAC_CHINTENSET_TCMPL) )
    {
      flags = DMAC_CHINTFLAG_TCMPL;   // keep only one flag to be processed
      DMAC->CHINTFLAG.bit.TCMPL = 1;  // clear interrupt flag
    }
    else if( flags | DMAC_CHINTFLAG_SUSP && (enable | DMAC_CHINTENSET_SUSP) )
    {
      flags = DMAC_CHINTFLAG_SUSP;    // keep only one flag to be processed
      DMAC->CHINTFLAG.bit.SUSP = 1;   // clear interrupt flag
    }
  CRITICAL_SECTION_LEAVE();

  if( _interrupt_callback[channel] != NULL )
  {
    if( flags | DMAC_CHINTFLAG_TERR )
    {
      _interrupt_callback[channel]( channel, PROCESSOR_DMAC_INTERRUPT_ERROR );
    }
    else if( flags | DMAC_CHINTFLAG_TCMPL )
    {
      _interrupt_callback[channel]( channel, PROCESSOR_DMAC_INTERRUPT_TRANSFER_DONE );
    }
    else if( flags | DMAC_CHINTFLAG_SUSP )
    {
      _interrupt_callback[channel]( channel, PROCESSOR_DMAC_INTERRUPT_SUSPEND );
    }
  }
}
