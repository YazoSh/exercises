section .data
	num db "257",0
section .bss
	strbuff resb 100
section .text
	global _start
_start:
	mov rax, num
	call _atoiRAX

	mov rdi, rax
	mov rax, 60 
	syscall
	
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
