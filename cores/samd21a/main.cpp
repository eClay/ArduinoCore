#include "Arduino.h"

#include "usb/USBAPI.h"
extern USBDeviceClass USBDevice;


// Weak empty variant initialization function.
// May be redefined by variant files.
void initVariant() __attribute__((weak));
void initVariant() { }

void setupUSB() __attribute__((weak));
void setupUSB() { }

extern "C"{
void SystemInit(void);
void SystemInit2(void);
void boardInit(void);
}
void initVariant(void);

void setup(void);
void loop(void);

int main(void)
{
    SystemInit();
    SystemInit2();
	boardInit();

	initVariant();

#if defined(USBCON)
  USBDevice.init();
  USBDevice.attach();
#endif
	
	setup();
    
	for (;;) {
		loop();
//		if (serialEventRun) serialEventRun();
	}
        
	return 0;
}

