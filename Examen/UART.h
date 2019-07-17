#ifndef UART_H
#define UART_H

#include <avr/io.h>
#include <avr/interrupt.h>
#include <inttypes.h>

#define BLACK 30
#define RED 31
#define GREEN 32
#define YELLOW 33
#define BLUE 34
#define PURPLE 35
#define CYAN 36
#define WHITE 37

#define BUFFER_SIZE 64
#define MOD(idx) (idx)&(BUFFER_SIZE -1)
#define BUFFER_EMPTY(buffer) buffer.in_idx == buffer.out_idx
#define BUFFER_FULL(buffer) buffer.in_idx == (MOD(buffer.out_idx-1))
#define MYUBRR(BAUD) (16000000/8/BAUD-1)

typedef struct {
	char buffer[BUFFER_SIZE]; /* espacio reservado */
	volatile unsigned char in_idx:6;  /* indice entrada (Head) con 6 bits su valor maximo es 63*/
	volatile unsigned char out_idx:6; /* indice entrada (tail) con 6 bits su valor maximo es 63*/
}ring_buffer_t;

void UART0_Init(uint8_t, uint32_t, uint8_t, uint8_t, uint8_t);
unsigned char UART0_available( void );
void UART0_putchar(char);
char UART0_getchar(void);
void inicializarColas(); 				//EN ESTA FUNCION SE ACTIVAN LAS INTERRUPCIONES GLOBALES
void UART0_puts(char *);
void UART0_gets(char *);
uint8_t UART0_AutoBaudRate(void);
void itoa(char* str, uint16_t number,const uint8_t base);
uint16_t atoi(const char *str);
void clrscr(void);
void setColor(uint8_t color);
void gotoxy(uint8_t x, uint8_t y);
void delay(uint16_t mseg);


#endif
