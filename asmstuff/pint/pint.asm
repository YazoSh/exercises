section .bss
	buff resb 100
section .text
	global _start
_start:
	
_printRAXint:
	_spintloop:
	mov rdx, 0
	cmp rax, 0
	jz _epintloop
	
	:
	_epintloop:
