#include "Timer.h"
#define BYTE unsigned char

extern void putchar(char dato);
extern void pokeb(unsigned int,unsigned int,BYTE);
void UpdateClock( void );
void DisplayClock( void );
void PrintDec2d( BYTE );
void delay( BYTE );
void setClock(BYTE,BYTE,BYTE);


BYTE seg=50; 
BYTE min=59;
BYTE hr=23;

void main()
{
    Timer_Ini(); 
	setClock(hr,min,seg);
	DisplayClock();
    while(1){
        if(TimerSecFlag() ){
           UpdateClock();
           DisplayClock();
           pokeb(0x0000, 0XFFFF,seg);
        }
        delay(100);
    }
} 
   
void UpdateClock( void )
{
	seg++;
    if(seg==60){	
        seg=0;
	    min++;
	}
    if(min==60){	
	    min =0;
	    hr++;
	}
    if(hr==24)
	    hr=0;
}
 
void DisplayClock( void )
{
    PrintDec2d(hr); 
    putchar(':');
    PrintDec2d(min);
    putchar(':');
    PrintDec2d(seg);
    putchar(13);
} 

void delay( BYTE i)
{
    while(--i);
}
 
void PrintDec2d( BYTE dato)
{
    putchar( dato/10 +'0'); 
    putchar( dato%10 +'0'); 
}

void setClock(BYTE horas,BYTE minutos,BYTE segundos)
{
	hr=horas; 
	min=minutos;
	seg=segundos;
}
   