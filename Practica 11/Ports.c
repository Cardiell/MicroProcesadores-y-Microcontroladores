/*
				DDRF
		  ___________________
			  0  | Entrada
			  1  | Salida

			    PORT
		   ___________________________
		      DDR=0   |   0   |  Gnd
			  DDR=0   |   1   |   5v
              DDR=1   |   1	  |  Pull-up		  
*/

#include "Ports.h"
#include "Timer.h"

uint8_t next=0,prev=0,flag=0;
uint32_t aux=0;
void InitPorts(void) 
{     
    DDRD  =  0; //0 = Entrada  1 salida
	PORTD = (1<<PD3) | (1<<PD0); // Pull-up
	DDRH |= (1<<PH6);
}


uint8_t checkPress(uint8_t PD)  //cuando no se presiona el boton es 1 puesto que esta leyendo el voltaje del pull-up
{

	if(!(PINF&(PD)) && !flag){
		aux=getMillis();
		flag=1;
	}	
	if((aux+40) < getMillis() && flag)
		if((PINF&(PD))){
			flag=0;
			if((aux+1000)> getMillis())
				return  SHORT_PRESSED;
			else
				return  LONG_PRESSED;
		}
		
	return UNDEFINED;		
}

uint8_t checkBtn(void)
{

	if((!(PIND&((1<<PD3))) && !next)){
		aux=getMillis();
		next=1;
	}
	else if((!(PIND&((1<<PD0))) && !prev)){
		aux=getMillis();
		prev=1;
	}

	if((aux+40) < getMillis() && (next | prev))
	{        // Esperando 40 segundos por el rebote
		if((PIND&(1<<PD3)) && next)//
		{
			next=0;
			aux=getMillis();      
			  while(getMillis()<aux+80);
				return  BNT_NEXT;

		}
		else if((PIND&(1<<PD0)) && prev){//si Pin3 esta en 1 regrese BNT_NEXT sino PREV
			prev=0;
			aux=getMillis();      
			  while(getMillis()<aux+80);
				return  BNT_PREV;
		}
	}
		
			return UNDEFINED;	
}

