#ifndef UART_H_
#define UART_H_
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
#define MOD(idx) ((idx)&(BUFFER_SIZE -1))
#define BUFFER_EMPTY(buffer) (buffer.in_idx == buffer.out_idx)
#define BUFFER_FULL(buffer) (buffer.in_idx == (MOD(buffer.out_idx-1)))
#define UART_DisableTransmitIT() (UCSR0B&=(~(1<<UDRIE0)))
#define UART_EnableTransmitIT() (UCSR0B |= (1<<UDRIE0))
#define MYUBRR(BAUD) (16000000/16/BAUD-1)

typedef struct{
    char buffer[BUFFER_SIZE]; /* espacio reservado */
    volatile unsigned char in_idx; /* indice entrada (Head) */
    volatile unsigned char out_idx; /* indice entrada (tail) */
}ring_buffer_t;

void Buffer_ini( void );
void UART_Ini(uint8_t com, uint16_t baudrate, uint8_t size,uint8_t parity, uint8_t stop);
uint8_t UART0_available( void );
void UART0_putchar(char data);
char UART0_getchar(void);
void UART0_puts(char *str);
void UART0_gets(char *str);
void itoa(char* str, uint16_t number,const uint8_t base);
uint16_t atoi(const char *str);
void clrscr(void);
void setColor(uint8_t color);
void gotoxy(uint8_t x, uint8_t y);




#endif
