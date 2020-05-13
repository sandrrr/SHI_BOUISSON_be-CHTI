	thumb
	export timer_callback
	
	area mesdata, code, readwrite
	export cmpt
cmpt dcd 0
		
	area moncode, code, readonly
GPIOB_BSRR	equ	0x40010C10	; Bit Set/Reset register

timer_callback proc
	ldr	r3, =GPIOB_BSRR
	ldr	r2, =cmpt
	ldr	r0, [r2]
	cbz 	r0, load_one
; mise a zero de PB1
load_zero
	mov	r1, #0x00020000
	mov 	r0, #0
	str	r0, [r2]
	b 	set
; mise a 1 de PB1
load_one
	mov	r1, #0x00000002
	mov 	r0, #1
	str	r0, [r2]
set
	str	r1, [r3]
; N.B. le registre BSRR est write-only, on ne peut pas le relire
	bx lr
	endp

	end