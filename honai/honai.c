/*
 	Honai Tower problem calculator 
	Calculates number of stebs as well as instructions for each step

	Compile with make
	Usage: ./honai DISCS
*/
#include <stdio.h>
#include <stdlib.h>

#include "stack.h"

stack *stacks[3];

int printtower(void)
{
	// Assumes that all stacks are the same size
	int height = stacks[0]->size;

	extern stack *stack[];
	int stacki = 0;

	for(int y = height; y >= 0; y--)
	{
		for(int x = 0; x < 3; x++)
		{
			int disc = peek(stacks[stacki++ % 3], y);
			printf(disc?"    %d":"    |", disc);
		}
		putchar('\n');
	}
	puts("    -----------");
	puts("    A    B    C\n\n");
}

int steps = 0;

int mov_honai(int discs, stack *src, stack *sup, stack *dist)
{
	extern int steps;
	if(discs > 0)
	{
		mov_honai(discs - 1, src, dist, sup);

		printtower();

		steps++;
		register int disc;
		disc = pop(src);
		push(dist, disc);

		mov_honai(discs -1, sup, src, dist);
	}
	return 0;
}

int honai(int discs)
{
	struct stack A, B, C;

	A.buffer = malloc(sizeof(int) * discs);
	A.size = discs;
	stacks[0] = &A;
	
	B.buffer = malloc(sizeof(int) * discs);
	B.size = discs;
	stacks[1] = &B;

	C.buffer = malloc(sizeof(int) * discs);
	C.size = discs;
	stacks[2] = &C;

	A.top = B.top = C.top = 0;

	for(int i = 0; i < discs; i++)
		push(&A, discs - i);

	extern int steps;
	steps = 0;
	mov_honai(discs, &A, &B, &C);

	printtower();

	printf("steps %d\n\n", steps);
}

int main(int argc, char **argv)
{
	if(argc != 2)
	{
		fputs("Error: syntax\n./honai DISCS\n", stderr);
		return 1;
	}
	int discs;
	sscanf(argv[1], "%d", &discs);

	honai(discs);
}
