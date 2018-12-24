#include "Math.h"

uint16_t media(uint8_t *datos) // SUM(xi)/n
{
	uint8_t i;
	uint16_t media=0;
	for(i=0;i<MUESTRAS;i++)
		media+=datos[i];        //SUM(xi)
return (media/MUESTRAS);     
}


uint16_t varianza(uint8_t *datos,uint16_t media) // (SUM((xi-_xi)^2))/(n)
{
	uint16_t suma=0;
	uint8_t i;

	for(i=0;i<MUESTRAS;i++)
		suma+=powt((datos[i]-media),2);		
return (suma/(MUESTRAS-1));
}



int16_t powt(int16_t base,int8_t exp)
{
	uint8_t i;
	int16_t res=1;
	 for(i=0;i<exp;i++)
	 	res *= base;

	return res;
}
