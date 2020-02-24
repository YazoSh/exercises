section .bss
	nstring resb 100
	stringp resb 8
section .text	
	global _printRAXint
_printRAXint:
	; sets the pointers up
	mov rbx, stringp
	mov r10, nstring
	mov byte [rbx], 10
	inc rbx 
	; fills the buffer 
	_nprintloop:
	mov rdx, 0
	mov rcx, 10
	div rcx
	add rdx, 48
	mov [rbx], rdx
	inc rbx

	cmp rax, 0
	jnz _nprintloop

	; prints the content of nstring in reverse
	_printloop:
	push rbx
	mov rax, 1
	mov rdi, 1
	mov rsi, rbx 
	mov rdx, 1
	syscall

	pop rbx
	dec rbx
	mov r10, nstring
	cmp r10, rbx
	jne _printloop
	ret
