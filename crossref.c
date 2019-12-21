/*
	Loads all input words into a binary tree and outputs a list of line numbers on which they occur
	but ignores some of the english noise words, not all of them cause i couldnt find a full list of them
	
	compile and run with ./a.out < "file"
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXWORD 100

// a list of some english noise words that will be filterd when encountered
char *noisewords[] = {"the","as","so","also","in","to",
 		      "a","of","therefore","thus","and"
 		      "for","too","will","since","is","he",
  		      "she","it"};

// Structers used for handling data
struct lnode{
	struct lnode *next;
	int line;
};

struct tnode{
	char *word;
	struct lnode *lines;

	struct tnode *right;
	struct tnode *left;
};
//

int getword(char *s);

int currline = 1;

int main()
{
	struct tnode *inserttnode(struct tnode *tn,char *word,int line);
	void printtree(struct tnode *n);
	void freetree(struct tnode *t);
	int isnoiseword(char *);

	char word[MAXWORD];
	int line;
	struct tnode *root = NULL;

	while((line = getword(word)) > 0)
		if(!isnoiseword(word))
			root = inserttnode(root,word,line);

	printtree(root);
	freetree(root);
}

int ischar(int c)
{
	return (c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z')?1:0;
}

int getword(char *s)
{
	int length(char *s);

	char *t = s; int c;
	while(!ischar(c = getchar()) && c != EOF)
		if(c == '\n') currline++;

	for(;ischar(*s = c); c = getchar(),s++)
		;

	*s = '\0';
	return ((c == '\n')?currline++:((c == EOF)?((length(t) == 0)?EOF:currline):currline));
}

#include <ctype.h>

int fstrcmp(char *s, char *t)
{
	while(*s)
		if(tolower(*s++) != tolower(*t++)) break;
	return *--s - *--t;
}

int isnoiseword(char *s)
{
	for(int i = 0; i < (sizeof noisewords / sizeof noisewords[0]); i++)
		if(!fstrcmp(s, noisewords[i]))
			return 1;
	return 0;
}

// Handles inserting words into the linked list
struct lnode *insertlist(struct lnode *t,int line)
{
	if(t != NULL)
	{
		t->next = insertlist(t->next,line);
		return t;
	}

	struct lnode *nn = NULL;
	if((nn = (struct lnode *)malloc(sizeof(struct lnode))) == NULL)
		return NULL;

	nn->line = line;
	nn->next = NULL;

	return nn;
}

int length(char *s)
{
	int len = 0;
	while(*s++ != '\0') len++;
	return len;
}

char *strdub(char *word)
{
	char *s = malloc(sizeof(char) * length(word) + 1);
	if(s == NULL)
	{
			perror("no enough memory!\n");
			return NULL;
	}
	strcpy(s, word);
	return s;
}

struct tnode *inserttnode(struct tnode *tn,char *word,int line)
{
	if(tn == NULL)
	{
		struct tnode *nn = (struct tnode *)malloc(sizeof(struct tnode));
		if(nn == NULL)
			perror("No enough memory left!\n");
		nn->lines = insertlist(nn->lines,line);
		nn->word = strdub(word);
		nn->left = nn->right = NULL;
		return nn;
	}

	int strcmpval;
	if((strcmpval = strcmp(tn->word, word)) == 0)
		insertlist(tn->lines, currline);
	else if(strcmpval < 0)
		tn->right = inserttnode(tn->right, word, line);
	else
		tn->left = inserttnode(tn->left, word, line);
	return tn;

}

void printlist(struct lnode *n)
{
	putchar('[');
	while(n != NULL)
	{
		printf("%d, ",n->line);
		n = n->next;
	}
	puts("\b\b]");
}

void printtree(struct tnode *n)
{
	if(n == NULL)
		return;
	printtree(n->left);

	printf("\"%s\"\tlines:", n->word);
	printlist(n->lines);

	printtree(n->right);
}

void freelist(struct lnode *n)
{
	if(n == NULL)
		return;
	freelist(n->next);
	free(n);
}

void freetree(struct tnode *t)
{
	if(t == NULL)
		return;
	freetree(t->left);
	freetree(t->right);
	free(t->word);
	freelist(t->lines);
	free(t);
}
