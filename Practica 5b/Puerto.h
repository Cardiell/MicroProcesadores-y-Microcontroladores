#define BYTE unsigned char
#define WORD unsigned int
#define PA 0x40
#define PB 0x41
#define PC 0x42          
#define RCtr 0x43 

extern void outportb( WORD,BYTE);
extern BYTE inportb( WORD);

/* @paragm : Activar un bit de un puerto
			 Puerto: PA,PB,PC
			 num_bit: 0...7*/
void SetBitPort( WORD,BYTE ); 

/* @paragm : borrar un bit de un puerto es decir darle valor de 0
			 Puerto: PA,PB,PC
			 num_bit: 0...7*/
void ClrBitPort( WORD,BYTE );

/* @paragm : Invierte un bit en posicion num_bit del puerto
			 Puerto: PA,PB,PC
			 num_bit: 0...7*/
void NotBitPort( WORD,BYTE );

/* @paragm : retorna el estado del bit de la posición num_bit del puerto 
			 Puerto: PA,PB,PC
			 num_bit: 0...7*/
BYTE TstBitPort( WORD,BYTE );

