#ifndef WIRING_TYPES_H
#define WIRING_TYPES_H

#include <stdbool.h>
#include <stdint.h>

#ifndef boolean
typedef bool boolean;
#endif

#ifndef byte
typedef uint8_t byte;
#endif

#ifndef word
typedef uint16_t word;
#endif

typedef bool pinstate_t;
#define LOW     false
#define HIGH    true

typedef enum pinmode
{
    INPUT = 0,
    OUTPUT,
    INPUT_PULLUP,
    INPUT_PULLDOWN,

    NUM_PINMODES,
    PINMODE_INVALID = NUM_PINMODES
} pinmode_t;

typedef enum intedge
{    
    CHANGE = 1,
    FALLING = 2,
    RISING = 3
} intedge_t;

typedef enum bitorder
{
    LSBFIRST = 0,
    MSBFIRST = 1
} bitorder_t;

#define DEC      10
#define HEX      16
#define OCT      8
#define BIN      2
#define BYTE     0

#endif
