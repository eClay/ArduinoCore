
#ifndef CORE_SYNC_H
#define CORE_SYNC_H

#include "processor/sam.h"

#include <stdint.h>

class __Guard {
public:
	__Guard() : primask(__get_PRIMASK()), loops(1) {
		__disable_irq();
	}
	~__Guard() {
		if (primask == 0) {
			__enable_irq();
			// http://infocenter.arm.com/help/topic/com.arm.doc.dai0321a/BIHBFEIB.html
			__ISB();
		}
	}
	uint32_t enter() { return loops--; }
private:
	uint32_t primask;
	uint32_t loops;
};

#define synchronized for (__Guard __guard; __guard.enter(); )

#endif  // CORE_SYNC_H
