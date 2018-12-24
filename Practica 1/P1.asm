.MODEL TINY
	LOCALS
.DATA
	   J        DW					0
	   N    	DW 					5
	   NS 		DW					0
	cadena 		DB	 'MICROPROCESADORESYMICROCONTROLADORES',0

.CODE
	ORG 100H

__main  PROC

				MOV 			SP,0FFFH			;inicializa SP(Stack Pointer)
@@While:											; while(1);
				CALL			__CIFRAR
				JMP				@@While
				RET									; nunca se llega aqui
ENDP

;**********************************************************************************************
;paragm:	
__CIFRAR	PROC	

				XOR				SI,SI               ;C
				XOR				DI,DI               ;I
				LEA 			DX,cadena           ;CX
				CALL			__STRLEN
				CMP				N,1
				JNE	 			@@WHILE
				LEA  			DX,CADENA
				CALL 			__PUTS
				JMP				@@FIN
@@WHILE:
				MOV				NS,0
				MOV				SI,DI   		     ;C=I
@@DO:	
				OR				DI,DI                ;if(i>0)
				JLE				@@ELSE	
				MOV				AX,N
				DEC				AX 						
				CMP				AX,DI 			     ;if(i<renglones-1)
				JLE				@@ELSE
				CMP				SI,J                 ;if(c>=j)
				JL				@@ELSE
				MOV				BX,SI
				SUB				BX,J
				MOV				AL,cadena[BX]
				CALL			__PUTCHAR
@@ELSE:
				CMP				SI,CX
				JGE				@@NOP
				MOV				BX,OFFSET cadena
				MOV				AL,BYTE PTR [BX+SI]
				CALL  			__PUTCHAR
@@NOP:
				MOV				AX,N
				ADD				AX,N
				ADD				AX,65534
				ADD				NS,AX
				MOV				AX,DI
				ADD				AX,NS
				MOV				SI,AX	
				MOV				AX,SI
				SUB				AX,J
				CMP				AX,CX
				JL				@@DO	
				MOV				AX,J
				INC				AX
				INC				AX
				MOV				J,AX	
				MOV				AX,DI
				INC				AX
				MOV				DI,AX
@@NEXT:
				CMP	DI,N
				JL	@@WHILE

@@FIN:
				RET
__CIFRAR ENDP

;**********************************************************************************************
;@paragm:   CX tiene el tamano de la cadena enviada por parametro
__STRLEN	PROC 							
				PUSH			 BX
				MOV 			 BX,DX
				XOR 			 CX,CX							; int i=0
@@While: 
				CMP  	 		BYTE PTR[BX],0					;while(cad[i]!=0)
				JE   	 		@@End_While
				INC 	 		CX								; i++
				INC 	 		BX
				JMP 	 		@@While
@@End_While: 
				POP 	 		BX
				RET
__STRLEN	ENDP

;**********************************************************************************************
;@paragm:  	 AL tiene el valor a imprimir
__PUTCHAR	PROC
				PUSH			 AX
				PUSH			 DX
				MOV 			 DL,AL
				MOV 			 AH,2						; imprimir caracter DL
				INT 			 21H						; usando servicio 2 (AH=2)
				POP 			 DX							; de la interrupcion21 INT 21H
				POP 			 AX
				RET
__PUTCHAR  ENDP
;**********************************************************************************************
;@paragm:	DX tiene la direccion de la cadena a imprimir
__PUTS	PROC
				PUSH 			 AX
				PUSH			 BX
				MOV 			 BX,DX
@@While: 
				MOV 			 AL,BYTE PTR[BX]
				CMP  			 AL,0
				JE   			 @@End_While
				CALL 			 __PUTCHAR
				INC 			 BX
				JMP 	 		@@While
@@End_While: 	
				POP 	 		BX
				POP 	 		AX
				RET
__PUTS	ENDP

END __main