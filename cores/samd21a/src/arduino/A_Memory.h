#ifndef ARDUINO_MEMORY_H
#define ARDUINO_MEMORY_H

#ifdef __cplusplus

#include <stddef.h>

void *operator new(size_t size);
void operator delete(void *ptr);
void *operator new[](size_t size);
void operator delete[](void *ptr);

#endif  // __cplusplus

#endif  // ARDUINO_MEMORY_H
