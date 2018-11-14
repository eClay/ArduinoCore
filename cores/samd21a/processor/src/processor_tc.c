#include "processor/tc.h"


void PROCESSOR_TC_InitializeAll( void )
{
  for( processor_tc_instance_t timer = 0; timer < NUM_PROCESSOR_TC_INSTANCES; timer++ )
  {
    PROCESSOR_TC_SoftwareReset( timer );
  }
}


static inline void PROCESSOR_TC_EVENT_Output_Enable(
    processor_tc_instance_t      timer,
    processor_tc_event_output_t  event
  )
{

}

static inline void PROCESSOR_TC_EVENT_Output_Disable(
    processor_tc_instance_t      timer,
    processor_tc_event_output_t  event
  )
{

}

static inline void PROCESSOR_TC_EVENT_CountMode_Set(
    processor_tc_instance_t          timer,
    processor_tc_event_count_mode_t  mode
  )
{

}


static inline void PROCESSOR_TC_EVENT_Input_Enable(
    processor_tc_instance_t      timer,
    processor_tc_event_input_t   event
  )
{

}

static inline void PROCESSOR_TC_EVENT_Input_Disable(
    processor_tc_instance_t      timer,
    processor_tc_event_input_t   event
  )
{

}

static inline void PROCESSOR_TC_EVENT_InputAction_Set(
    processor_tc_instance_t            timer,
    processor_tc_event_input_action_t action
  )
{

}


