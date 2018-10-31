#include "WMath.h"

#include "WTypes.h"

long map(long value, long fromLow, long fromHigh, long toLow, long toHigh)
{
  return (value - fromLow) * (toHigh - toLow) / (fromHigh - fromLow) + toLow;
}

word makeWord(unsigned int w)
{ 
    return w;
}

word makeWord(unsigned char h, unsigned char l)
{
    return (h << 8) | l;
}
