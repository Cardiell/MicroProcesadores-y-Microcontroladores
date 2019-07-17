#include "UART.h"

ring_buffer_t cola_rx,cola_tx;


void inicializarColas(){
	cola_rx.in_idx = 0;
	cola_rx.out_idx = 0;
	cola_tx.in_idx = 0;
	cola_tx.out_idx = 0;
	sei();
}

void UART0_Init(uint8_t com, uint32_t baudrate, uint8_t size, uint8_t parity, uint8_t stop)
{
	  inicializarColas();		//EN ESTA FUNCION SE ACTIVAN LAS INTERRUPCIONES GLOBALES
	  uint32_t *UBRRn;
	  uint16_t *UCSRnA, *UCSRnB, *UCSRnC;  
	  

	  switch(com){
	  	case 0:          // UART 0
			case 1:      // UART 1
			 	case 2:  // UART 2
				      UBRRn  = (uint32_t *)0xC4 +(8*com); // Puesto que cada 8 bits se encuentra otro UART del 0 al 2 se multiplica el numero de UART *8
					  UCSRnA = (uint16_t *)0xC0 +(8*com);
					  UCSRnB = (uint16_t *)0xC1 +(8*com);
					  UCSRnC = (uint16_t *)0xC2 +(8*com);
		break;
	    case 3:          //UART 3                         // Como el UART 3 se encuentra mas arriba que los otros 3 se hace un caso diferente      
				      UBRRn  = (uint32_t *)0x134;
					  UCSRnA = (uint16_t *)0x130;
					  UCSRnB = (uint16_t *)0x131;
					  UCSRnC = (uint16_t *)0x132;
		break;
	  }

	  if(parity==1) parity=3;            // 00 no paridad, 01 reservado 10 par 11 impar 

	  *UBRRn  = MYUBRR(baudrate);
	  *UCSRnA = (1<<U2X0);                  //RXCn TXCn UDREn FEn DORn Upen U2Xn MPCMn
	  *UCSRnB = (3<<TXEN0) | (1<<RXCIE0); //RXCIEn TXCIEn UDRIEn RXENn TXENn UCSZn2 RXB8n TXB8n
	  *UCSRnC = (parity<<UPM00) | ((stop-1)<<USBS0) | ((size-5)<<UCSZ00); // UMSELn1 UMSELn0 UPMn1 UPMn0 USBSn UCSZn1 UCSZn0 UCPOLn
}


uint8_t UART0_AutoBaudRate(void)
{

	DDRE = ~(1<<PE0);
	TCCR0A = 0;
	TCCR0B = (2<<CS00);
	
	while(PINE & (1<<PE0));
	TCNT0 = 0;

	while(!(PINE & 1<<PE0));
	TCCR0B =0;
	UBRR0 = TCNT0 -1;  
	return (TCNT0 -1);

}



unsigned char UART0_available( void )
{
    if(BUFFER_EMPTY(cola_rx))
	    return 0;
	return 1;
}

// ------------------------------------ TRANSMISION ------------------------------
ISR(USART0_UDRE_vect){
	if(BUFFER_EMPTY(cola_tx))
		UCSR0B &= ~(1<<UDRIE0);
	else
		UDR0 = cola_tx.buffer[cola_tx.out_idx++];
		
}

void UART0_putchar(char data){
	while(BUFFER_FULL(cola_tx));
	cola_tx.buffer[cola_tx.in_idx++]=data;
	UCSR0B |= (1<<UDRIE0);
}

// ------------------------------------ RECEPCION ------------------------------------

ISR(USART0_RX_vect){
	if(!(BUFFER_FULL(cola_rx)))
		cola_rx.buffer[cola_rx.in_idx++]=UDR0;
}

char UART0_getchar(void){
	while(UART0_available()==0);
	return cola_rx.buffer[cola_rx.out_idx++];
}


void UART0_puts(char *str){
	while(*str)
		UART0_putchar(*str++);
}


// ------------------------------------------------------------------------------------
void itoa(char* str, uint16_t number,const uint8_t base)
{
	uint16_t t,i=0,j=0;
	uint8_t temp;
	while(number != 0)
	{
		t = number%base;
		number/=base;
		if(t < 10)
		    str[i++] = t+'0';
		else
			str[i++] = t+55;
	}
	if(i == 0)
		str[i++] = '0';
	str[i--] = '\0';
	while(i > j)
		temp = str[i],str[i--] = str[j],str[j++] = temp;
}

uint16_t atoi(const char *str)
{
    uint16_t num=0,i=0;
	while(str[i] != '\0' && str[i] > 47 && str[i] < 58)
		num = (num*10) + (str[i++]-'0');
	return num;
}

void clrscr( void )
{
    UART0_puts("\033[2J");
}

void setColor(uint8_t color)
{
    char colors[8]; 

	itoa(colors,color,10);
    UART0_puts("\033[");
	UART0_puts(colors);
	UART0_puts(";40m");
}

void gotoxy(uint8_t x,uint8_t y)
{
    char px[8],py[8]; 

	itoa(px,x,10);               
	itoa(py,y,10);
    UART0_puts("\033[");
	UART0_puts(py);
	UART0_puts(";");
	UART0_puts(px);
	UART0_puts("f");
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
