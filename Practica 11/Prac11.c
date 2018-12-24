#include "UART.h"
#include "Timer.h"
#include "Ports.h"
#include "Song.h"



uint32_t notaslen();
uint16_t memlen();
void imprimeVolumen(int8_t volumen,uint8_t dato);
void imprimenumCancion(uint8_t num);

char buffer[60];
uint8_t idx=0;
int8_t volu=100;

uint8_t dato;
int main(void)
{

	UART0_AutoBaudRate();
	UART_ini(0,1234,8,0,1);
	InitPorts();
	Timer0_Ini();
	clrscr();

	gotoxy(60,0);
	UART0_puts("Bienvenido Usuario");
	imprimenumCancion(idx);
	imprimeVolumen(1,' ');
	gotoxy(50,6);
	UART0_puts("presiona p para reproducir una cancion");
	gotoxy(64,7);
	UART0_puts("[   ]");
	gotoxy(66,7);
	while(1){
		if (UART0_available()){
			dato=UART0_getchar();
			// Play Song
			if(dato == 'p'){
				Timer2_Play((playList[idx]),notaslen()); //void Timer2_Play(const struct note *,uint8_t)
					gotoxy(66,7);
					UART0_putchar('p');
			}
			
			//Increase Volume
			if(dato == 'V'){
				Timer2_Volume(1);
				imprimeVolumen(1,'V');
			}
			//Decrease Volume
			if(dato == 'v'){
				Timer2_Volume(-1);
				imprimeVolumen(-1,'v');
			}


		}

		switch (checkBtn()){
			case BNT_NEXT: 
					if(idx < (memlen()))
					{	
						idx++;
						Timer2_Play((playList[idx]),notaslen());
					}
				    imprimenumCancion(idx);
			break;
			case BNT_PREV: 
				if(idx>0)
				{
					idx--;
					Timer2_Play((playList[idx]),notaslen());
				}
				imprimenumCancion(idx);
			break;
		}

	}
	return 0;
}


void imprimeVolumen(int8_t volumen,uint8_t dato)
{
	if((volumen == -1 && volu != 0) | (volumen == 1 && volu != 100) | (dato==' ')){
		if(dato!=' ')
			volu += (volumen*10);
		itoa(buffer,volu,10);
		gotoxy(0,0);
		UART0_puts("Volumen:     %");
		gotoxy(9,0);
		UART0_puts("  ");
		UART0_puts(buffer);
		gotoxy(47,14);
		UART0_puts("Presiona V para subir volumen o v para bajar");
		gotoxy(64,15);
		UART0_puts("[   ]");
		gotoxy(66,15);
		UART0_putchar(dato);
		}

}

void imprimenumCancion(uint8_t num)
{
	gotoxy(62,30);
	UART0_puts("Cancion[    ]: ");
	gotoxy(71,30);
	itoa(buffer,idx+1,10);
	UART0_puts(buffer);
	gotoxy(62,32);
	UART0_puts("                                         ");
	gotoxy(62,32);
	UART0_puts((char *)(LetrasCanciones[idx]));
	
}

uint32_t notaslen()
{

	if(idx < memlen()+1)
		return (playList[idx+1]- playList[idx]); //Correcto
	return 0;

}

uint16_t memlen()
{
  return ((sizeof(playList)/sizeof( const struct note* ))-2);
}

