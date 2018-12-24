#ifndef _TIMER_H
#define _TIMER_H
#include <inttypes.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>

#define c 261
#define d 294
#define e 329
#define f 349
#define g 391
#define gS 415
#define a 440
#define aS 466
#define b 494
#define aa 	493
#define cH 523
#define cSH 554
#define dH 587
#define dSH 622
#define eH 659
#define fH 698
#define fSH 740
#define gH 784
#define gSH 830
#define aH 880
#define hH 	987
#define bL 247
#define fS 370
#define cS 277
#define aL 220
#define gL 196
#define dS 311
#define gSL 208
#define cL 131
#define eL 165
#define aSL 233

#define C6 1046 
#define F6 1397
#define G6 1568
#define G_7 3322
#define G_6 1661
#define G_5 831
#define E7 2637
#define E6 1318
#define D7 2349
#define D6 1174
#define B6 1976
#define B5 988
#define A6 1760
#define A_6 1865
#define A5 880
#define A_5 932
#define C_7 2093
#define C_6 1109
#define E5 659


// More notes can be found at:
// http://www.intmath.com/trigonometric-graphs/music.php

#define TEMPO	500
#define TEMPO_500 500
#define TEMPO_250 250
#define TEMPO_600 600
#define TEMPO_700 700
#define SILENCE 10

struct note{
	uint16_t freq;
	uint16_t delay;
};


void Timer0_Ini( void );
void Timer2_Freq_Gen(uint8_t ticks);
void Timer2_Play(const struct note *song,unsigned int len);
void Timer2_Volume(int8_t direction);
uint32_t getMillis(void);
#endif
