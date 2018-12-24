#include "Timer.h"
#include "UART.h"

#define T_TIMER (16000000/256)
#define TICKS(f) (T_TIMER/f)        /*	Definir el macro que calcula los ticks en base a al parametro de frecuencia (f). */


const struct note *cancion;
uint16_t mSecCnt=0;
uint16_t tam=0;
uint16_t cnt=0;
uint8_t  vol=100;
uint8_t silencio=0;
int16_t bandera =0;

static volatile uint32_t milliSec = 0;

void Timer0_Ini ( void )//     1ms
{
	TCNT0  = 0;           // Inicializar valor para el timer0 
	TCCR0A = (2<<WGM00);  // inicializa timer0 en modo 2(CTC) 
	OCR0A  = (250-1);     // T_t*(Freq/Presc) = 1ms*(16000000/64) = 250 
    TIMSK0 = (1<<OCIE0A); // habilita interrupcion del Timer0 
	sei();                // habilita interrupciones (global) 
	TCCR0B = (3<<CS00);   // con Prescalador 64 
}

ISR(TIMER0_COMPA_vect)
{ 

	mSecCnt++; 					/* 	Código para actualizar bandera de milisegundos */
	milliSec++;

	/*	Agregar las instrucciones necesarias para reproducir la siguiente nota en el arreglo dependiendo de la duración,e insertar los silencios entre cada nota. */
    if(cnt < tam){
		if(silencio == 0){
		    if(bandera == 0){
			    Timer2_Freq_Gen(TICKS(pgm_read_word(&cancion[cnt].freq)));
				bandera = 1;
			}
		    if(mSecCnt == pgm_read_word(&cancion[cnt].delay)){
				bandera = 0;
				mSecCnt=0;
				cnt++;
				silencio = 1;
		    }
	    } 
	    else{
		    if(bandera == 0){
			    Timer2_Freq_Gen(0);
				bandera = 1;
			}
		    if(mSecCnt == SILENCE){
			    mSecCnt = 0;
			    silencio = 0;
				bandera = 0;
			}
	    }
	}else{
    	Timer2_Freq_Gen(0);
	}
}

void Timer2_Freq_Gen(uint8_t ticks)
{
	if(ticks > 0){                             //	Si "ticks" es mayor que 0 entonces, inicializa y habilita el Generador de Frecuencia del Timer2 con el tope dado por "ticks".

		OCR2A  = ticks-1;                      // estableciando la frecuencia de la musica
		OCR2B  = ((OCR2A/2)*vol)/100;          // Estableciendo el tope del volumen de las canciones volumen maximo 50%
		if(OCR2B !=0)
		{
			TCCR2A |= (2<<COM2B0);                // 0 cuando OCR2A llegue al tope             
			TCCR2B |= (6<<CS20) | (1<<WGM22);     // preescalador 256
		}else{
			TCCR2A |= (2<<COM2B0);                // 0 cuando OCR2A llegue al tope             
			TCCR2B = 0;     // preescalador 256
		}

	}else{                                   //De lo contrario se requiere deshabilitar el Generador, generando de  esta forma el silencio (0 lógico).

	    TCCR2B = 0;                          //Parando el contador del timer 2
	}
}

void Timer2_Play(const struct note *song,unsigned int len)/*	Función que establece las condiciones necesarias para queel generador recorra el arreglo de notas. */
{
	cnt = 0;
	bandera = 0;
	mSecCnt = 0;	

    cancion = song;                                          //Asignandole a cancion la estructura que se manda desde por parametro
	tam = len;                                               //asignandole a tam la longitud de la cancion
	TCCR2A |= (3<<WGM20) | (2<<COM2B0);                     // Fast PWM OCRA ---- 0 cuando OCR2B llegue al tope
	TCCR2B |= (1<<WGM22);                                   // Configuracion como Fast PWM OCRA
    Timer2_Freq_Gen(0);
}

void Timer2_Volume(int8_t direction)	/* 	Ajusta el ciclo de trabajo para incrementar o decrementar el volumen de las notas que se estan generando. */
{

    if((direction == -1 && vol != 0) | (direction == 1 && vol != 100))
        vol += (direction*10);
}

uint32_t getMillis(void){
	return milliSec;
}
