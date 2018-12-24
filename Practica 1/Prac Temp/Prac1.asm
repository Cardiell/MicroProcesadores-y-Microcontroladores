.model tiny
	locals
.data

	cadena DB 'MICROPROCESADORESYMICROCONTROLADORES',0

.code
             org 100h

main	PROC
		MOV 	SP,0FFFh					;inicializa SP(Stack Pointer)
@@While:									; while(1);
		MOV		AX,OFFSET cadena
		PUSH	AX
		CALL	STRLEN
		POP 	AX
		MOV 	DX,AX
		CALL    PUTS
		MOV		DX,CX
		CALL 	PUTS
		JMP		@@While
		RET 								; nunca se llega aqui
ENDP

;**********************************************************************************************
;@paragm:   CX tiene el tamano de la cadena enviada por parametro
STRLEN	PROC 							;---------------------------
		PUSH	BP
		MOV		BP,SP
		PUSH	SI 							;int strlen(const char *cad)
		PUSH	DI
		MOV		DI,WORD PTR [BP+4] 			;---------------------------
	   	XOR		SI,SI						;      int i=0
@@While:
		MOV		BX,DI
		CMP		BYTE PTR[BX],0				;----------------------------
		JE		@@End_While					;	while(*cad++)
		INC		DI							;---------------------------
		INC		SI							;		i++;
@@End_While:
		MOV		CX,SI						;---------------------------
		POP		DI
		POP		SI							;		return i;
		POP		BP
		RET;								--------------------------
ENDP

;**********************************************************************************************
;@paragm:  	 AL tiene el valor a imprimir
PUTCHAR	PROC
		PUSH	 AX
		PUSH	 DX
		MOV 	 DL,AL
		MOV 	 AH,2						; imprimir caracter DL
		INT 	 21H						; usando servicio 2 (AH=2)
		POP 	 DX							; de la interrupcion21 INT 21H
		POP 	 AX
		RET
PUTCHAR  ENDP
;**********************************************************************************************
;@paragm:	DX tiene la direccion de la cadena a imprimir
PUTS	PROC
		PUSH 	 AX
		PUSH	 BX
		MOV 	 BX,DX
@@While: 
		MOV 	 AL,BYTE PTR[BX]
		CMP  	 AL,0
		JE   	 @@End_While
		CALL 	 PUTCHAR
		INC 	 BX
		JMP 	 @@While
@@End_While: 
		POP 	 BX
		POP 	 AX
		RET
ENDP

END