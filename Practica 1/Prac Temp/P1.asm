   
.model tiny

   ;----- Insert INCLUDE "filename" directives here
   ;----- Insert EQU and = equates here
   
   locals
   
.data
      
      Mens       DB  'Hola Mundo',10,13,0


.code
             org 100h
	
;*************************************************************
;  Procedimiento principal
;*************************************************************	
  principal proc
            mov sp,0fffh			; inicializa SP (Stack Pointer)
									
  @@sigue:		
            mov  al,'x'
			call putchar
			jmp @@sigue
			
			ret						; nunca se llega aqui
			endp

			
;***************************************************************
;  procedimientos
;***************************************************************            
    putchar	proc
			push ax
			push dx
			mov dl,al
			mov ah,2				; imprimir caracter DL
			int 21h					; usando servico 2 (ah=2)
			pop dx					; del int 21h
			pop ax
			ret
			endp

end   principal              ; End of program 