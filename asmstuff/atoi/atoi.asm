	global _atoiRAX
_atoiRAX:
	mov rbx, rax	
	mov rax, 0
	
	_sloop:
	mov r9b, byte [rbx]
	cmp r9b, 0
	jz _eloop
	cmp r9b, 48
	jl _eloop
	cmp r9b, 57
	jg _eloop
	
	mov r10b, r9b 
	sub r10, 48
	mov r11, 10
	mul r11
	add rax, r10
	
	inc rbx
	jmp _sloop
	_eloop:
	ret
