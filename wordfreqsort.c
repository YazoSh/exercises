/*
	sorts ditinct words of input in order of frequency
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct treen{
	struct treen *right;
	struct treen *left;
	char *word;
	int count;
};

struct listn{
	struct listn *next;
	char *word;
	int count;
};

int main()
{
	struct treen *addtree(struct treen *, struct listn *);
	struct listn *addlist(struct listn *, char *);

	void printtree(struct treen *);
	struct treen *listtotree(struct treen *, struct listn *);

	int getword(char *);
	#define MAXWORD 100
	char s[MAXWORD];
	struct listn *lroot = NULL;
	struct treen *troot = NULL;

	/// loads words and counts them
	while(getword(s) != EOF)
		lroot = addlist(lroot, s);
	troot = listtotree(troot, lroot);
	printtree(troot);
}

int length(char *s)
{
	int n = 0;
	while(*s++) n++;
	return n;
}

int ischar(int c)
{
	return (c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z')?1:0;
}

int getword(char *s)
{
	char *t = s; int c;

	while(!ischar(c = getchar()) && c != EOF)
		;

	for(;ischar(*s = c); c = getchar(), s++)
		;

	*s = '\0';
	return (length(t) == 0)?EOF:1;
}

char *strdub(char *s)
{
	char *t = malloc(length(s) * sizeof(char));
	strcpy(t,s);
	return t;
}

struct treen *addtree(struct treen *tn,struct listn *ln)
{
	if(tn == NULL)
	{
		struct treen *nn = malloc(sizeof(struct treen));
		nn->word = ln->word;
		nn->count = ln->count;
		nn->right = nn->left = NULL;
		return nn;
	}
	else if(tn->count <= ln->count)
		 tn->right = addtree(tn->right, ln);
	else tn->left = addtree(tn->left, ln);
	return tn;
}

struct listn *addlist(struct listn *ln, char *s)
{
	if(ln == NULL)
	{
		struct listn *nn = malloc(sizeof(struct listn));
		nn->word = strdub(s);
		nn->count = 1;
		nn->next = NULL;
		return nn;
	}
	else if(!strcmp(s, ln->word))
		(ln->count)++;
	else
		ln->next = addlist(ln->next, s);
	return ln;
}

void printtree(struct treen *tn)
{
	if(tn == NULL)
		return;
	printtree(tn->right);

	printf("\"%s\"\tcount: %d\n", tn->word, tn->count);

	printtree(tn->left);
	free(tn->word);
	free(tn);
}

struct treen *listtotree(struct treen *tn, struct listn *ln)
{
	if(ln == NULL) return NULL;
	struct treen *n = tn = addtree(tn, ln);
	listtotree(tn, ln->next);
	free(ln);
	return n;
}
