#ifndef _MATH_H
#define _MATH_H

#include <inttypes.h>


#define RANGO 9
#define MUESTRAS 10


uint16_t media(uint8_t *); // SUM(xi)/n
uint16_t varianza(uint8_t *,uint16_t); // (SUM((_xi -xi)^2))/(n-1)
int16_t powt(int16_t,int8_t);

#endif
