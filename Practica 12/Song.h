#ifndef _SONG_H
#define _SONG_H

#include <avr/io.h>
#include <avr/pgmspace.h>
#include <inttypes.h>
#include "Timer.h"

typedef const struct note* PGM_S;

//###################################################################################################################################################################

const PROGMEM struct note Clocks[]={       //217
	{dSH, TEMPO_500*1/2},
	{aS,  TEMPO_500*1/2},
	{g,  TEMPO_500*1/2},
	{dSH,  TEMPO_500*1/2},
	{aS, TEMPO_500*1/2},
	{g,  TEMPO_500*1/2},
	{dSH, TEMPO_500*1/2},
	{aS, TEMPO_500*1/2},
	{cSH,  TEMPO_500*1/2},
	{aS,  TEMPO_500*1/2},
	{f,  TEMPO_500*1/2},
	{cSH,  TEMPO_500*1/2},
	{aS,  TEMPO_500*1/2},
	{f, TEMPO_500*1/2},
	{cSH,  TEMPO_500*1/2},
	{aS, TEMPO_500*1/2},
	{cSH, TEMPO_500*1/2},
	{aS,  TEMPO_500*1/2},
	{f,  TEMPO_500*1/2},
	{cSH,  TEMPO_500*1/2},
	{aS, TEMPO_500*1/2},
	{f,  TEMPO_500*1/2},
	{cSH,  TEMPO_500*1/2},
	{aS,  TEMPO_500*1/2},
	{c, TEMPO_500*1/2},
	{gS, TEMPO_500*1/2},
	{f,  TEMPO_500*1/2},
	{cH, TEMPO_500*1/2},
	{gS,  TEMPO_500*1/2},
	{f,  TEMPO_500*1/2},
	{cH,  TEMPO_500*1/2},
	{gS,  TEMPO_500*1/2},
	{dSH, TEMPO_500*1/2},
	{aS, TEMPO_500*1/2},
	{g,  TEMPO_500*1/2},
	{dSH, TEMPO_500*1/2},
	{aS, TEMPO_500*1/2},
	{g,  TEMPO_500*1/2},
	{dSH, TEMPO_500*1/2},
	{aS,  TEMPO_500*1/2},
	{cSH,  TEMPO_500*1/2},
	{aS,  TEMPO_500*1/2},
	{f, TEMPO_500*1/2},
	{cSH,  TEMPO_500*1/2},
	{aS,  TEMPO_500*1/2},
	{f,  TEMPO_500*1/2},
	{cSH,  TEMPO_500*1/2},
	{aS,  TEMPO_500*1/2},
	{cSH,  TEMPO_500*1/2},
	{aS,  TEMPO_500*1/2},
	{f,  TEMPO_500*1/2},
	{cSH,  TEMPO_500*1/2},
	{aS,  TEMPO_500*1/2},
	{f, TEMPO_500*1/2},
	{cSH, TEMPO_500*1/2},
	{aS,  TEMPO_500*1/2},
	{cH, TEMPO_500*1/2},
	{gS,  TEMPO_500*1/2},
	{f,  TEMPO_500*1/2},
	{cH, TEMPO_500*1/2},
	{gS,  TEMPO_500*1/2},
	{f, TEMPO_500*1/2},
	{cH, TEMPO_500*1/2},
	{gS,  TEMPO_500*1/2},
	{dSH, TEMPO_500/3},
	{aS, TEMPO_500/3},
	{g, TEMPO_500/3},
	{dSH, TEMPO_500/3},
	{aS, TEMPO_500/3},
	{g, TEMPO_500/3},
	{dSH, TEMPO_500/3},
	{aS, TEMPO_500/3},
	{cSH, TEMPO_500/3},
	{aS, TEMPO_500/3},
	{f, TEMPO_500/3},
	{cSH, TEMPO_500/3},
	{aS, TEMPO_500/3},
	{f, TEMPO_500/3},
	{cSH, TEMPO_500/3},
	{aS, TEMPO_500/3},
	{cSH, TEMPO_500/3},
	{aS, TEMPO_500/3},
	{f, TEMPO_500/3},
	{cSH, TEMPO_500/3},
	{aS, TEMPO_500/3},
	{f, TEMPO_500/3},
	{cSH, TEMPO_500/3},
	{aS, TEMPO_500/3},
	{cH, TEMPO_500/3},
	{gS, TEMPO_500/3},
	{f, TEMPO_500/3},
	{cH, TEMPO_500/3},
	{gS, TEMPO_500/3},
	{f, TEMPO_500/3},
	{cH, TEMPO_500/3},
	{gS, TEMPO_500/3},
	{dSH, TEMPO_500/3},
	{aS, TEMPO_500/3},
	{g, TEMPO_500/3},
	{dSH, TEMPO_500/3},
	{aS, TEMPO_500/3},
	{g, TEMPO_500/3},
	{dSH, TEMPO_500/3},
	{aS, TEMPO_500/3},
	{cSH, TEMPO_500/3},
	{aS, TEMPO_500/3},
	{f, TEMPO_500/3},
	{cSH, TEMPO_500/3},
	{aS, TEMPO_500/3},
	{f, TEMPO_500/3},
	{cSH, TEMPO_500/3},
	{aS, TEMPO_500/3},
	{cSH, TEMPO_500/3},
	{aS, TEMPO_500/3},
	{f, TEMPO_500/3},
	{cSH, TEMPO_500/3},
	{aS, TEMPO_500/4},
	{f, TEMPO_500/3},
	{cSH, TEMPO_500/3},
	{aS, TEMPO_500/3},
	{cH, TEMPO_500/3},
	{gS, TEMPO_500/3},
	{f, TEMPO_500/3},
	{cH, TEMPO_500/3},
	{gS, TEMPO_500/3},
	{f, TEMPO_500/3},
	{cH, TEMPO_500/3},
	{gS, TEMPO_500/3},
	{g, TEMPO_500*3/4},
	{g, TEMPO_500*1/2},
	{g, TEMPO_500*3/4},
	{aS, TEMPO_500*1/4},
	{cSH, TEMPO_500*1/4},
	{cH, TEMPO_500*3/4},
	{f, TEMPO_500*3/4},
	{f, TEMPO_500*3/4},
	{f, TEMPO_500*1/2},
	{f, TEMPO_500*3/4},
	{aS, TEMPO_500*1/6},
	{f, TEMPO_500*1/2},
	{f, TEMPO_500*3/4},
	{g, TEMPO_500*1/2},
	{g, TEMPO_500*3/4},
	{g, TEMPO_500*1/2},
	{g, TEMPO_500*3/4},
	{f, TEMPO_500*1/4},
	{cSH, TEMPO_500*1/4},
	{cH, TEMPO_500*1/4},
	{f, TEMPO_500*3/4},
	{f, TEMPO_500*3/4},
	{f, TEMPO_500*1/2},
	{f, TEMPO_500*3/4},
	{f, TEMPO_500*3/4},
	{dSH, TEMPO_500*1/3},
	{aS,  TEMPO_500*1/3},
	{g,  TEMPO_500*1/3},
	{dSH,  TEMPO_500*1/3},
	{aS, TEMPO_500*1/3},
	{g,  TEMPO_500*1/3},
	{dSH, TEMPO_500*1/3},
	{aS, TEMPO_500*1/3},
	{cSH,  TEMPO_500*1/3},
	{aS,  TEMPO_500*1/3},
	{f,  TEMPO_500*1/3},
	{cSH,  TEMPO_500*1/3},
	{aS,  TEMPO_500*1/3},
	{f, TEMPO_500*1/3},
	{cSH,  TEMPO_500*1/3},
	{aS, TEMPO_500*1/3},
	{cSH, TEMPO_500*1/3},
	{aS,  TEMPO_500*1/3},
	{f,  TEMPO_500*1/3},
	{cSH,  TEMPO_500*1/3},
	{aS, TEMPO_500*1/3},
	{f,  TEMPO_500*1/3},
	{cSH,  TEMPO_500*1/3},
	{aS,  TEMPO_500*1/3},
	{c, TEMPO_500*1/3},
	{gS, TEMPO_500*1/3},
	{f,  TEMPO_500*1/3},
	{cH, TEMPO_500*1/3},
	{gS,  TEMPO_500*1/3},
	{f,  TEMPO_500*1/3},
	{cH,  TEMPO_500*1/3},
	{gS,  TEMPO_500*1/3},
	{dSH, TEMPO_500*1/3},
	{aS, TEMPO_500*1/3},
	{g,  TEMPO_500*1/3},
	{dSH, TEMPO_500*1/3},
	{aS, TEMPO_500*1/3},
	{g,  TEMPO_500*1/3},
	{dSH, TEMPO_500*1/3},
	{aS,  TEMPO_500*1/3},
	{cSH,  TEMPO_500*1/3},
	{aS,  TEMPO_500*1/3},
	{f, TEMPO_500*1/3},
	{cSH,  TEMPO_500*1/3},
	{aS,  TEMPO_500*1/3},
	{f,  TEMPO_500*1/3},
	{cSH,  TEMPO_500*1/3},
	{aS,  TEMPO_500*1/3},
	{cSH,  TEMPO_500*1/3},
	{aS,  TEMPO_500*1/3},
	{f,  TEMPO_500*1/3},
	{cSH,  TEMPO_500*1/3},
	{aS,  TEMPO_500*1/3},
	{f, TEMPO_500*1/3},
	{cSH, TEMPO_500*1/3},
	{aS,  TEMPO_500*1/3},
	{cH, TEMPO_500*1/3},
	{gS,  TEMPO_500*1/3},
	{f,  TEMPO_500*1/3},
	{cH, TEMPO_500*1/3},
	{gS,  TEMPO_500*1/3},
	{f, TEMPO_500*1/3},
	{cH, TEMPO_500*1/3},
	{gS,  TEMPO_500*1/3}
};



const PROGMEM struct note FIN[] ={{'\0','\0'}};

PGM_S playList[]={
	Clocks,
	FIN

};



#endif

