#ifndef CORE_INTERRUPT_H
#define CORE_INTERRUPT_H

#define CORE_INTERRUPT_global_enable()    __enable_irq()
#define CORE_INTERRUPT_global_disable()   __disable_irq()

#endif  // CORE_INTERRUPT_H
