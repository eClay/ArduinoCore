#ifndef ARDUINO_RANDOM_H
#define ARDUINO_RANDOM_H

#ifdef __cplusplus

long random(long max);
long random(long min, long max);

void randomSeed(unsigned long seed);

#endif  // __cplusplus

#endif  // ARDUINO_RANDOM_H
