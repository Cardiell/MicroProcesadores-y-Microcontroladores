#define INTR 8
#define WORD unsigned int

extern void pokew(WORD segment,WORD offset,WORD value);
void interrupt ManejadorISR( void );
unsigned char TimerSecFlag( void );
void Timer_Ini( void );

volatile static unsigned char SecFlag; 
                                      
void interrupt ManejadorISR( void )
{
    static unsigned char Cont = 0;
    Cont++; 
    if(Cont == 20){
        SecFlag=1;
        Cont = 0;
    }
}
 
unsigned char TimerSecFlag( void )
{
    if( SecFlag == 1 ){
        SecFlag = 0;
        return 1;
    }
    else
        return 0;
}
 
void Timer_Ini( void )
{
    SecFlag=0;
    pokew(0x0,INTR*4,((WORD)&ManejadorISR)+0x100); 
    pokew(0x0,INTR*4+2,_CS); 
}