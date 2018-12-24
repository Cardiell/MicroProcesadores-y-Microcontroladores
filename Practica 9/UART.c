#include "uart.h"

ring_buffer_t buffer_RX; 
ring_buffer_t buffer_TX;


void Buffer_ini( void )
{
    buffer_RX.in_idx  = 0;
    buffer_RX.out_idx = 0;
	buffer_TX.in_idx  = 0;
    buffer_TX.out_idx = 0;
	sei();
}

void UART_Ini(uint8_t com, uint16_t baudrate, uint8_t size,uint8_t parity, uint8_t stop)
{
	  Buffer_ini();
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
	  *UCSRnA = 0;                  //RXCn TXCn UDREn FEn DORn Upen U2Xn MPCMn
	  *UCSRnB = (3<<TXEN0) | (1<<RXCIE0); //RXCIEn TXCIEn UDRIEn RXENn TXENn UCSZn2 RXB8n TXB8n
	  *UCSRnC = (parity<<UPM00) | ((stop-1)<<USBS0) | ((size-5)<<UCSZ00); // UMSELn1 UMSELn0 UPMn1 UPMn0 USBSn UCSZn1 UCSZn0 UCPOLn
}



uint8_t UART0_available( void )
{
    return (BUFFER_EMPTY(buffer_RX) ? 0 : 1); //retorna 0 si el buffer esta vacio de lo contrario 1
}



void UART0_putchar(char data)
{
    while(BUFFER_FULL(buffer_TX));// quedate aqui hasta que el buffer no este lleno
      	buffer_TX.buffer[buffer_TX.in_idx]=data;
	    buffer_TX.in_idx=MOD(buffer_TX.in_idx-1);
		UART_EnableTransmitIT();
}

ISR(USART0_UDRE_vect)
{
    if(BUFFER_EMPTY(buffer_TX))
	    UART_DisableTransmitIT();
    else{
	
	    UDR0=buffer_TX.buffer[buffer_TX.out_idx];
    	buffer_TX.out_idx=MOD(buffer_TX.out_idx-1);
    }
}

//    --------------------------------------------------------------
char UART0_getchar(void)
{
    char d;
    while(UART0_available()==0); // quedate aqui hasta que el buffer no este vacio
	d=buffer_RX.buffer[buffer_RX.out_idx];
	buffer_RX.out_idx=MOD(buffer_RX.out_idx-1);
	return d;
}


ISR(USART0_RX_vect)
{
    if(BUFFER_FULL(buffer_RX)==0)
    {
	
		buffer_RX.buffer[buffer_RX.in_idx]=UDR0;
	    buffer_RX.in_idx=MOD(buffer_RX.in_idx-1);
	}
}
//------------------------------------------------------------

void UART0_puts(char *str)
{
  while(*str)
      UART0_putchar(*str++);
}

void UART0_gets(char *str)
{
	uint16_t cont=0;
	while((str[cont]=UART0_getchar())!='\r')
	{
		if(cont<17||str[cont]=='\b')
		{
			if(str[cont]=='\b')
			{
				if(cont>0)
					UART0_putchar(str[cont--]),UART0_puts(" \b");
			}
			else if(str[cont]!='\b')
				UART0_putchar(str[cont++]);
         }
	}
	str[cont]='\0';
}



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



