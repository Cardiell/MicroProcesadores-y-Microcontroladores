#ifndef _UART_H
#define _UART_H

#include<avr/io.h>

void Buffer_ini( void );
void UART_ini(uint8_t com, uint16_t baudrate, uint8_t size,uint8_t parity, uint8_t stop);
void UART0_putchar(char data);
void UART0_puts(char *str);
char UART0_getchar(void);
void UART0_gets(char *str);
uint8_t UART0_available( void );
uint16_t atoi(char *str);
void itoa(char* str,uint16_t num,uint8_t base);
void clrscr( void );
void gotoxy(uint8_t,uint8_t);
void UART0_AutoBaudRate();

#endif
