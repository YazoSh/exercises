; input: rax as a pointer to a char
; prints a null terminated string
section .text
	global _putsRAX
_putsRAX:
	push rax
	mov rbx, 0
_sloop:
	cmp byte [rax], 0	
	jz _eloop
	inc rax 
	inc rbx
	jmp _sloop
_eloop:
	mov rax, 1
	mov rdi, 1
	pop rsi
	mov rdx, rbx
	syscall
	ret
