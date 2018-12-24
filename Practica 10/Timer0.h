#ifndef _TIMER0_H
#define _TIMER0_H
#include <inttypes.h>
#include <avr/interrupt.h>

/* Funci�n para inicializar el Timer0 y generar */
/* la temporizaci�n de 1 Sec. */
void Timer0_Ini ( void );

// Funcion que retorna la cantidad de milli segundos desde que arranco el sistema.
uint32_t millis(void);

#endif /* _TIMER0_H */
