; ce programme est pour l'assembleur RealView (Keil)
	thumb
	import TabCos
	import TabSin
	export module_carre
;
	area  moncode, code, readonly
N equ 63
;
		
module_carre proc
	; ro = @Signal
	; r1 = k
	
	push { r4, r5, r6, r7, r8, r9, r10, r11, lr }
	ldr r2, =TabCos ; r2 = @TabCos
	ldr r3, =TabSin ; r3 = @TabSin
	ldr r4, =N ; r4 = N
	movw r5, #0 ; r5 = i
	mov r6, #0 ; r6 = somme_reel
	mov r7, #0 ; r7 = somme_imaginaire

for
	mul r8, r5, r1 ; r8 = ik
	AND r8, r4 ; r8 = ik%N
	ldrsh r9, [r2, r8, lsl #1] ; r9 = cos(ik%N)
	ldrsh r10, [r3, r8, lsl #1] ; r10 = sin(ik%N)
	ldrsh r11, [r0, r5, lsl #1] ; r11 = x(i)
	mla r6, r9, r11, r6
	mla r7, r10, r11, r7
	
	add r5, #1
	cmp r5, r4
	bls for ; r5 <= r4
	
	smull r11, r6, r6, r6 ; r11,r6 = r6*r6 = Re(k)^2
	smlal r11, r6, r7, r7 ; (r11,r6 += r7*r7) = Re(k)^2 + Im(k)^2
	mov r0, r6 
	pop { r4, r5, r6, r7, r8, r9, r10, r11, pc }
	endp

	end