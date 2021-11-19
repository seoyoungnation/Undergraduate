.text
.global matrix         
         
matrix:
	stmfd sp!, {r0-r12,lr}
				
	mov	r6,#0						// r6 = i 					
	mov	r7,#0						// r7 = j 							
	mov	r8,#0						// r8 = k 							
	mov	r9,#0				  		// r9 for sum of multiplications
	
	ldr r5, [r3, #8]				// store ArraySize[2](=v) at r5 
	ldr r4, [r3, #4]			 	// store ArraySize[1](=u) at r4
	ldr r3, [r3]     				// store ArraySize[0](=s) at r3

Loop:			
	add	r11, r0, r6, LSL #2			// access address of A[i]			
	ldr r11, [r11]			
	add	r11, r11, r7, LSL #2 		// access address of A[i][j] 
	
	ldr	r12, [r11]					// store A[i][j] at r12		

	add r11, r1, r7, LSL #2			// access address of B[j]
	ldr r11, [r11]				
	add	r11, r11, r8, LSL #2		// access address of B[j][k]

	ldr	r11, [r11]					// store B[j][k] at r11

	mul	r12, r11, r12				// r12 = A[i][j] * B[j][k] 
	add	r9, r9, r12					// r9 += r12
	
	add	r7, r7, #1					// j++
	cmp	r7, r4						// if (j < u) 		 
	bne	Loop						// goto loop
	mov	r7, #0						// j = 0		

												
	add r11, r2, r6, LSL #2			// access address of C[i]
	ldr r11, [r11]					
	add	r11, r11, r8, LSL #2		// access address of C[i][k]						

	str	r9, [r11]					// C[i][k] = r9
													; 
	mov	r9,#0						// r9 = 0 
	
	add	r8,r8,#1					// k++
	cmp	r8, r5						// if k < v	
	bne	Loop						// goto loop

	mov	r8,#0						// k = 0
	
	add	r6,r6,#1					// i++
	cmp	r6, r3						// if i < s		
	bne	Loop						// goto loop

	ldmfd sp!, {r0-r12,pc}
	
.end
		
		
