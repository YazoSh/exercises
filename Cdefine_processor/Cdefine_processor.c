/*
	a simple version of the #define C precessor
	processes #define and #undef lines and replaces tokens accordingly
	Usage:	#define name replacment_text
		#undef	name
	compile and run with ./a.out < file.c > out.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct tablen{
	struct tablen *next;
	char *name;
	char *defn;
}tablen;

#define HASHSIZE 10
tablen *hashtable[HASHSIZE];

int hash(char *s)
{
	unsigned int hashval = 0;
	while(*s++)
		hashval += (*s - 'a');
	return hashval % HASHSIZE;
}

tablen *lookup(char *name)
{
	tablen *trav = hashtable[hash(name)];
	while(trav)
		if(!strcmp(trav->name, name))
			return trav;
		else trav = trav->next;
	return NULL;
}

tablen *install(char *name, char *defn)
{
	char *strdub(char *s);

	tablen *np;
	unsigned hashval;
	if((np = lookup(name)) == NULL)
	{
		np = malloc(sizeof(tablen));
		if(np == NULL || (np->name = strdub(name)) == NULL)
			return NULL;
		hashval = hash(name);
		np->next = hashtable[hashval];
		hashtable[hashval] = np;
	}
	else
		free(np->defn);
	if((np->defn = strdub(defn)) == NULL)
		return NULL;
	return np;
}

int undefn(char *s)
{
	tablen *np, *tmp;
	int hashval;
	if((np = hashtable[hashval = hash(s)]) == NULL)
		return 1;
	if(!strcmp(np->name, s))
	{
		hashtable[hashval] = np->next;
		free(np->name);
		free(np->defn);
		free(np);
		return 0;
	}
	else
		while(np->next)
			if(!strcmp(np->next->name, s))
			{
				tmp = np->next;
				np->next = np->next->next;
				free(tmp->name);
				free(tmp->defn);
				free(tmp);
				return 0;
			}
	return 1;
}

int length(char *s)
{
	int n = 0;
	while(*s++) n++;
	return n;
}

char *strdub(char *s)
{
	char *t = malloc(sizeof(char) * length(s) + 1);
	strcpy(t, s);
	return t;
}

void freelist(tablen *n)
{
	if(n)
	{
		freelist(n->next);
		free(n->name);
		free(n->defn);
		free(n);
	}
}

void freetable()
{
	for(int i = 0; i < HASHSIZE;i++)
		freelist(hashtable[i]);
}

//
//
//

#define MAXWORD 100
#define MAXLINE 1000
#define MAXCOMM 10

int _getline(char *s)
{
	int c;
	if((c = getchar()) == EOF)
		return c;

	for(*s++ = c; (c = getchar()) != '\n' && c != EOF; *s++ = c)
		;
	*s = '\0';
	return 0;
}

int notspace(int c)
{
	return !isspace(c);
}

//extarcts the first word from a line and returns the new line index pointer
char *firstword(char *linep, char *wordbuff, int includesymbols)
{
	int (*filter)(int) = (includesymbols)? notspace: isalnum;
	while(!filter(*linep) && *linep != '\0')
		linep++;

	while(filter(*linep) && *linep != '\0')
		*wordbuff++ = *linep++;
	*wordbuff = '\0';
	return linep;
}

char *wordcat(char *line, char *word)
{
	while(*line = *word)
		line++,word++;
	return line;
}

char firstchar(char *s)
{
	while(isspace(*s) && *s != '\0')
		s++;
	return *s;
}

int processline(char *line)
{
	int getlineval;
	char word[MAXWORD], defn[MAXWORD], outline[MAXLINE], *linep, *outlinep;
	if((getlineval = _getline(line)) == EOF)
		return getlineval;
	linep = line;
	outlinep = outline;

	if(firstchar(linep) == '#')
	{
		linep = firstword(linep, word, 0);
		if(!strcmp(word, "define"))
		{
			linep = firstword(linep, word, 0);
			linep = firstword(linep, defn, 1);

			install(word, defn);
			*line = '\0';
		}
		else if(!strcmp(word, "undef"))
		{
			linep = firstword(linep, word, 0);
			undefn(word);
			*line = '\0';
		}
		else
		{
			strcpy(outline, line);
			strcat(outline, "\n\0");
			strcpy(line, outline);
		}
	}
	else
	{
		while(*linep)
		{
			while(!isalnum(*linep) && *linep != '\0')
				*outlinep++ = *linep++;

			linep = firstword(linep, word, 0);
			tablen *defen;
			if((defen = lookup(word)))
				outlinep = wordcat(outlinep, defen->defn);
			else outlinep = wordcat(outlinep, word);
		}
		*outlinep++ = '\n';
		*outlinep = '\0';
		strcpy(line, outline);
	}
	return getlineval;
}

int main()
{
	char line[MAXLINE];
	while(processline(line) != EOF)
		printf("%s",line);
	freetable();
	return 0;
}
