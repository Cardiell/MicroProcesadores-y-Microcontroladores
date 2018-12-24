#include <stdio.h>

int main()
{
    printf("%x",~3);
    printf("\n%x",3&6);
    printf("\n%x",3|6);
    printf("\n%x",1|6);
    printf("\n%x",7>>1);
    printf("\n%x",7<<2);
    printf("\n%x",~0);
    printf("\n%x",!0);
    printf("\n%x",2&4);
    printf("\n%x",2&&4);
    printf("\n%x",2|4);
    printf("\n%x",2||4);
    printf("\n%x",0x55<<3);
    printf("\n%x",(0xF<<0)|(1<<6));
    printf("\n%x",(1<<8)|(1<<10)|(3<<12));
    printf("\n%x",(0xFFFF)&(0xD<<10)|(5<<6)|(0xF));

        return 0;
}
