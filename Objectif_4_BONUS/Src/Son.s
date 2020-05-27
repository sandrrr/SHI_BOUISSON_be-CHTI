	thumb
	include etat.inc
	export timer_callback
	import etat
		
	area moncode, code, readonly
TIM3_CCR3	equ	0x4000043C	; adresse registre PWM


timer_callback proc
	push {r4, r5}
	ldr r0, =etat ; r0 = etat
	ldr r1, [r0, #E_POS] ; r1 = etat.position
	ldr r2, [R0, #E_TAI] ; r2 = etat.taille
	ldr r3, [r0, #E_RES] ; r3 = etat.resolution
	ldr r4, [r0, #E_SON] ; r4 = etat.son
	ldr r5, =TIM3_CCR3 ; r5 = @PWM
	cmp r1, r2
	beq fin ; r1 == r2
	
read ; r1 < r2
	ldrsh r12, [r4, r1, lsl #0x1] ; r12 = etat.son[etat.position]
	
	mul r12, r3 ; on multiplie par la résolution
	asr r12, #16 ; on ramène entre -360 et 360
	add r12, #360 ; on ramène entre 0 et 720
	
	add r1, #1 ; on incrémente la position
	str r1, [r0, #E_POS] ; on store dans la structure
	str r12, [r5] ; on store l'échantillon dans l'@ du PWM
	
fin ; r1 == r2
	pop {r4, r5}
	bx lr
	endp

	end