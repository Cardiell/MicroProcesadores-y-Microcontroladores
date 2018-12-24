#include "Puerto.h"       
#define PTOs_Config 0x88 

extern void putchar(char);
extern char getch(void);

void delay( WORD );
void printBin(BYTE);
void puts(const char *);
void LedOn(BYTE);
void LedOff();
void imprimeLeds(BYTE);
BYTE bits=0x0,temp;

BYTE Led[6][2]={{0x89,0x02},
			    {0x89,0x01},
			 	{0x98,0x04},
			 	{0x98,0x02},
			 	{0x8A,0x01},
			 	{0x8A,0x04}};
int i;

void main( void ){
	outportb(RCtr, PTOs_Config); /* inicializar 8255 */
	while(1)
	{
		for(i=0; i<=7; i++)
		{
			puts("\r\n");
			puts("bit ");
			putchar(i+'0');
			puts(": ");
			getch();
			temp=TstBitPort(PC,4);	
			printBin(temp);
			temp <<=i;
			bits |=temp;	
		}
		puts("\r\n");
		puts("Cadena Final: ");
		printBin(bits);
        while(1){
        	imprimeLeds(bits);
        }
	}
}

void imprimeLeds(BYTE dato)
{
	BYTE msk=0x1;
	BYTE bandera;
	BYTE x;
	for(i=0;i<6;i++)
	{
		outportb(RCtr,Led[i][0]); /* inicializar 8255 */
		bandera= msk&dato;
		if(bandera)
			LedOn(Led[i][1]);
		else
			LedOff();
		dato>>=1;
	}
}

void LedOn(BYTE dato)
{	
	BYTE bandera;
	bandera=dato&1;
	if(bandera)
		SetBitPort(PA,1);
	else
		ClrBitPort(PA,1);
	dato>>=1;
	bandera=dato&1;
	if(bandera)
		SetBitPort(PB,1);
	else
		ClrBitPort(PB,1);
	dato>>=1;
	bandera=dato&1;
	if(bandera)
		SetBitPort(PC,1);
	else
		ClrBitPort(PC,1);

		delay(35);
}
void LedOff()
{
	ClrBitPort(PA,1);
	ClrBitPort(PB,1);
	ClrBitPort(PC,1);
		delay(35);
}

void delay( WORD i)
{
    while(--i);
}

/* función simple para desplegar un byte en formato binario */
void printBin( BYTE dato ){
	BYTE msk=0x80;
	do{
		putchar( (dato & msk) ? '1' : '0' );
		msk>>=1;
	}while( msk );
}

void puts(const char *cad)
{
	while(*cad)
		putchar(*cad++);
}

/* 
     Control    MODO     PA    PCh   MOD    PB    PCb 
      __________________________________________________
        1         00      0      1     0      0     0*
        
	MODO
    00 = Modo 0
    01 = Modo 1
    !X = Modo 2

   PA,PB,PC
   0 = salida
   1 = entrada

 */