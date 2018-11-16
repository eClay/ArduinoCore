#include "hri/tc.h"

#include <stddef.h>


void HRI_TC_Initialize( void )
{
  for( hri_tc_instance_t timer = 0; timer < HRI_TC_NUM_INSTANCES; timer++ )
  {
    HRI_TC_SoftwareReset( timer );
  }
}
