#ifndef WIRING_MATH_H
#define WIRING_MATH_H

#include <math.h>
#include "WTypes.h"

#define PI                             (3.1415926535897932384626433832795)
#define TWO_PI                         (6.283185307179586476925286766559)
#define HALF_PI                        (1.5707963267948966192313216916398)

#define EPSILON                        (0.0001)

#define DEG_TO_RAD  (0.017453292519943295769236907684886)
#define RAD_TO_DEG  (57.295779513082320876798154814105)

// undefine stdlib's abs if encountered
#ifdef abs
#undef abs
#endif
#define abs(x) ((x)>0?(x):-(x))

#define constrain(x,a,b) ((x)<(a)?(a):((x)>(b)?(b):(x)))

long map(long value, long fromLow, long fromHigh, long toLow, long toHigh);

#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))

#define round(x)     ((x)>=0?(long)((x)+0.5):(long)((x)-0.5))

#define radians(deg) ((deg)*DEG_TO_RAD)
#define degrees(rad) ((rad)*RAD_TO_DEG)

#define sq(x) ((x)*(x))

#define lowByte(x)  ((byte)((x) & 0xff))
#define highByte(x) ((byte)((x) >> 8))

#define bitRead(value, bit) (((value) >> (bit)) & 0x01)
#define bitSet(value, bit) ((value) |= (1UL << (bit)))
#define bitClear(value, bit) ((value) &= ~(1UL << (bit)))
#define bitWrite(value, bit, bitvalue) (bitvalue ? bitSet(value, bit) : bitClear(value, bit))

#define bit(b) (1UL << (b))

#ifdef __cplusplus
word makeWord(uint16_t w);
word makeWord(byte h, byte l);
#define word(...) makeWord(__VA_ARGS__)
#endif

#endif
