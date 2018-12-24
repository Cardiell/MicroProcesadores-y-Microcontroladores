DOSSEG
.MODEL tiny
	.CODE
PUBLIC _outportb
PUBLIC _inportb
PUBLIC _putchar
PUBLIC _getch
org 100h

;***********************************************************************
;@paragm: se manda como parametro el puerto y lo recoge DX al igual que 
;		  se manda el dato a desplegar y lo toma AL
_outportb PROC NEAR
					  PUSH 				BP 
					  MOV 				BP,SP 
				      MOV 				DX,[BP+4]
				      MOV 				AL,BYTE PTR[BP+6]
					  OUT 				DX,AL
	 				  MOV 				SP,BP
					  POP 				BP 
					  RET 
_outportb ENDP 
;***********************************************************************
;@paragm: Se manda como parametro el puerto y lo recoge DX
;		  
_inportb PROC NEAR
					  PUSH 				BP 
					  MOV 				BP,SP 
				      MOV 				DX,[BP+4]
					  IN 				AL,DX
	 				  MOV 				SP,BP
					  POP 				BP 
					  RET 
_inportb ENDP 


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