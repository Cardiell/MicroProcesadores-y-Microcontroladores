#include <avr/io.h>
#include "UART.h"
#include "Timer.h"
#include "Song.h"


uint32_t notaslen(uint8_t);
uint16_t memlen();
void menu(uint8_t caracter,uint8_t numSpeaker);

int main()
{
	uint8_t tecla,idx=2;
	UART0_Init(0,115200,8,0,1);
	Timer1_Ini();
	InitPorts();
	clrscr();
	menu(' ',3);
	while(1)
	{
		if(UART0_available()) {
			tecla=UART0_getchar();
		//Si se presiona 1 se reproduce o para la Cancion
			if(tecla =='1') {
				if(Speaker[0].estado==PAUSE) {										//La estructura Speaker se encuentra en Timer.h , se crearon 2 estructura una para cada bocina.
					Speaker[0].estado=PLAY;
					menu('X',1);
					Speaker_Play(playList[idx+5],notaslen(idx+5),1);
				}else {																
					Speaker[0].estado=PAUSE;
					menu(' ',1);
					Speaker_Pause();
				}
		//Si se presiona 2 se reproduce o para la 2da cancion
			}else if(tecla =='2') {
				if(Speaker[1].estado==PAUSE) {										
					Speaker[1].estado=PLAY;  
					menu('X',2);              
					Speaker_Play(playList[idx],notaslen(idx),2);  //Se encia la cancion, el numero de notas y el numero de Speaker
				}else{																
					Speaker[1].estado=PAUSE; 
					menu(' ',2);
					Speaker_Pause();
				}
		//Si se presiona 3 ambas bocinas se paran.
			}else if(tecla=='3') {
				Speaker[0].estado=PAUSE;
				Speaker[1].estado=PAUSE;
				menu(' ',3);
				Speaker_Pause();
			}
		}
	}
	return 0;
}

void menu(uint8_t caracter,uint8_t numSpeaker)
{

	if(numSpeaker ==1)
	{
		gotoxy(20,11);
		UART0_putchar(caracter);
	}else if(numSpeaker ==2) {
		gotoxy(46,11);
		UART0_putchar(caracter);
	}else{
		gotoxy(10,0);
		UART0_puts("Bienvenido usuario presiona 1 o 2 para repdoducir una cancion");
		gotoxy(10,2);
		UART0_puts("         Presiona 3 para pausar ambas canciones      ");
		gotoxy(15,10);
		UART0_puts("Cancion 1                 Cancion 2");
		gotoxy(15,11);
		UART0_puts("   [   ]                     [   ]   ");
	} 
}


uint32_t notaslen(uint8_t idx)
{

	if(idx < memlen()+1)
		return (playList[idx+1]- playList[idx]); //Correcto
	return 0;

}

uint16_t memlen()
{
  return ((sizeof(playList)/sizeof( const struct note* ))-2);
}


