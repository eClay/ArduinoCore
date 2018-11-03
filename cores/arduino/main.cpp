/*
  main.cpp - Main loop for Arduino sketches
  Copyright (c) 2005-2013 Arduino Team.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

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

