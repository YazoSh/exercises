/* 
	a calculator for simple post-fix math expressions like "(3 - 2) * (5 + 7)"\
	are entered like "3 2 - 5 7 + *".
	also supports the use of these Trigonometric functions (sin,cos,tan),\
	used as in "sin 1" where "10" is in radians,
	and (exp,pow) use as "exp 10" and "pow 3 2".
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>


#define MAXOP 100
#define NUMBER 0
#define MATHFUNCTION -2

int getop(char []);
void push(double);
double pop(void);
void math_function(char *);

char s[MAXOP];

//reverse Polish calculator
int main()
{
	int type;
	double op2;

	while((type = getop(s)) != EOF)
	{
		switch(type)
		{
			case NUMBER:
				push(atof(s));
				break;
			case MATHFUNCTION:
				math_function(s);
				break;	
			case '+':
				push(pop() + pop());
				break;
			case '*':
				push(pop() * pop());
				break;
			case '-':
				op2 = pop();
				push(pop() - op2);
				break;
			case '/':
				op2 = pop();
				if(op2 == 0)
				{
					printf("error zero division");
					break;
				}
				push(pop() / op2);
				break;
			case '%':
				op2 = pop();
				if(op2 == 0)
				{
					printf("error zero division");
					break;
				}
				push((int)pop() % (int)op2);
				break;
			case '\n':
				printf("\t%.8g\n",pop());
				break;
			default:
				printf("Unkown command!\n");
				break;
		}
	}
}

#define MAXVAL 100

#define SIN 0
#define COS 1
#define TAN 2
#define EXP 3
#define POW 4

int getch(void);
int getch(void);
void ungetch(int);
int ismath(char *);
int ischar(int);
int isign(int);

int sp = 0;
double val[MAXVAL];

//pushes f into the stack
void push(double f)
{
	if(sp < MAXVAL)
		val[sp++] = f;
	else
		printf("stack is full!\n");

    for(int i = 0;i < sp;i++)
    	printf("%g ", val[i]);
    printf("#\n");
}

//pops from the stack
double pop(void)
{
	if(sp > 0)
		return val[--sp];
	else
	{
		printf("stack is empty! %i\n",sp);
		return 0.0;
	}
}

//gets the next oprand or number
int getop(char s[])
{
	int i = 0;
	int c,sign;

	//skips blanks and taps
	while((s[0] = c = getch()) == ' ' || c == '\t' )
		;
	s[1] = '\0';


	//returns c if its an oprand
	if(!isdigit(c) && c != '.' && isign(c) && !ischar(c))
		return c;

	//collect the sign
	if(c == '-')
	{
		c = s[++i] = getch();
	}
	
	//collect the math function
	if(ischar(c))
	{
		while(ischar(s[++i] = c = getch()))
			;
		s[i] = '\0';
		return MATHFUNCTION;
	}


	//collect integer part
	if(isdigit(c))
		while(isdigit(s[++i] = c = getch()))
			;

	//collect fraction part
	if(c == '.')
		while(isdigit(s[++i] = c = getch()))
			;

	s[i] = '\0';

	if(c != EOF)
		ungetch(c);
	return 	NUMBER;
}

int ismath(char *s)
{
	if(!strcmp(s,"sin") || !strcmp(s , "SIN"))
		return SIN;
	if(!strcmp(s,"cos") || !strcmp(s , "COS"))
		return COS;
	if(!strcmp(s,"tan") || !strcmp(s , "TAN"))
		return TAN;
	if(!strcmp(s,"exp") || !strcmp(s , "EXP"))
		return EXP;
	if(!strcmp(s,"pow") || !strcmp(s , "POW"))
		return POW;
	return -1;
}

int ischar(int c)
{
	return (c >= 'a' && c <= 'z')?1:0;
}


void math_function(char *t)
{
	int func;
	double s2;
	if((func = ismath(t)) == -1)
	{
		printf("Unkown command!!!\n");
		return;
	}
	if(getop(s) != NUMBER)
	{
		printf("Unkown command!!!\n");
		return;
	}
	switch(func)
	{
		case SIN:
			push(sin(atof(s)));
			break;
		case COS:
			push(cos(atof(s)));
			break;
		case TAN:
			push(tan(atof(s)));
			break;
		case EXP:
			push(exp(atof(s)));
			break;
		case POW:
			s2 = atof(s);
			getop(s);
			push(pow(s2,atof(s)));
			break;
	}
	return;
}


int isign(int c)
{
	if(c != '-')
		return 1;

	c = getch();
	ungetch(c);
	return (isdigit(c))?0:1;
}

#define BUFFSIZE 100

char buf[BUFFSIZE];
int bufp = 0;

//gets a possibly pushed back charecter
int getch(void)
{
	return (bufp > 0)? buf[--bufp] : getchar();
}

//pushes a charecter back to input
void ungetch(int c)
{	
	if(bufp >= BUFFSIZE)
		printf("buffer is full!\n");
	else
		buf[bufp++] = c;
}
