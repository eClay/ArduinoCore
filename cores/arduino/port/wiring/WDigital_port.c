#include "WDigital.h"

#include "sam.h"

#include "WTypes.h"


#ifdef __cplusplus
 extern "C" {
#endif

typedef struct _PinDescription
{
  uint8_t      ulPortGroup ;
  uint8_t         ulPortPin ;
  uint8_t       ulPinType;
} PinDescription ;

PinDescription g_APinDescription[] =
{
    {0, 16, 1},
    {0, 17, 1},
};

#define PIO_NOT_A_PIN  0

void pinMode(uint8_t pin, uint8_t mode)
{
  // Handle the case the pin isn't usable as PIO
  if ( g_APinDescription[pin].ulPinType == PIO_NOT_A_PIN )
  {
    return ;
  }

  // Set pin mode according to chapter '22.6.3 I/O Pin Configuration'
  switch ( mode )
  {
    case INPUT:
      // Set pin to input mode
      PORT->Group[g_APinDescription[pin].ulPortGroup].PINCFG[g_APinDescription[pin].ulPortPin].reg=(uint8_t)(PORT_PINCFG_INEN) ;
      PORT->Group[g_APinDescription[pin].ulPortGroup].DIRCLR.reg = (uint32_t)(1<<g_APinDescription[pin].ulPortPin) ;
    break ;

    case INPUT_PULLUP:
      // Set pin to input mode with pull-up resistor enabled
      PORT->Group[g_APinDescription[pin].ulPortGroup].PINCFG[g_APinDescription[pin].ulPortPin].reg=(uint8_t)(PORT_PINCFG_INEN|PORT_PINCFG_PULLEN) ;
      PORT->Group[g_APinDescription[pin].ulPortGroup].DIRCLR.reg = (uint32_t)(1<<g_APinDescription[pin].ulPortPin) ;

      // Enable pull level (cf '22.6.3.2 Input Configuration' and '22.8.7 Data Output Value Set')
      PORT->Group[g_APinDescription[pin].ulPortGroup].OUTSET.reg = (uint32_t)(1<<g_APinDescription[pin].ulPortPin) ;
    break ;

    case INPUT_PULLDOWN:
      // Set pin to input mode with pull-down resistor enabled
      PORT->Group[g_APinDescription[pin].ulPortGroup].PINCFG[g_APinDescription[pin].ulPortPin].reg=(uint8_t)(PORT_PINCFG_INEN|PORT_PINCFG_PULLEN) ;
      PORT->Group[g_APinDescription[pin].ulPortGroup].DIRCLR.reg = (uint32_t)(1<<g_APinDescription[pin].ulPortPin) ;

      // Enable pull level (cf '22.6.3.2 Input Configuration' and '22.8.6 Data Output Value Clear')
      PORT->Group[g_APinDescription[pin].ulPortGroup].OUTCLR.reg = (uint32_t)(1<<g_APinDescription[pin].ulPortPin) ;
    break ;

    case OUTPUT:
      // enable input, to support reading back values, with pullups disabled
      PORT->Group[g_APinDescription[pin].ulPortGroup].PINCFG[g_APinDescription[pin].ulPortPin].reg=(uint8_t)(PORT_PINCFG_INEN) ;

      // Set pin to output mode
      PORT->Group[g_APinDescription[pin].ulPortGroup].DIRSET.reg = (uint32_t)(1<<g_APinDescription[pin].ulPortPin) ;
    break ;

    default:
      // do nothing
    break ;
  }
}

void digitalWrite(uint8_t pin, uint8_t value)
{
  // Handle the case the pin isn't usable as PIO
  if ( g_APinDescription[pin].ulPinType == PIO_NOT_A_PIN )
  {
    return ;
  }

  uint8_t port = g_APinDescription[pin].ulPortGroup;
  uint8_t portPin = g_APinDescription[pin].ulPortPin;
  uint32_t pinMask = (1ul << portPin);

  if ( (PORT->Group[port].DIRSET.reg & pinMask) == 0 ) {
    // the pin is not an output, disable pull-up if val is LOW, otherwise enable pull-up
    PORT->Group[port].PINCFG[portPin].bit.PULLEN = ((value == LOW) ? 0 : 1) ;
  }

  switch ( value )
  {
    case LOW:
      PORT->Group[port].OUTCLR.reg = pinMask;
    break ;

    default:
      PORT->Group[port].OUTSET.reg = pinMask;
    break ;
  }

  return ;
}

int digitalRead(uint8_t pin)
{
  // Handle the case the pin isn't usable as PIO
  if ( g_APinDescription[pin].ulPinType == PIO_NOT_A_PIN )
  {
    return LOW ;
  }

  if ( (PORT->Group[g_APinDescription[pin].ulPortGroup].IN.reg & (1ul << g_APinDescription[pin].ulPortPin)) != 0 )
  {
    return HIGH ;
  }

  return LOW ;
}

#ifdef __cplusplus
}
#endif

