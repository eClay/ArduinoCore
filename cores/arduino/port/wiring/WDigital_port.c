#include "api/WDigital.h"

#include "sam.h"

#include "api/WTypes.h"


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

void pinMode(pin_size_t pinNumber, PinMode pinMode)
{
  // Handle the case the pin isn't usable as PIO
  if ( g_APinDescription[pinNumber].ulPinType == PIO_NOT_A_PIN )
  {
    return ;
  }

  // Set pin mode according to chapter '22.6.3 I/O Pin Configuration'
  switch ( pinMode )
  {
    case INPUT:
      // Set pin to input mode
      PORT->Group[g_APinDescription[pinNumber].ulPortGroup].PINCFG[g_APinDescription[pinNumber].ulPortPin].reg=(uint8_t)(PORT_PINCFG_INEN) ;
      PORT->Group[g_APinDescription[pinNumber].ulPortGroup].DIRCLR.reg = (uint32_t)(1<<g_APinDescription[pinNumber].ulPortPin) ;
    break ;

    case INPUT_PULLUP:
      // Set pin to input mode with pull-up resistor enabled
      PORT->Group[g_APinDescription[pinNumber].ulPortGroup].PINCFG[g_APinDescription[pinNumber].ulPortPin].reg=(uint8_t)(PORT_PINCFG_INEN|PORT_PINCFG_PULLEN) ;
      PORT->Group[g_APinDescription[pinNumber].ulPortGroup].DIRCLR.reg = (uint32_t)(1<<g_APinDescription[pinNumber].ulPortPin) ;

      // Enable pull level (cf '22.6.3.2 Input Configuration' and '22.8.7 Data Output Value Set')
      PORT->Group[g_APinDescription[pinNumber].ulPortGroup].OUTSET.reg = (uint32_t)(1<<g_APinDescription[pinNumber].ulPortPin) ;
    break ;

    case INPUT_PULLDOWN:
      // Set pin to input mode with pull-down resistor enabled
      PORT->Group[g_APinDescription[pinNumber].ulPortGroup].PINCFG[g_APinDescription[pinNumber].ulPortPin].reg=(uint8_t)(PORT_PINCFG_INEN|PORT_PINCFG_PULLEN) ;
      PORT->Group[g_APinDescription[pinNumber].ulPortGroup].DIRCLR.reg = (uint32_t)(1<<g_APinDescription[pinNumber].ulPortPin) ;

      // Enable pull level (cf '22.6.3.2 Input Configuration' and '22.8.6 Data Output Value Clear')
      PORT->Group[g_APinDescription[pinNumber].ulPortGroup].OUTCLR.reg = (uint32_t)(1<<g_APinDescription[pinNumber].ulPortPin) ;
    break ;

    case OUTPUT:
      // enable input, to support reading back values, with pullups disabled
      PORT->Group[g_APinDescription[pinNumber].ulPortGroup].PINCFG[g_APinDescription[pinNumber].ulPortPin].reg=(uint8_t)(PORT_PINCFG_INEN) ;

      // Set pin to output mode
      PORT->Group[g_APinDescription[pinNumber].ulPortGroup].DIRSET.reg = (uint32_t)(1<<g_APinDescription[pinNumber].ulPortPin) ;
    break ;

    default:
      // do nothing
    break ;
  }
}

void digitalWrite(pin_size_t pinNumber, PinStatus status)
{
  // Handle the case the pin isn't usable as PIO
  if ( g_APinDescription[pinNumber].ulPinType == PIO_NOT_A_PIN )
  {
    return ;
  }

  uint8_t port = g_APinDescription[pinNumber].ulPortGroup;
  uint8_t portPin = g_APinDescription[pinNumber].ulPortPin;
  uint32_t pinMask = (1ul << portPin);

  if ( (PORT->Group[port].DIRSET.reg & pinMask) == 0 ) {
    // the pin is not an output, disable pull-up if val is LOW, otherwise enable pull-up
    PORT->Group[port].PINCFG[portPin].bit.PULLEN = ((status == LOW) ? 0 : 1) ;
  }

  switch ( status )
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

PinStatus digitalRead(pin_size_t pinNumber)
{
  // Handle the case the pin isn't usable as PIO
  if ( g_APinDescription[pinNumber].ulPinType == PIO_NOT_A_PIN )
  {
    return LOW ;
  }

  if ( (PORT->Group[g_APinDescription[pinNumber].ulPortGroup].IN.reg & (1ul << g_APinDescription[pinNumber].ulPortPin)) != 0 )
  {
    return HIGH ;
  }

  return LOW ;
}

#ifdef __cplusplus
}
#endif

