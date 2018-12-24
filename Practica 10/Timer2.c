#include "Timer2.h"
#include "UART0.h"

static volatile uint8_t segundos;
static uint8_t base=1;
static uint8_t seg=0,min=0,hor=0;

void Timer2_Ini( uint8_t baseT ){
	if( baseT>0 &&baseT<9){
	base=baseT;
	segundos=0;

	TIMSK2 = 0;                   //borrar  interrupciones
	ASSR = (1<<AS2);              //Seleccionar modo Asincrono
	TCNT2 = 0;                    //Borrar el contador del temporizador
	TCCR2A = (2<<WGM20);          // Valor a comparar
	OCR2A=(32768/1024)-1;         //Motdo CTC
	TCCR2B = (7<<CS20);           // Establecer preescalador de 1024

	while(ASSR&((1<<TCN2UB)|(1<<OCR2AUB)|(1<<OCR2BUB)|(1<<TCR2AUB)|(1<<TCR2BUB))); // Esperar por bandera para hacer el match con el nuevo Crystal
		TIFR2 = (1<<OCF2A);           // Borrar cualqueir interrupcion de desbordamiento pendiente
	TIMSK2=(1<<OCIE2A);               //Habilitar interrupciones que se necesiten
	sei();	                          //Habilitar interrupciones globales
	}	
}

uint8_t Timer2_SecFlag( void ){
	if(segundos==base){
		segundos=0;
		return 1;
	}
	else{
		 return 0;
	}
}

	/* Rutina de Servicio de Interrupción para atender la interrupción */
	/* por Comparación del Timer2 (TCNT2 y OCR2 son iguales) */
ISR(SIG_OUTPUT_COMPARE2A){
	seg++;
	segundos++;
} /* fin de la rutina de servicio de Interrupción (RSI) */

void Clock_Update( void ){
	if(seg>=60){
		seg -= 60;
		min++;
	}
	if(min==60){
		min=0;
		hor++;
	}
	if(hor==24)
		hor=0;
}

void PrintDec2d(uint8_t dato){
	UART0_putchar( dato/10 +'0'); /* Imprime decenas */
	UART0_putchar( dato%10 +'0'); /* Imprime unidades */
}

void Clock_Display( void ){
	/* imprimir reloj en formato "hh:mm:ss" */
	PrintDec2d(hor); /* solo se esta desplegando horas */
	UART0_putchar(':');
	PrintDec2d(min); /* solo se esta desplegando minutos */
	UART0_putchar(':');
	PrintDec2d(seg); /* solo se esta desplegando segundos */
	UART0_putchar(13);
}

void Clock_Ini(uint8_t horas, uint8_t minutos, uint8_t segundos){
	seg = segundos;
	min = minutos;
	hor = horas;
}

