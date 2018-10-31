#ifndef WIRING_DELAY_H
#define WIRING_DELAY_H

#ifdef __cplusplus
extern "C"{
#endif

void delay(unsigned long ms);
void delayMicroseconds(unsigned int us);

#ifdef __cplusplus
} // extern "C"
#endif

#endif