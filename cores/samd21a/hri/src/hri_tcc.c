#include "hri/tcc.h"


void HRI_TCC_InitializeAll( void )
{
  for( hri_tcc_instance_t timer = 0; timer < NUM_HRI_TCC_INSTANCES; timer++ )
  {
    HRI_TCC_SoftwareReset( timer );
  }
}
