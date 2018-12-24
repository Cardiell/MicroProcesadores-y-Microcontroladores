extern char getchar(void);
extern void putchar(char);
void gets(char *);
void puts(const char *);
void itoa(char *,unsigned int,const unsigned char);
unsigned int atoi(const char *);

char cad[50];
char res[50];
unsigned int dato;

int main(void)
{
    while(1){
		puts("Ingresa un numero base 10:");
		gets(cad);
		dato = atoi(cad);
		itoa(res,dato,16);
		puts(res);
		itoa(res,dato,2);
		puts(res);
    }
	return 0;
}

void gets(char *cad)
{
	int cont=0;
	while((cad[cont]=getchar())!='\r')
	{
		if(cont<17||cad[cont]=='\b')
			if(cad[cont]=='\b')
			{
				if(cont>0)
					putchar(cad[cont--]),putchar(' '),putchar('\b');
			}
			else if(cad[cont]!='\b')
				putchar(cad[cont++]);
	}
	cad[cont]='\0';
	puts("\r\n");
}

void puts(const char *cad)
{
	while(*cad)
		putchar(*cad++);
	putchar('\r');
	putchar('\n');

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

unsigned int atoi(const char *pCad)
{
    unsigned int num=0;
    int i=0;
	while(pCad[i] != '\0' && pCad[i] > 47 && pCad[i] < 58)
		num = (num*10) + (pCad[i++]-'0');
	return num;
}
