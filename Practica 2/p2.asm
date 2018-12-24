DOSSEG
.MODEL TINY
	.CODE
	ORG 100H
PUBLIC _putchar
PUBLIC _getchar

;***********************************************************************
;@paragm: se mada como parametro el caracter a imprimir y lo recoge
;		  DL para su previa impresion
_putchar PROC  NEAR

					  PUSH 				BP
					  MOV 				BP,SP
					  MOV 				DL,[BP+4]
					  MOV 				AH,2
					  INT 				21H
					  POP 				BP
					  RET
_putchar ENDP
;**********************************************************************
;@paragm: 
_getchar PROC  NEAR
					  MOV 				AH,8
					  INT 				21H
					  RET
_getchar ENDP

END


