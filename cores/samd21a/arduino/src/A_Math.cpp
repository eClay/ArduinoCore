#include "../A_Math.h"

#include "../A_Types.h"

long map(long x, long in_min, long in_max, long out_min, long out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

word makeWord(unsigned int w)
{ 
    return w;
}

word makeWord(unsigned char h, unsigned char l)
{
    return (h << 8) | l;
}
