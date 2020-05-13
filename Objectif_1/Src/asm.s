; ce programme est pour l'assembleur RealView (Keil)
	thumb
	import TabCos
	import TabSin
	export somme_carres
	export module_carre
;
	area  moncode, code, readonly
N equ 63
;

somme_carres proc
	; r0 = indice d'un angle d'entrée dans la table
	
	ldr r1, =TabCos
	ldr r2, =TabSin
	ldrsh r3, [r1, r0, lsl #1]
	ldrsh r12, [r2, r0, lsl #1]
	mul r3, r3
	mul r12, r12
	add r3, r12
	mov r0, r3
	bx lr
	endp
		
calcul_partie proc
	; r0 = @Signal
	; r1 = k
	; r2 = @TabCos ou @TabSin
	
	push { r4, r5, r6, r7, r12, lr }
	ldr r4, =N ; r4 = N
	mov r6, #0 ; r6 = i
	mov r7, #0 ; r7 = somme

for
	mul r12, r6, r1 ; r12 = ik
	AND r12, r4 ; r12 = ik%N
	ldrsh r3, [r2, r12, lsl #1] ; r3 = cos(ik%N) ou sin(ik%N)
	ldrsh r5, [r0, r6, lsl #1] ; r5 = x(i)
	mul r5, r3
	
	add r7, r5
	add r6, #1
	
	cmp r6, r4
	bls for ; r6 <= r4
	
	mov r0, r7
	pop { r4, r5, r6, r7, r12, pc }
	endp

module_carre proc
	; ro = @Signal
	; r1 = k
	
	push { r4, r11, lr }
	mov r4, r0 ; Sauvegarde de r0 dans r4
	ldr r2, =TabCos ; r2 = @TabCos
	bl calcul_partie ; r0 = Re(k)
	smull r11, r12, r0, r0 ; r11,r12 = r0*r0 = Re(k)^2
	mov r0, r4 
	ldr r2, =TabSin ; r2 = @TabSin
	bl calcul_partie ; r0 = Im(k)
	smlal r11, r12, r0, r0 ; (r11,r12 += r0*r0) = Re(k)^2 + Im(k)^2
	mov r0, r12 
	pop { r4, r11, pc }
	endp

	end