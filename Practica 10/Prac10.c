#include <avr/io.h>
#include "Timer0.h"
#include "Timer2.h"
#include "UART0.h"

int main()
{
    char str[]="";
	UART0_AutoBaudRate();	
	UART_ini(0,123,8,0,1);               /* llamar a función para inicializar UART0 */

	
	clrscr();
	gotoxy(5,1);
	UART0_puts("Autobauding done. UBRR0=");
	itoa(str,UBRR0,10);
	UART0_puts(str);
	UART0_puts("\n\r");
	Timer0_Ini();
	Timer2_Ini(7);  
	Clock_Ini(23,59,50);

	while(1){ 							/* == main loop == */
		if( Timer2_SecFlag() ){ 		/* ¿ha pasado n Segundo? */
			Clock_Update();
			gotoxy(5,2);
			Clock_Display();
			gotoxy(5,3);
			UART0_puts("millis=");
			itoa(str,millis(),10);		/* itoa solo convertirá los 16bits menos significativos */
			UART0_puts(str);
		}
	} 									/* fin del loop principal */
	return 0; 							/* <-- no se llega aquí */
}
