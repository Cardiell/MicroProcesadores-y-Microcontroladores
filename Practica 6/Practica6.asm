;-;------------- definiciones e includes ------------------------------
.INCLUDE "m1280def.inc" ; Incluir definiciones de Registros para 1280
;------------- inicializar ------------------------------------------
LDI R24,1
 
LDI R26,0x55;   0000 0000 0101 0101
LDI R27,0x00;X  1010 1010 0100 1000----
;                                      |
LDI R28,0xAA;   0000 0000 1010 1010    |   R24=0
LDI R29,0x00;Y  0101 0101 0000 0000----
;                                      |
LDI R30,0x55;	0000 0000 0101 0101    |   R24 =1
LDI R31,0x00;Z  1010 1010 0000 0000----
;------------- ciclo principal --------------------------------------
inicio: 
      CPI R24,0                          ;	if(R24 ==0)
      BREQ cero                          ; 		 goto cero; 
	  CPI R24,1                          ;	if(R24 ==0) 
	  BREQ uno                           ;    	goto uno;
	  RJMP inicio                        ;   goto inicio;


cero:                                    ;cero:

	  MOVW R20:R21,X                      ; TEMP=X
	  MOVW X,Y                            ; X=Y 
	  MOVW Y,R20:R21                      ; Y=TEMP

      CLC                  ;C=0
	  ROR Xl               ;Rd[7]=0->C      ----> 0101 0101       Rd[0]=0 -> C       R26=0x55
	  ROL Xh               ;Rd[0]=0->C      <---  0000 0000       Rd[7]=0 -> C       R27=0x00                   
	  ROR Xl               ;Rd[7]=0->C      ----> 0010 1010       Rd[0]=1 -> C       R26=0x2A
	  ROL Xh               ;Rd[0]=1->C      <---  0000 0001       Rd[7]=0 -> C       R27=0x01
	  ROR Xl               ;Rd[7]=0->C      ----> 0001 0101       Rd[0]=0 -> C       R26=0x15
	  ROL Xh               ;Rd[0]=0->C      <---  0000 0010       Rd[7]=0 -> C       R27=0x02
	  ROR Xl               ;Rd[7]=0->C      ----> 0000 1010       Rd[0]=1 -> C       R26=0x0A
	  ROL Xh               ;Rd[0]=1->C      <---  0000 0101       Rd[7]=0 -> C       R27=0x05
	  ROR Xl               ;Rd[7]=0->C      ----> 0000 0101       Rd[0]=0 -> C       R26=0x05
	  ROL Xh               ;Rd[0]=0->C      <---  0000 1010       Rd[7]=0 -> C       R27=0x0A
	  ROR Xl               ;Rd[7]=0->C      ----> 0000 0010       Rd[0]=1 -> C       R26=0x02
	  ROL Xh               ;Rd[0]=1->C      <---  0001 0101       Rd[7]=0 -> C       R27=0x15
	  ROR Xl               ;Rd[7]=0->C      ----> 0000 0001       Rd[0]=0 -> C       R26=0x01
	  ROL Xh               ;Rd[0]=0->C      <---  0010 1010       Rd[7]=0 -> C       R27=0x2A
	  ROR Xl               ;Rd[7]=0->C      ----> 0000 0000       Rd[0]=1 -> C       R26=0x00
	  ROL Xh               ;Rd[0]=1->C      <---  0101 0101       Rd[7]=0 -> C       R27=0x55
	  ROR Xl               ;Rd[7]=0->C      ----> 0000 0000       Rd[0]=0 -> C       R26=0x00

      CLC                  ;C=0
	  ROR Yl               ;Rd[7]=0->C      ----> 0000 1001       Rd[0]=0 -> C       R26=0x09
	  ROL Yh               ;Rd[0]=0->C      <---  0110 1000       Rd[7]=0 -> C       R27=0x68
	  ROR Yl               ;Rd[7]=0->C      ----> 0000 0100       Rd[0]=1 -> C       R26=0x04
	  ROL Yh               ;Rd[0]=1->C      <---  1101 0001       Rd[7]=0 -> C       R27=0xD1
	  ROR Yl               ;Rd[7]=0->C      ----> 0000 0010       Rd[0]=0 -> C       R26=0x02
	  ROL Yh               ;Rd[0]=0->C      <---  1010 0010       Rd[7]=1 -> C       R27=0xA2
	  ROR Yl               ;Rd[7]=1->C      ----> 1000 0001       Rd[0]=0 -> C       R26=0x81
	  ROL Yh               ;Rd[0]=0->C      <---  0100 0100       Rd[7]=1 -> C       R27=0x44
	  ROR Yl               ;Rd[7]=1->C      ----> 1100 0000       Rd[0]=1 -> C       R26=0xC0
	  ROL Yh               ;Rd[0]=1->C      <---  1000 1001       Rd[7]=0 -> C       R27=0x89
 	  ROR Yl               ;Rd[7]=0->C      ----> 0110 0000       Rd[0]=0 -> C       R26=0x60
	  ROL Yh               ;Rd[0]=0->C      <---  0001 0010       Rd[7]=1 -> C       R27=0x12
	  ROR Yl               ;Rd[7]=1->C      ----> 1011 0000       Rd[0]=0 -> C       R26=0xB0
	  ROL Yh               ;Rd[0]=0->C      <---  0010 0100       Rd[7]=0 -> C       R27=0x24
	  ROR Yl               ;Rd[7]=0->C      ----> 0101 1000       Rd[0]=0 -> C       R26=0x58
	  ROL Yh               ;Rd[0]=0->C      <---  0100 1000       Rd[7]=0 -> C       R27=0x48
      ROR Yl               ;Rd[7]=0->C      ----> 0010 1100       Rd[0]=0 -> C       R26=0x2C
	  RJMP inicio
	
uno: 								        
	
	  MOVW R20:R21,Z                        ;
	  MOVW Z,Y
	  MOVW Y,R20:R21
	  ;C=0          
 	  ;       -->0001 0010--> 
	  ;      |               |
	  ;      C               C
	  ;      |               |
	  ;       <--0011 0100<--
      CLC
	  ROR Zl
	  ROL Zh

	  ROR Zl
	  ROL Zh

	  ROR Zl
	  ROL Zh

	  ROR Zl
	  ROL Zh

	  ROR Zl
	  ROL Zh

      ROR Zl
	  ROL Zh

	  ROR Zl
	  ROL Zh

	  ROR Zl
	  ROL Zh
	  ROR Zl

      CLC            ; Limpiando el carry
	  ROR Yl
	  ROL Yh

	  ROR Yl
	  ROL Yh

	  ROR Yl
	  ROL Yh

	  ROR Yl
	  ROL Yh

	  ROR Yl
	  ROL Yh

      ROR Yl
	  ROL Yh

	  ROR Yl
	  ROL Yh

	  ROR Yl
	  ROL Yh
	  ROR Yl
	  RJMP inicio
	 
;--------------------------------------------------------------------

