.MODEL TINY
  LOCALS
.DATA
      TEMP        DB                      100 DUP(?)
      CADENA      DB      "MICROPROCESADORESYMICROCONTROLADORES",0
      N           DW                      5

.CODE
  ORG 100H

__main  PROC
                      MOV       SP,0FFFH                       ;inicializa SP(Stack Pointer)
                      CMP       N,1
                      JE        @@NO
                      LEA       DX,CADENA
                      CALL      PUTS
                      JMP       FINITO
@@NO:
                      CALL      __CIFRAR
@@FINITO:
                      JMP @@FINITO
                      RET
ENDP
;************************************************************************************************************************
;@paragm: Procedimiento para cifrar un texto.
__CIFRAR    PROC
                      MOV       SI,0                           ; i=0
                      XOR       BX,BX
@@PimerosCaracteres:
                      CMP       SI,N                           ; if(i == N)  ....
                      JE        @@WHILE
                      MOV       AL,CADENA[BX]                  ; temp[i] = cadena[i];
                      MOV       TEMP[SI],AL              
                      INC       SI     
                      ADD       BX,1                           ;       i++;
                      JMP       @@PimerosCaracteres            ; Ingresando la cadena inicial = MICROP
@@WHILE:
                      CMP       CADENA[BX],0                            ;while(i != tamCad)
                      JE        @@FIN
                      MOV       CX,N                            ; num = N
                      DEC       CX                              ; num--
                      MOV       AX,0                            ; bandera=0 
@@LOOP:                                                         ;while(num!=0)
                      CMP       WORD PTR CADENA[BX],0                    ; if(cadena[i]!=0) .......
                      JE        @@excepcion                     ;  else
                      MOV       DI,WORD PTR CADENA[BX]          ;       cad = cadena[i]  
                      PUSH      DI                              ;       push(cad)
                      INC       BX                              ;       i++
                      INC       AX                              ;       bandera++
                      LOOP      @@LOOP                          ;       num--
                      JMP       @@NORMAL
@@excepcion:                                                    ;.......
                      MOV       CX,AX                           ; num = bandera
                      JMP       @@INGRESAR
@@NORMAL:                              
                      MOV       CX,N                            ; num = N
                      DEC       CX                              ; num--
@@INGRESAR:

@@LOOP2:                                                        ;while(num!=0)
                      POP       DI                              ;  bx = pop()
                      MOV       WORD PTR TEMP[SI],DI            ;  temp[i] = bx
                      INC       SI                              ;   i++
                      LOOP      @@LOOP2                         ;   num--
                      MOV       WORD PTR TEMP[SI],'*'
                      INC       SI
                      MOV       WORD PTR TEMP[SI],'*'
                      INC       SI 
                      MOV       CX,N                             ; num = N
                      DEC       CX                               ; num--  
@@LOOP3:                                                         ;while(num!=0){
                      CMP       CADENA[BX],0                     ; if(cadena[i] == 0) ......
                      JE        @@FIN
                      MOV       DX,WORD PTR CADENA[BX]                    ;   al = cadena[i]
                      MOV       WORD PTR TEMP[SI],DX                      ;   temp[i] = al
                      INC       SI  
                      INC       BX                               ;    i++
                      LOOP      @@LOOP3                          ;    num-- }

                      JMP       @@WHILE                          ; }
@@FIN:
                      MOV       TEMP[SI],0
                      CALL      __IMPRIMIR
                      RET
__CIFRAR   ENDP
;**********************************************************************************************
;paragm: Procedimiento el cual permite imprimir de manera correcta la cadena previamente almacenada en Variable TEMP
__IMPRIMIR  PROC
                      LEA BX,TEMP
                      CALL __SIZEOF
                      XOR DI,DI                   ; i=0
                      JMP @@WHILE
@@COMPARA:
                      MOV SI,DI                   ; j=i
                      JMP @@ENTONCES
@@WHILE2: 
                      CMP BYTE PTR TEMP[SI],'*'   ; if(temp[si] != '*')
                      JNE @@NEXT
                      ADD SI,N                    ; j+=5;
                      JMP @@ENTONCES              ; continue;
@@NEXT: 
                      MOV AL,BYTE PTR TEMP[SI]    ; putchar(temp[j]);
                      CALL __PUTCHAR
                      ADD SI,N                    ; j+=5;
@@ENTONCES:
                      CMP SI,DX                   ; while(j < tam)
                      JL  @@WHILE2
                      INC DI
@@WHILE:
                      CMP DI,N                    ; while(i<N)
                      JL  @@COMPARA
                      RET
__IMPRIMIR ENDP
;***********************************************************************
;@paragm: BX toma la posicion inical de la candena y DX el tamano de la cadena
__SIZEOF proc
                      XOR SI,SI                    ;i=0
@@INICIO:
                      CMP BYTE PTR[BX+SI],0        ;while(cadena[i]!=0)
                      JE @@FIN
                      INC SI                       ; i++
                      JMP @@INICIO
@@FIN:
                      MOV DX,SI                   
                      RET
__SIZEOF endp
;**********************************************************************************************
;@paragm:    AL tiene el valor a imprimir
__PUTCHAR PROC
                      PUSH       AX
                      PUSH       DX
                      MOV        DL,AL
                      MOV        AH,2           ; imprimir caracter DL
                      INT        21H            ; usando servicio 2 (AH=2)
                      POP        DX             ; de la interrupcion21 INT 21H
                      POP        AX
                      RET
__PUTCHAR  ENDP
;**********************************************************************************************
;@paragm: DX tiene la direccion de la cadena a imprimir
__PUTS  PROC
        PUSH       AX
        PUSH       BX
        MOV        BX,DX
@@While: 
        MOV        AL,BYTE PTR[BX]
        CMP        AL,0
        JE         @@End_While
        CALL       __PUTCHAR
        INC        BX
        JMP       @@While
@@End_While:  
        POP       BX
        POP       AX
        RET
__PUTS  ENDP
END __main
