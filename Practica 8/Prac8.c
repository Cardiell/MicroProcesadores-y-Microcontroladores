//https://www.avrfreaks.net/forum/turning-onoff-one-bit-port

/*
				DDR
		  ___________________
			  0  | Entrada
			  1  | Salida

			    PORT
		   ___________________________
		      DDR=0   |   0   |  Gnd
			  DDR=0   |   1   |   5v
              DDR=1   |   1	  |  Pull-up		  
*/
#include <avr/io.h>
// Macros
#define SetBitPort(port, bit) asm ("sbi %0, %1"::"I"(_SFR_IO_ADDR(port)),"I" (bit))
#define ClrBitPort(port, bit) asm ("cbi %0, %1"::"I"(_SFR_IO_ADDR(port)),"I" (bit))

// Press States
#define UNDEFINED 0
#define SHORT_PRESSED 1
#define LONG_PRESSED 2

// Prototypes
void delay(uint16_t mseg);
void InitPorts(void);
void LedOn(uint8_t dato);
void LedOff();
uint8_t checkBtn(void);
void updateLeds(void);

// Global variables
uint8_t globalCounter=0,bandera=0;
uint8_t Led[8][2]={
		{0x43,0x82},
		{0x43,0x81},
		{0x46,0x84},
		{0x46,0x82},
		{0x45,0x81},
		{0x45,0x8E},
		{0x4C,0x88},
		{0x4C,0x84}};


uint32_t millis=0,aux;


int main(void){
delay(1);

InitPorts();
	while(1){
		switch(checkBtn()){
			case SHORT_PRESSED: globalCounter++;
			break;
			case LONG_PRESSED: globalCounter--;
			break;
		}
	updateLeds();
	delay(1);
	millis++;
	}
}

void InitPorts(void) 
{     
    DDRF = 0b01001111; //0 = Entrada
	PORTF =0b10001111; //1 = Salida
}

void updateLeds(void)
{
	uint8_t msk=0x1;
	uint8_t bandera;
	uint8_t i;
	uint8_t temp=globalCounter;
	for(i=0;i<8;i++)
	{
		DDRF =Led[i][0];
		bandera=msk&temp;
			if(bandera)
				LedOn(Led[i][1]);
			else
				LedOff();
		temp>>=1;
		delay(1);
		millis++;
	}
	
}
void LedOn(uint8_t dato)
{
	uint8_t bandera; 
	bandera = dato&1;
	if(bandera)
		SetBitPort(PORTF,0);
	else
		ClrBitPort(PORTF,0);
	dato>>=1;
	bandera=dato&1;
	if(bandera)
		SetBitPort(PORTF,1);
	else
		ClrBitPort(PORTF,1);
	dato>>=1;
	bandera=dato&1;
	if(bandera)
		SetBitPort(PORTF,2);
	else
		ClrBitPort(PORTF,2);
	dato>>=1;
	bandera=dato&1;
	if(bandera)
		SetBitPort(PORTF,3);
	else
		ClrBitPort(PORTF,3);
	
}
void LedOff()
{
	DDRF=0x40;
	ClrBitPort(PORTF,0);
	ClrBitPort(PORTF,1);
	ClrBitPort(PORTF,2);
    ClrBitPort(PORTF,3);
}

void delay(uint16_t mseg){ 	
	uint16_t i=0; 		  
	while(mseg!=0){      
		i= 1999;          
		asm("nop");          
		while(i!=0){     
			i--;          
		   asm("nop");    
		   asm("nop");	
		   }
		 mseg--;	    
		}	
	
}  	                          



uint8_t checkBtn(void){

	if(!(PINF&(1<<PF7)) && !bandera){
		aux=millis;
		bandera=1;
	}	
	if((aux+40) < millis && bandera)
		if((PINF&(1<<PF7))){
			bandera=0;
			if((aux+1000)> millis)
				return  SHORT_PRESSED;
			else
				return  LONG_PRESSED;
		}
		
	return UNDEFINED;	
}
