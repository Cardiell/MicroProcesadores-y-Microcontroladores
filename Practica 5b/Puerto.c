#include "Puerto.h"



void SetBitPort(WORD Puerto, BYTE num_bit)
{
	outportb( Puerto,inportb(Puerto)|(0x01 << num_bit) );
}


void ClrBitPort(WORD Puerto, BYTE num_bit)
{
	outportb( Puerto,inportb(Puerto)&~(0x01 << num_bit) );
}


void NotBitPort(WORD Puerto, BYTE num_bit)
{
	outportb( Puerto,inportb(Puerto)^(0x01 << num_bit) );  
}


BYTE TstBitPort(WORD Puerto, BYTE num_bit)
{
	if( (inportb(Puerto)&(0x01 << num_bit)) == 0 )
		return 0;
	else 
		return 1;
}


