#include <stdio.h>

int main()
{
    char* car1,car2;         // ----->  Respuesta solo car1
    char cadena[10] = {0};
    int multi_enteros[5][5],*apuntador,valor=2;
    cadena[1] = 'H';
    cadena[2] = 'o';
    cadena[3] = 'l';
    cadena[4] = 'a';

    printf("%s",cadena);     // -----> Respuesta
    printf("%s",&cadena[1]); // ---->Respuesta
    printf("\n");
    printf("%s",cadena+3); //   ---->Respuesta
    printf("\n");
    apuntador = (int*)multi_enteros; //--->Respuesta
    multi_enteros[1][1] = 1;
    multi_enteros[1][2] = valor;
    multi_enteros[1][3] = 3;
    printf("%d",apuntador[7]);    // -----> Respuesta
    printf("\n");
    car1 = (char*)&multi_enteros[3][2];
    car1[0] = '1';
    *(car1+1) = '2';
    printf("%d",apuntador[17]);   // ----->12849
    return 0;
}
