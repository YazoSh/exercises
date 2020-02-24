section .data
	promt db "Enter your name: " ;17
	hello db "Hello " ;6
section .bss
	buf resb 16
section .text
	global _start
_start:
	mov rax, 1
	mov rdi, 1
	mov rsi, promt
	mov rdx, 17
	syscall

	mov rax, 0
	mov rdi, 0
	mov rsi, buf
	mov rdx, 16	
	syscall

	mov rax, 1
	mov rdi, 1
	mov rsi, hello
	mov rdx, 6
	syscall

	mov rax, 1
	mov rdi, 1
	mov rsi, buf
	mov rdx, 16
	syscall
	
	mov rax, 60
	mov rdi, 69
	syscall
