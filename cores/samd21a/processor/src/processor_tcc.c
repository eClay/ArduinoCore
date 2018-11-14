#include "processor/tcc.h"


void PROCESSOR_TCC_InitializeAll( void )
{
  for( processor_tcc_instance_t timer = 0; timer < NUM_PROCESSOR_TCC_INSTANCES; timer++ )
  {
    PROCESSOR_TCC_SoftwareReset( timer );
  }
}
