#include <avr/io.h>
#include "UART.h"


int main(void)
{
	char cad[20];
	uint16_t num;
	UART_Ini(0,12345,8,1,2);//numero de UART,baudrate,size Data , Paridad , Stop bit
	while(1) {
		UART0_getchar();
		clrscr();
		gotoxy(2,2);
		setColor(YELLOW); //Definirlo en UART.h
		UART0_puts("Introduce un numero:");
		gotoxy(22,2);
		setColor(GREEN); //Definirlo en UART.h
		UART0_gets(cad);
		num = atoi(cad);
		itoa(cad,num,16);
		gotoxy(5,3);
		setColor(BLUE); //Definirlo en UART.h
		UART0_puts("Hex: ");
		UART0_puts(cad);
		itoa(cad,num,2);
		gotoxy(5,4);
		UART0_puts("Bin: ");
		UART0_puts(cad);
	}

	return 0;
}

