#ifndef _TIMER2_H
#define _TIMER2_H
#include <inttypes.h>
#include <avr/interrupt.h>
#include <avr/io.h>
/* Funcion para inicializar el Timer2 para generar N seg. */
void Timer2_Ini( uint8_t baseT );
/* Funcion para verificar bandera del segundo */
uint8_t Timer2_SecFlag( void );

/* Funciones para actualizar el reloj de la consola*/
void Clock_Update( void );
void Clock_Display( void );
void Clock_Ini(uint8_t, uint8_t,uint8_t);
void PrintDec2d(uint8_t);

#endif /* _TIMER2_H */

