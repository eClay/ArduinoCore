#ifndef ARDUINO_MATH_H
#define ARDUINO_MATH_H

#include <math.h>
#include <stdint.h>

#include "A_Types.h"

#define PI          3.1415926535897932384626433832795
#define HALF_PI     1.5707963267948966192313216916398
#define TWO_PI      6.283185307179586476925286766559

#define EPSILON                        (0.0001)

#define DEG_TO_RAD  0.017453292519943295769236907684886
#define RAD_TO_DEG  57.295779513082320876798154814105

#define EULER       2.718281828459045235360287471352

// undefine stdlib's abs if encountered
#ifdef abs
#undef abs
#endif
#define abs(x) ((x)>0?(x):-(x))

#ifndef constrain
#define constrain(amt,low,high) ((amt)<(low)?(low):((amt)>(high)?(high):(amt)))
#endif

long map(long x, long in_min, long in_max, long out_min, long out_max);

#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))

#ifndef min
#define min(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a < _b ? _a : _b; })
#endif

#ifndef max
#define max(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a > _b ? _a : _b; })
#endif

#define round(x)     ((x)>=0?(long)((x)+0.5):(long)((x)-0.5))

#ifndef radians
#define radians(deg) ((deg)*DEG_TO_RAD)
#endif

#ifndef degrees
#define degrees(rad) ((rad)*RAD_TO_DEG)
#endif

#ifndef sq
#define sq(x) ((x)*(x))
#endif

#define lowByte(x)  ((uint8_t)((x) & 0xff))
#define highByte(x) ((uint8_t)((x) >> 8))

#define bitRead(value, bit) (((value) >> (bit)) & 0x01)
#define bitSet(value, bit) ((value) |= (1UL << (bit)))
#define bitClear(value, bit) ((value) &= ~(1UL << (bit)))
#define bitWrite(value, bit, bitvalue) (bitvalue ? bitSet(value, bit) : bitClear(value, bit))

#ifndef bit
#define bit(b) (1UL << (b))
#endif

#ifdef __cplusplus

word makeWord(uint16_t w);
word makeWord(byte h, byte l);

#define word(...) makeWord(__VA_ARGS__)

#endif  // __cplusplus

#endif  // ARDUINO_MATH_H
