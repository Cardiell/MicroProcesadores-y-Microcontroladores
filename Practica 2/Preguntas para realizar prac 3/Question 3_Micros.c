#include <stdio.h>
#include <stdint.h>
typedef struct camposBits{
	unsigned char b0:2;
	unsigned char b1:2;
	unsigned char b2:2;
	unsigned char b3:2;
}CAMPOS_BITS_T;

typedef union arreglo{
	uint32_t u32; // dato sin signo de 32 bits
	uint16_t u16[2]; // dato sin signo de 16 bits
	uint8_t u8[4]; // dato sin signo de 8 bits
	CAMPOS_BITS_T byte_bits[4];
}ARREGLO_T;

int main() {
    ARREGLO_T mi_arreglo;

    mi_arreglo.u32 = 0xA;
    mi_arreglo.byte_bits[3].b2 = 2;
    mi_arreglo.u16[1] |= 7;
    mi_arreglo.u32 |= 9<<21;
    mi_arreglo.u16[0] |= 3<<13;
    printf("%x",mi_arreglo); // ---> Respuesta
    return 0;
}
