#ifndef STACK
#define STACK

struct stack {
	int size;
	int top;
	int *buffer;
};

typedef struct stack stack;

int push(stack *stack, int n);

int pop(stack *stack);

int peek(stack *stack, int pos);

#endif
