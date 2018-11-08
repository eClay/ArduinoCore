#ifndef CORE_DIGITAL_H
#define CORE_DIGITAL_H

#include "sam.h"

#ifdef __cplusplus
extern "C" {
#endif

void digitalWrite_variable(pin_size_t pinNumber, PinStatus status);
void digitalWrite_low(pin_size_t pinNumber);
void digitalWrite_high(pin_size_t pinNumber);

static inline void digitalWrite(pin_size_t pinNumber, PinStatus status) __attribute__((always_inline, unused));
static inline void digitalWrite(pin_size_t pinNumber, PinStatus status)
{
  if( __builtin_constant_p(pinNumber) )
  {
    if(status == LOW)
    {
      switch( pinNumber )
      {
        case 1:
          REG_PORT_OUTCLR0 = PORT_PA00;  break;
        case 2:
          REG_PORT_OUTCLR0 = PORT_PA01;  break;
        case 3:
          REG_PORT_OUTCLR0 = PORT_PA02;  break;
        case 4:
          REG_PORT_OUTCLR0 = PORT_PA03;  break;
        case 7:
          REG_PORT_OUTCLR1 = PORT_PB08;  break;
        case 8:
          REG_PORT_OUTCLR1 = PORT_PB09;  break;
        case 9:
          REG_PORT_OUTCLR0 = PORT_PA04;  break;
        case 10:
          REG_PORT_OUTCLR0 = PORT_PA05;  break;
        case 11:
          REG_PORT_OUTCLR0 = PORT_PA06;  break;
        case 12:
          REG_PORT_OUTCLR0 = PORT_PA07;  break;
        case 13:
          REG_PORT_OUTCLR0 = PORT_PA08;  break;
        case 14:
          REG_PORT_OUTCLR0 = PORT_PA09;  break;
        case 15:
          REG_PORT_OUTCLR0 = PORT_PA10;  break;
        case 16:
          REG_PORT_OUTCLR0 = PORT_PA11;  break;
        case 19:
          REG_PORT_OUTCLR1 = PORT_PB10;  break;
        case 20:
          REG_PORT_OUTCLR1 = PORT_PB11;  break;
        case 21:
          REG_PORT_OUTCLR0 = PORT_PA12;  break;
        case 22:
          REG_PORT_OUTCLR0 = PORT_PA13;  break;
        case 23:
          REG_PORT_OUTCLR0 = PORT_PA14;  break;
        case 24:
          REG_PORT_OUTCLR0 = PORT_PA15;  break;
        case 25:
          REG_PORT_OUTCLR0 = PORT_PA16;  break;
        case 26:
          REG_PORT_OUTCLR0 = PORT_PA17;  break;
        case 27:
          REG_PORT_OUTCLR0 = PORT_PA18;  break;
        case 28:
          REG_PORT_OUTCLR0 = PORT_PA19;  break;
        case 29:
          REG_PORT_OUTCLR0 = PORT_PA20;  break;
        case 30:
          REG_PORT_OUTCLR0 = PORT_PA21;  break;
        case 31:
          REG_PORT_OUTCLR0 = PORT_PA22;  break;
        case 32:
          REG_PORT_OUTCLR0 = PORT_PA23;  break;
        case 33:
          REG_PORT_OUTCLR0 = PORT_PA24;  break;
        case 34:
          REG_PORT_OUTCLR0 = PORT_PA25;  break;
        case 37:
          REG_PORT_OUTCLR1 = PORT_PB22;  break;
        case 38:
          REG_PORT_OUTCLR1 = PORT_PB23;  break;
        case 39:
          REG_PORT_OUTCLR0 = PORT_PA27;  break;
        case 41:
          REG_PORT_OUTCLR0 = PORT_PA28;  break;
        case 45:
          REG_PORT_OUTCLR0 = PORT_PA30;  break;
        case 46:
          REG_PORT_OUTCLR0 = PORT_PA31;  break;
        case 47:
          REG_PORT_OUTCLR1 = PORT_PB02;  break;
        case 48:
          REG_PORT_OUTCLR1 = PORT_PB03;  break;
        default:
          break;
      }
    }
    else if( status == HIGH )
    {
      switch( pinNumber )
      {
        case 1:
          REG_PORT_OUTSET0 = PORT_PA00;  break;
        case 2:
          REG_PORT_OUTSET0 = PORT_PA01;  break;
        case 3:
          REG_PORT_OUTSET0 = PORT_PA02;  break;
        case 4:
          REG_PORT_OUTSET0 = PORT_PA03;  break;
        case 7:
          REG_PORT_OUTSET1 = PORT_PB08;  break;
        case 8:
          REG_PORT_OUTSET1 = PORT_PB09;  break;
        case 9:
          REG_PORT_OUTSET0 = PORT_PA04;  break;
        case 10:
          REG_PORT_OUTSET0 = PORT_PA05;  break;
        case 11:
          REG_PORT_OUTSET0 = PORT_PA06;  break;
        case 12:
          REG_PORT_OUTSET0 = PORT_PA07;  break;
        case 13:
          REG_PORT_OUTSET0 = PORT_PA08;  break;
        case 14:
          REG_PORT_OUTSET0 = PORT_PA09;  break;
        case 15:
          REG_PORT_OUTSET0 = PORT_PA10;  break;
        case 16:
          REG_PORT_OUTSET0 = PORT_PA11;  break;
        case 19:
          REG_PORT_OUTSET1 = PORT_PB10;  break;
        case 20:
          REG_PORT_OUTSET1 = PORT_PB11;  break;
        case 21:
          REG_PORT_OUTSET0 = PORT_PA12;  break;
        case 22:
          REG_PORT_OUTSET0 = PORT_PA13;  break;
        case 23:
          REG_PORT_OUTSET0 = PORT_PA14;  break;
        case 24:
          REG_PORT_OUTSET0 = PORT_PA15;  break;
        case 25:
          REG_PORT_OUTSET0 = PORT_PA16;  break;
        case 26:
          REG_PORT_OUTSET0 = PORT_PA17;  break;
        case 27:
          REG_PORT_OUTSET0 = PORT_PA18;  break;
        case 28:
          REG_PORT_OUTSET0 = PORT_PA19;  break;
        case 29:
          REG_PORT_OUTSET0 = PORT_PA20;  break;
        case 30:
          REG_PORT_OUTSET0 = PORT_PA21;  break;
        case 31:
          REG_PORT_OUTSET0 = PORT_PA22;  break;
        case 32:
          REG_PORT_OUTSET0 = PORT_PA23;  break;
        case 33:
          REG_PORT_OUTSET0 = PORT_PA24;  break;
        case 34:
          REG_PORT_OUTSET0 = PORT_PA25;  break;
        case 37:
          REG_PORT_OUTSET1 = PORT_PB22;  break;
        case 38:
          REG_PORT_OUTSET1 = PORT_PB23;  break;
        case 39:
          REG_PORT_OUTSET0 = PORT_PA27;  break;
        case 41:
          REG_PORT_OUTSET0 = PORT_PA28;  break;
        case 45:
          REG_PORT_OUTSET0 = PORT_PA30;  break;
        case 46:
          REG_PORT_OUTSET0 = PORT_PA31;  break;
        case 47:
          REG_PORT_OUTSET1 = PORT_PB02;  break;
        case 48:
          REG_PORT_OUTSET1 = PORT_PB03;  break;
        default:
          break;
      }
    }
  }
  else if( __builtin_constant_p(status) )
  {
    if( status == LOW )
    {
      digitalWrite_low(pinNumber);
    }
    else if( status == HIGH )
    {
      digitalWrite_high(pinNumber);
    }
    else
    {
      digitalWrite_variable( pinNumber, status );
    }
  }
  else
  {
    digitalWrite_variable(pinNumber, status);
  }
}

#ifdef __cplusplus
}
#endif

#endif  // CORE_DIGITAL_H
