DOSSEG
.MODEL TINY
	.CODE
	ORG 100H
PUBLIC _peek
PUBLIC _poke
PUBLIC _printNumBase
PUBLIC _putchar
PUBLIC _getch
org 100h
;----------------------------------------------------------------------------------
_peek PROC NEAR
					PUSH 		BP 
					MOV 		BP,SP 
     				MOV 		DX,[BP+4] ; Segmento
     				MOV 		BX,[BP+6] ; Offset
	 				PUSH 		DS
	 				MOV 		DS,DX
     				MOV 		AL,BYTE PTR[BX]
	 				POP 		DS
	 				MOV 		SP,BP
					POP 		BP 	
					RET 
_peek ENDP 
;----------------------------------------------------------------------------------
_poke PROC NEAR
					PUSH 		BP 
					MOV 		BP,SP 
				    MOV 		DX,[BP+4] ; Segmento
				    MOV 		BX,[BP+6] ; Offset
				    MOV 		AX,[BP+8] ; Dato
					PUSH 		DS
					MOV 		DS,DX
					MOV 		BYTE PTR[BX],AL
				    POP 		DS
				    MOV			SP,BP
					POP 		BP 
					RET
_poke ENDP 

;------------------------------------------------------------------------------------
_printNumBase PROC NEAR
					PUSH 		BP 
					MOV 		BP,SP 
				    MOV 		AX,[BP+4];num
					MOV 		BX,[BP+6];base
					XOR 		CX,CX 
@@NXT:	
					XOR 		DX,DX 
					DIV 		BX  
					PUSH		DX 
					INC 		CX
					CMP 		AX,0
					JNE 		@@NXT
@@VERIF:
					POP 		AX
					CMP 		AX,10 
					JB 			@@LESS
					ADD 		AX,7
@@LESS: 
					ADD 		AX,'0'
					CALL 		putchars 
					LOOP 		@@VERIF
					MOV 		SP,BP
					POP 		BP 
					RET 
_printNumBase ENDP
;-----------------------------------------------------------------
putchars PROC	NEAR
					PUSH		AX
					PUSH		DX
					MOV 		DL,AL
					MOV 		AH,02h
					INT			21H
					POP 		DX
					POP 		AX
					RET
putchars ENDP


;***********************************************************************
;@paragm: se mada como parametro el caracter a imprimir y lo recoge
;		  DL para su previa impresion
_putchar PROC  NEAR

					  PUSH 				BP
					  MOV 				BP,SP
					  MOV 				DL,[BP+4]
					  MOV 				AH,2
					  INT 				21H
					  MOV 				SP,BP
					  POP 				BP
					  RET
_putchar ENDP
;**********************************************************************
;@paragm: 
_getch PROC  NEAR
					  MOV 				AH,8
					  INT 				21H
					  RET
_getch ENDP
END
