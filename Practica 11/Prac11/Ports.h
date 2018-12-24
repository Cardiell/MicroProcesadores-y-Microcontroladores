#ifndef _PORTS_H
#define _PORTS_H

#include <avr/io.h>
// Macros
#define SetBitPort(port, bit) asm ("sbi %0, %1"::"I"(_SFR_IO_ADDR(port)),"I" (bit))
#define ClrBitPort(port, bit) asm ("cbi %0, %1"::"I"(_SFR_IO_ADDR(port)),"I" (bit))

// Press States
#define UNDEFINED 0
#define SHORT_PRESSED 1
#define LONG_PRESSED 2

// Event btn
#define BNT_NEXT 3
#define BNT_PREV 4




void InitPorts(void);
uint8_t checkBtn(void);
uint8_t checkPress(uint8_t PD);

#endif
