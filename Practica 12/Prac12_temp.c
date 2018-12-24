#include "UART.h"
#include "Timer.h"
#include "Ports.h"
#include "Song.h"
#include "Math.h"


void ADC_Ini();
uint8_t ADC_Read(uint8_t channel);
uint8_t motionDetected(void);
char buffer[30];


int main()
{
	uint8_t seg10=0,flag=0;
	UART0_AutoBaudRate();
	UART_ini(0,9600,8,0,1);
	InitPorts();
	ADC_Ini();
	Timer0_Ini();
	UART0_puts("Detectando...");

	while(1)
	{
		if(UART0_available())
		{
			if(motionDetected()==1)
			{
				UART0_puts("Detected\r\n");
				seg10=0;
				if(flag==0)
				{
					Timer2_Play(playList[0],(playList[1]- playList[0]));
					flag=1;
				}
			}

			if( Timer0_SecFlag() && motionDetected()==0 &&flag==1)
			{
				seg10++;
				if(seg10==10)
				{
					UART0_puts("10 seg no Detected\r\n");
					Timer2_Stop();
					seg10=0;
					flag=0;
				}
			}
		}
	}


return 0;

}


void ADC_Ini()
{
//medir tierra y lo que nos de guardarlo en variable offset y restarselo a ADCH
	

	ADMUX  = (1<<ADLAR)|(1<<REFS0);   		//ADC y ajustando resultado a la izquierda
	ADCSRA = (1<<ADEN) | (7<<ADPS0);  		//Preescalador 128 y habilitando ADC
	ADCSRB = 0;                       		//No trigger
	//DIDR0  = (1<<ADC1D);              		//ADC1 solamente como convertidor analogico Digital, para ahorrar consumo de potencia del micro
	

}

uint8_t ADC_Read(uint8_t channel)
{
  channel &= 0x07;                          // MASCARA
  ADMUX = (ADMUX & 0xF8)|channel;           // Obteniendo el canal deseado
  ADCSRA |= (1<<ADSC); 					    // Inicia conversion
  while(ADCSRA & (1<<ADSC));                // Esperando a leer el dato
  return (ADCH);
}

uint8_t motionDetected(void)
{
	uint8_t i;
	uint16_t varian;
	static uint8_t datos[MUESTRAS];

	for(i=0;i<MUESTRAS;i++)
		datos[i]=ADC_Read(7);
	varian =(varianza(datos,media(datos))*5)/512;
	if( varian > RANGO)
		return 1;
	else
		return 0;
}
//ADSC


