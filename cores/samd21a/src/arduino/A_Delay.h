#ifndef ARDUINO_DELAY_H
#define ARDUINO_DELAY_H

#ifdef __cplusplus
extern "C"{
#endif

void delay(unsigned long ms);
void delayMicroseconds(unsigned int us);

#ifdef __cplusplus
} // extern "C"
#endif

#endif  // ARDUINO_DELAY_H
