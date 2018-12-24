#include "UART.h"

#include<avr/interrupt.h>
#include <inttypes.h>

#define BUFFER_SIZE 64
#define MOD(idx) (idx)&(BUFFER_SIZE -1)
#define BUFFER_EMPTY(buffer) buffer.in_idx == buffer.out_idx
#define BUFFER_FULL(buffer) buffer.in_idx == (MOD(buffer.out_idx-1))

typedef struct{
    char buffer[BUFFER_SIZE]; /* espacio reservado */
    volatile unsigned char in_idx:6; /* indice entrada (Head) */
    volatile unsigned char out_idx:6; /* indice entrada (tail) */
}ring_buffer_t;

ring_buffer_t cola_rx; 
ring_buffer_t cola_tx;

void Buffer_ini( void )
{
    cola_rx.in_idx  = 0;
    cola_rx.out_idx = 0;
	cola_tx.in_idx  = 0;
    cola_tx.out_idx = 0;
}

void UART_ini(uint8_t com, uint16_t baudrate, uint8_t size,uint8_t parity, uint8_t stop)
{
  uint32_t *UBRRn;
  uint16_t *UCSRnA, *UCSRnB, *UCSRnC;  
Buffer_ini();
  if(com != 3){
      UBRRn  = (unsigned long int *)0xC4 +(8*com);//c5
	  UCSRnA = (unsigned int *)0xC0 +(8*com);
	  UCSRnB = (unsigned int *)0xC1 +(8*com);
	  UCSRnC = (unsigned int *)0xC2 +(8*com);
  }else{
      UBRRn  = (unsigned long int *)0x134;//135
	  UCSRnA = (unsigned int *)0x130;
	  UCSRnB = (unsigned int *)0x131;
	  UCSRnC = (unsigned int *)0x132;
  }

  if(parity==1) parity=3;

  //*UBRRn  = (16000000/(8*baudrate))-1;
  *UCSRnA = (1<<U2X0);
  *UCSRnB = (3<<TXEN0) | (1<<RXCIE0);
  *UCSRnC = (parity<<UPM00) | ((stop-1)<<USBS0) | ((size-5)<<UCSZ00);
  sei();
}

void UART0_AutoBaudRate(void)
{
	DDRE = ~(1<<PE0);
	TCCR0A = 0;
	TCCR0B = (2<<CS00);
	
	while(PINE & 1<<PE0);
	TCNT0 = 0;

	while(!(PINE & 1<<PE0));
	TCCR0B =0;
	UBRR0 = TCNT0 -1;     //Tiempo/periodo/ps --- ubrr = Fos/(ps*baud)
}

uint8_t UART0_available( void )
{
    if(BUFFER_EMPTY(cola_rx))
	    return 0;
    else
	    return 1;
}

void UART0_putchar(char data)
{
    while(BUFFER_FULL(cola_tx));

	if(BUFFER_EMPTY(cola_tx)){
	    cola_tx.buffer[cola_tx.in_idx++]=data;
		UCSR0B |= (1<<UDRIE0);
	}
    else{
	    cola_tx.buffer[cola_tx.in_idx++]=data;
	}
}

char UART0_getchar(void)
{
    while(BUFFER_EMPTY(cola_rx));
	return cola_rx.buffer[cola_rx.out_idx++];
}

void UART0_puts(char *str)
{
  while(*str){
      UART0_putchar(*str);
	  str++;
  }
}

void UART0_gets(char *str)
{
	unsigned int cnt=0,dato=0;
    char *aux;
	while(dato != 13){
		dato = UART0_getchar();
		if(dato != 8 && dato != 13 && cnt<50){
			UART0_putchar(dato);
			aux = str+cnt;
		    *aux = dato; 
			cnt++;
		}
        else if(dato == 8 && cnt!=0){
			UART0_putchar(dato);
			UART0_puts(" \b");
			cnt--;
		}
	}
	
	aux = str+cnt;
	*aux = '\0';
}

void itoa(char *str,uint16_t number,uint8_t base)
{
	uint16_t res,i=0,j=0;
	uint8_t temp;
	
	while(number != 0)
	{
		res = number%base;
		number = number/base;
		if(res < 10)
		    str[i] = res+'0';
		else 
			str[i] = res+55;
		i++;
	}
	if(i == 0){
		str[i] = '0';
		i++;
	}
	str[i] = '\0';
    i--;
	while(i > j){
		temp = str[i];
		str[i] = str[j];
		str[j] = temp;
		i--;
		j++;
	}
}

uint16_t atoi(char *str)    
{
    uint16_t num=0, i=0;
	
	while(str[i] != '\0' && str[i] > 47 && str[i] < 58)
	{   
		num = (num*10) + (str[i]-'0');
		i++;
	}
	return num;
}

void clrscr( void )
{
    UART0_puts("\033[2J");
}

void gotoxy(uint8_t x,uint8_t y)
{
    char px[8],py[8]; 

	itoa(px,x,10);
	itoa(py,y,10);

    UART0_puts("\033[");
	UART0_puts(py);
	UART0_puts(";");
	UART0_puts(px);
	UART0_puts("f");
}

ISR(USART0_UDRE_vect)
{
    if(BUFFER_EMPTY(cola_tx)){
	    UCSR0B&=(~(1<<UDRIE0));
	}
    else{
	    UDR0=cola_tx.buffer[cola_tx.out_idx++];
	}
}

ISR(USART0_RX_vect)
{
    while(BUFFER_FULL(cola_rx));
	cola_rx.buffer[cola_rx.in_idx++]=UDR0;
}

