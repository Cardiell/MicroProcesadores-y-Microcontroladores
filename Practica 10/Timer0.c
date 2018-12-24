#include "Timer0.h"

static volatile uint32_t milliSec = 0;
void Timer0_Ini ( void ){

	 TCNT0=0; /* Inicializar valor para el timer0 */
	 TCCR0A=(2<<WGM00); /* inicializa timer0 en modo CTC */
	 OCR0A = (250 - 1);
	 TIMSK0=(1<<OCIE0A); /* habilita interrupcion de comparacion con registro OCR0A */
	 TCCR0B=(3<<CS00); /* con Prescalador 64 */
	 TIFR0=0;
	 sei(); /* habilita interrupciones (global) */
}

ISR (TIMER0_COMPA_vect){ /* Interrupcion por comparacion de registro A */
	milliSec++; /* Incrementa contador de milisegundos */
}


uint32_t millis(void){
	return milliSec;
}
