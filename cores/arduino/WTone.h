#ifndef WTONE_H
#define WTONE_H

#ifdef __cplusplus

#include <stdint.h>

void tone(uint8_t pin, unsigned int frequency, unsigned long duration = 0);
void noTone(uint8_t pin);

#endif

#endif