#ifndef WIRING_STRING_PORT_H
#define WIRING_STRING_PORT_H

#include <stdlib.h>

#define ltoa    itoa
#define ultoa   utoa

#ifdef __cplusplus
extern "C" {
#endif

char *dtostrf(double val, signed char width, unsigned char prec, char *sout);

#ifdef __cplusplus
}
#endif

#endif