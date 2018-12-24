DOSSEG
.MODEL TINY
	.CODE
	ORG 100H
PUBLIC _pokeb
PUBLIC _putchar
PUBLIC _pokew

org 100h

;----------------------------------------------------------------------------------
_pokeb PROC NEAR
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
_pokeb ENDP 



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
;*************************************************************************
_pokew PROC NEAR
					PUSH 		BP 
					MOV 		BP,SP 
				    MOV 		DX,[BP+4] ; Segmento
				    MOV 		BX,[BP+6] ; Offset
				    MOV 		AX,[BP+8] ; Dato
					PUSH 		DS
					MOV 		DS,DX
					MOV 		[BX],AX
				    POP 		DS
				    MOV			SP,BP
					POP 		BP 
					RET
_pokew ENDP 

END
