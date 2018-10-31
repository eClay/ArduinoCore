#ifndef WTIME_H
#define WTIME_H

#define clockCyclesPerMicrosecond() ( F_CPU / 1000000L )
#define clockCyclesToMicroseconds(a) ( (a) / clockCyclesPerMicrosecond() )
#define microsecondsToClockCycles(a) ( (a) * clockCyclesPerMicrosecond() )

#ifdef __cplusplus
extern "C"{
#endif

unsigned long millis(void);
unsigned long micros(void);

#ifdef __cplusplus
} // extern "C"
#endif

#endif