section .data
	string db "hello there",10,0
section .text
	global _start
_start:
	mov rax, string
	call _putsRAX

	mov rax, 60
	mov rdi, 0
	syscall
	
; input: rax as a pointer to a char
; prints a null terminated string
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
