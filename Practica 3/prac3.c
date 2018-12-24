extern unsigned char peek(unsigned int,unsigned int);
extern void poke(unsigned int,unsigned int,unsigned int);
extern void printNumBase(unsigned int,unsigned int);
extern void putchar(char);
extern char getch(void);
void error(unsigned char,unsigned char);
void puts(const char *);
void fallo(char *,unsigned char);
void falloDirecciones(int); 
void itoa(char *,unsigned int,const unsigned char);

unsigned int offset = 0x2200;
char dato[50];
unsigned char data; 

void main(){ 
		int i;

	while(1)
	{
	for(i=0;i<11;i++)                              
		poke(0,offset+(0x0001<<i),0x00); 
	falloDirecciones(offset);
		poke(0,offset,0xAA);
		data = peek(0,offset);
		if(data != 0xAA)
			fallo("0xAA",0xAA); 
		poke(0,offset,0x55);
		data = peek(0,offset);
		if(data != 0x55) 
			fallo("0x55",0x55);
		if(offset == 0xFFFF)
			break;
		offset++;
	}
	puts("...Ok....");
	while(1)
		getch();
} 

void falloDirecciones(int j)      		  
{                                             
	unsigned char i;
	int bandera=0;  

 	poke(0,offset,0xFF);
	for(i=1;i<11;i++)                             
	{                                       
		if(peek(0,offset+(0x0001<<i)) != 0x00)     
		{   
			if(bandera==0){
				puts("Fallo direccion: ");
				itoa(dato,j,16);
				puts(dato);
				puts("\r\n");
			}
			puts("Linea(s): ");
			itoa(dato,i,10);
			puts(dato);
			puts(", ");
			getch();
			poke(0,offset+(0x0001<<i),0x00);
			bandera++;
		}

	}
	bandera=0;
			puts("\n\r");

}


void error(unsigned char d,unsigned char hex)
{
	int i=0;
	unsigned char xor = d^hex,mascara,temp;  
	while(i <=7)  
	{                    
		temp = xor>>i;
		mascara = temp & 0x01;
		if(mascara==0x01)
		{
			putchar(i+'0');
			putchar(',');
		}
		i++;
	}

}

void fallo(char *escribio,unsigned char hex1)
{ 
	unsigned char temp;
	puts("..ERROR..\n\r");
	if(data==0x00)
	{
		puts("Fallo catastrofico..");
		while(1)
			getch();
	}else{
		puts("Dir:  ");
		itoa(dato,offset,16);
		puts(dato);
		puts("\n\rW: ");
		puts(escribio);
		puts("\n\rLinea(s): ");
		error(data,hex1);
		if(hex1== 0xAA)		temp = 0x55;
		else				temp = 0xAA;
		poke(0,offset,temp);
		data = peek(0,offset);
		if(data != temp) 
			error(data,temp);
		puts("\n\rR: ");
		printNumBase(data,16);
		puts("\n\r");
		while(1)
		  getch();
	}

}

void puts(const char *cad)
{
	while(*cad)
		putchar(*cad++);
}

void itoa(char *pCad,unsigned int numero,const unsigned char base)
{
	int t,i=0,j=0;
	char temp;
	while(numero != 0)
	{
		t = numero%base;
		numero/=base;
		if(t < 10)
		    pCad[i++] = t+'0';
		else
			pCad[i++] = t+55;
	}
	if(i == 0)
		pCad[i++] = '0';
	pCad[i--] = '\0';
	while(i > j)
		temp = pCad[i],pCad[i--] = pCad[j],pCad[j++] = temp;
}

