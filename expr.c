/*
	Turns a post-fix expression into an in-fix expression

	Usage: ./expr <post-fix expression>
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OPRAND 0
#define OPERATOR 1

//where the magic happenes
int main(int argc,char *argv[])
{
	int type(char *s);
	char *expcat(char *opr1,char *opr2,char operator);

	//string stack functions
	void spush(char *s);
	char *spop();

	char *tmp;
	while(--argc)
		switch(type(*++argv))
		{
			case OPRAND:						//postfix: (1 + 2) * (4 + 5)
				spush(*argv);
				break;
			case OPERATOR:
				tmp = spop();
				spush(expcat(spop(),tmp,**argv));
				break;
			default:
				printf("Invalid operation!!\n");
				goto end;
		}
	char *s;
	while((s = spop()))
		printf("%s\n",s);
	end:
	return 0;
}

//returns the type of the content in a string
int type(char *s)
{
	int isnum(char *s);
	if(isnum(s))
		return OPRAND;
	else if(*s == '+' || *s == '-' || *s == '*' || *s == '/')
		return OPERATOR;
	else return -1;
}	

#include <ctype.h>

//checks if a string is a valid number
int isnum(char *s)
{	
	int c;
	if(*s == '-')
		s++;
	while((c = *s++))
		if(c == '.')
			goto ifFraction;
		else if(!isdigit(c))
			return 0;
	return 1;
	ifFraction:
	while((c = *s++))
		if(!isdigit(c))
			return 0;
	return 1;
}

int length(char* s);

//concatenates two strings and a charectar to form a mathmatical term
char *expcat(char *opr1,char *opr2,char operator)
{
	if(!opr1 || !opr2)
		return NULL;
	//(1 + 2)
	char *alloc(int n);
	#define EXTRA 6 //adds space for the braces, extra spaces and the null char
	int n = EXTRA + length(opr1) + length(opr2);
	char *p = alloc(n);
	char *s = p;
	*p++ = '(';
	strcat(p,opr1);p += length(opr1);
	*p++ = ' ';
	*p++ = operator;
	*p++ = ' ';
	strcat(p,opr2);p += length(opr2);
	*p++ = ')';
	*p = '\0';
	return s;
}

//returns the length of a given string
int length(char* s)
{
	int n = 0;
	while(*s++)
		n++;
	return n;
}

#define MAXSTACK 100

//string stack
char *Sstack[MAXSTACK]; 
char **Sstackp = Sstack;
char *alloc(int n);

void spush(char *s)
{
	int n = length(s)+1;
	char *p = alloc(n);
	strcpy(p,s);
	*Sstackp++ = p; 
}

char *spop()
{
	if(*Sstackp == *Sstack)
		return NULL;
	return *--Sstackp;
}
//

//storage allocator
#define MAXBUFFER 1000
char buffer[MAXBUFFER];
char *bufferp = buffer;

char *alloc(int n)
{
	if(buffer + MAXBUFFER - bufferp >= n)
	{
		bufferp += n;
		return bufferp - n;
	}
	else
		return 	NULL;
}
//
