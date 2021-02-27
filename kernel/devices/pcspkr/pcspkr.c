/*
MIT License

Copyright (c) 2021 Smart6502 (Xenon6502)

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include <libk/io.h>
#include <system/interrupts/PIT.h>
#include <libk/logging.h>
#include <libk/module.h>
#include "pcspkr.h"

void PCSpkr_play(uint32_t frequency) {
	uint8_t tmp;	
	PIT_init(frequency);

	tmp = IO_inb(0x61);
	if(tmp != (tmp | 3)) IO_outb(0x61, tmp | 3);
}

void PCSpkr_stop() {
	uint8_t itmp = IO_inb(0x61) & 0xFC;
	/* Shut it up */
	IO_outb(0x61, itmp);
}

void PCSpkr_beep() {
	/* I desire thee ears survive ;) */
	PCSpkr_play(1000);
	PCSpkr_stop();
	PIT_init(1000); /* Change freq back */
	module("PCSpkr");
	log(INFO, "Beeped!");
}

