#include <stdio.h>

#include "stack.h"

int push(stack *stack, int n)
{
	if(stack->top < stack->size)
	{
		stack->buffer[stack->top++] = n;
		return 0;
	}
	return -1;
}

int pop(stack *stack)
{
	if(stack->top > 0)
	{
		return stack->buffer[(stack->top--) - 1];
	}
	fputs("Error: Stack is empty\n", stderr);
	return 0;
}

int peek(stack *stack, int pos)
{
	if(pos < 0)
		return -1;
	if(pos >= stack->top)
		return 0;

	return stack->buffer[pos];
}
