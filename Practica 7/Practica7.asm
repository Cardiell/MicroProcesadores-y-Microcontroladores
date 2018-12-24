;------------- definiciones e includes ------------------------------
.INCLUDE "m1280def.inc"
.equ INIT_VALUE = 0x80

;------------- init PORTS -------------------------------------------
ldi R24,INIT_VALUE
out DDRB,R24
;------------- main loop -------------------------------------------
next:
call delay678m
out PINB,R24
rjmp next


delay123:
	ldi R16,2
	nxt:
		ldi R17,244
		nxt2:
			NOP
			dec R17
			brne nxt2
		dec R16
		brne nxt
	ret

delay45m:
		ldi R16,10
		nxt3:
			ldi R17,164
			nxt4:	
				ldi R18,109
				nxt5:
					NOP
					dec R18
					brne nxt5
				dec R17
				brne nxt4
		dec R16
		brne nxt3
	ret


delay678m:
		ldi R16,0
		nxt6:
		LDI R17,103
		nxt7:
			LDI R18,224
			nxt8:
				LDI R19,11
				nxt9:
					NOP
					DEC R19
					BRNE nxt9
				DEC R18
				BRNE nxt8
			NOP
			DEC R17
			BRNE nxt7
		DEC R16
		BRNE nxt6
	ret
