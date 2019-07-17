#include "Timer.h"
#include "UART.h"

#define T_TIMER (16000000/256)
#define TICKS(f) (T_TIMER/f)        /*	Definir el macro que calcula los ticks en base a al parametro de frecuencia (f). */


uint8_t silencio=0,silencio2=0;

void Timer1_Ini( void )//     1ms
{
	TCNT1  = 0;           			 // Inicializar valor para el timer1 
	TCCR1A = 0;  
	OCR1A  = (250-1);     			 // T_t*(Freq/Presc) = 1ms*(16000000/64) = 250 
    TIMSK1 = (1<<OCIE1A); 			 // habilita interrupcion del Timer1 
	sei();                			 // habilita interrupciones (global) 
	TCCR1B = (3<<CS10)|(1<<WGM12);   // con Prescalador 64 y  modo CTC
}


ISR(TIMER1_COMPA_vect)
{ 
		//Reiniciando canciones
if(Speaker[0].cnt==Speaker[0].longCancion) Speaker[0].cnt=0; 
if(Speaker[1].cnt==Speaker[1].longCancion) Speaker[1].cnt=0;
	
	/*    Codigo necesario para sacar la frecuencia necesaria para el Speaker 1     */

	if(Speaker[0].estado==PLAY)	{
		Speaker[0].mSecCnt++; 				
		
		if(silencio == 0){
		    if(Speaker[0].flag == 0){
			    Timer_Freq_Gen(TICKS(pgm_read_word(&(Speaker[0].cancion[Speaker[0].cnt].freq))),1);
				Speaker[0].flag = 1;
			}
		    if(Speaker[0].mSecCnt == pgm_read_word(&(Speaker[0].cancion[Speaker[0].cnt].delay))){
				Speaker[0].flag = 0;
				Speaker[0].mSecCnt=0;
				Speaker[0].cnt++;
				silencio = 1;
		    }
	    } 
	    else{
		    if(Speaker[0].flag == 0){
			    Timer_Freq_Gen(0,1);
				Speaker[0].flag = 1;
			}
		    if(Speaker[0].mSecCnt == SILENCE){
			    Speaker[0].mSecCnt = 0;
			    silencio = 0;
				Speaker[0].flag = 0;
			}
	    }
	}
/*    Codigo necesario para sacar la frecuencia necesaria para el Speaker 2 */

	if(Speaker[1].estado ==PLAY){
		Speaker[1].mSecCnt++;			
		if(silencio2 == 0){
		    if(Speaker[1].flag == 0){
			    Timer_Freq_Gen(TICKS(pgm_read_word(&(Speaker[1].cancion[Speaker[1].cnt].freq))),2);
				Speaker[1].flag = 1;
			}
		    if(Speaker[1].mSecCnt == pgm_read_word(&(Speaker[1].cancion[Speaker[1].cnt].delay))){
				Speaker[1].flag = 0;
				Speaker[1].mSecCnt=0;
				Speaker[1].cnt++;
				silencio2 = 1;
		    }
	    } 
	    else{
		    if(Speaker[1].flag == 0){
			    Timer_Freq_Gen(0,2);
				Speaker[1].flag = 1;
			}
		    if(Speaker[1].mSecCnt == SILENCE){
			    Speaker[1].mSecCnt = 0;
			    silencio2 = 0;
				Speaker[1].flag = 0;
			}
	    }
	}
}

void Timer_Freq_Gen(uint8_t ticks,uint8_t numSpeaker)
{
		if(Speaker[0].estado==PLAY && numSpeaker ==1){
			if(ticks > 0){                             //	Si "ticks" es mayor que 0 entonces, inicializa y habilita el Generador de Frecuencia del Timer2 con el tope dado por "ticks".
				OCR2A  = ticks-1;                      // estableciando la frecuencia de la musica
				TCCR2A |= (1<<COM2A0);                // Toggle OC2A on Compare Match    
				TCCR2B |= (6<<CS20);			      // preescalador 256  
			}else
				TCCR2B = 0;                           //De lo contrario se requiere deshabilitar el Generador, generando de  esta forma el silencio (0 lógico).
		}
		if(Speaker[1].estado==PLAY && numSpeaker ==2){ 
			DDRB |= (1<<PB7);  
			if(ticks > 0){                             //	Si "ticks" es mayor que 0 entonces, inicializa y habilita el Generador de Frecuencia del Timer0 con el tope dado por "ticks". 
				OCR0A  = ticks-1;                      // estableciando la frecuencia de la musica
				TCCR0A |= (1<<COM0A0);                // Toggle OC0A on Compare Match 
				TCCR0B |= (4<<CS00);
			}else									  //De lo contrario se requiere deshabilitar el Generador, generando de  esta forma el silencio (0 lógico).
				TCCR0B = 0;
				
		}
}

void Speaker_Play(const struct note *song,unsigned int len,uint8_t numSpeaker)/*	Función que establece las condiciones necesarias para queel generador recorra el arreglo de notas. */
{

	if(Speaker[0].estado == PLAY && numSpeaker==1) {
	/*    Valores iniciales para Speaker 0   */
		Speaker[0].longCancion=len;
		Speaker[0].flag=0;
		Speaker[0].mSecCnt=0;
		Speaker[0].cancion=song;
		TCCR2A |= (2<<WGM20);  				 // Modo CTC  ----Top OCRA
	}
	if(Speaker[1].estado == PLAY && numSpeaker==2) {
	/*    Valores iniciales para Speaker 0   */
		Speaker[1].longCancion=len;
		Speaker[1].flag=0;
		Speaker[1].mSecCnt=0;
		Speaker[1].cancion = song;           
		TCCR0A |= (2<<WGM00);                //Modo CTC   ----Top OCRA
	}

    Timer_Freq_Gen(0,numSpeaker);
}



void Speaker_Pause()
{
	if(Speaker[0].estado==PAUSE)
	{
		TCCR2B = 0;
	}
   if(Speaker[1].estado==PAUSE)
	{
		TCCR0B = 0;
		DDRB &= ~(1<<PB7);
	}
}
void InitPorts(void) 
{     
	DDRB |= (1<<PB4); 
}

