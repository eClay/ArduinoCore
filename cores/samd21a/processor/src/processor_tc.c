#include "processor/tc.h"


void PROCESSOR_TC_InitializeAll( void )
{
  for( processor_tc_instance_t timer = 0; timer < NUM_PROCESSOR_TC_INSTANCES; timer++ )
  {
    PROCESSOR_TC_SoftwareReset( timer );
  }
}
