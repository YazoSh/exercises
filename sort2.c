/* 
	sorts lines of text from standered input 
	uses the quick sort algorithm
	
	Usage ./sort [OPTIONS]...

	Ordering options:

	-n 
		compare according to string numerical value

	-r 
		sort lines in reverse

	-d
		consider only blanks and alphanumeric characters

	-f
		fold lower case to upper case characters

	--field n
		sorts lines to the nth field

	-delimiter-char c
		sepecifies the delimiter character default is '\t'
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINES 5000 //max numeber of inpute lines
#define MAXLEN 1000 //max length for each input line

char *lineptr[MAXLINES];

int readlines(char *lineptr[],char buffer[]);
void writelines(char *lineptr[],int nlines);

void qsort_(char *a[],int left,int right,int reverse,int dir_order,
			int fieldsort,int field,char delimiter_char,
			int (*comp)(void *,void *,int,int,int,char));
int numcmp(char *s1,char *s2,int dir_order,int fieldsort,int field,char delimiter_char);
int strfcmp(char *s1,char *s2,int dir_order,int fieldsort,int field,char delimiter_char);
int strCmp(char *s1,char *s2,int dir_order,int fieldsort,int field,char delimiter_char);
int isnum(char *s);
int length(char *s);

int main(int argc ,char *argv[])
{

	int c,numerical = 0,reverse = 0,fold = 0,dir_order = 0,fieldsort = 0,field = 0;
	char delimiter_char = '\t';

	while(--argc && (*++argv)[0] == '-')
	{	
		while((c = *++argv[0]))
			switch(c)
				{
					case 'n':
						numerical = 1;
						break;
					case 'r':
						reverse = 1;
						break;
					case 'f':
						fold = 1;
						break;
					case 'd':
						dir_order = 1;
						break;
					case '-':
						if(!strcmp(*argv,"-field"))
						{
							fieldsort = 1;
							if(--argc && isnum(*++argv))
							{
								field = atoi(*argv);
								break;
							}
						}
						else if(!strcmp(*argv,"-delimiter-char"))
						{
							if(--argc && length(*++argv) == 1)
							{
								delimiter_char = *argv[0];
								break;
							}
						}
					default:
						printf("Unkown argument!!\n");
						return 1;
				}
	}
	#define MAXBUFF (MAXLINES * MAXLEN)
	char buffer[MAXBUFF];//allocates storage to store lines of text
	int nlines;

	if((nlines = readlines(lineptr,buffer)) >= 0)
	{
		qsort_((void *)lineptr,0,nlines-1,reverse,dir_order,
			fieldsort,field,delimiter_char,
			(int (*)(void *,void *,int,int,int,char))
			(numerical? numcmp :(fold?strfcmp : strCmp)));
		writelines(lineptr,nlines);
	}
	else
	{
		printf("Error ,input is too big\n");
		return 1;
	}
}

int getlinE(char *s) //reads input line by line
{
	int i,c;
	for(i = 0; i<MAXLEN-1 && (c = getchar()) != EOF && c != '\n';i++)
		s[i] = c;

	if(c == '\n')
		s[i++] = c;
	s[i] = '\0';

	return i;
}

int readlines(char *lineptr[],char buffer[]) //reads all lines on input and stores them in the buffer
{
	int nlines = 0,len;
	char line[MAXLEN], *bufferp = buffer;
	while((len = getlinE(line)) > 0)
		if(nlines >= MAXLINES || ((buffer + MAXBUFF - bufferp) < len))
			return -1;
		else
		{
			line[len-1] = '\0';
			strcpy(bufferp,line);
			lineptr[nlines++] = bufferp;
			bufferp += len;
		}
	return nlines;
}

void writelines(char *lineptr[],int nlines)
{
	while(nlines-- > 0)
		printf("%s\n", *lineptr++);
}

//the sorting algorithm
void qsort_(char *a[],int left,int right,int reverse,int dir_order,
			int fieldsort,int field,char delimiter_char,
			int (*comp)(void *,void *,int,int,int,char))
{
	if(left >= right)
		return;

	void swap(void **a,void **b);

	swap((void *)&a[(left+right)/2],(void *)&a[left]);
	int last = left;
	for(int i = last+1;i <= right;i++)
		if(reverse)
		{
			if((*comp)(a[i],a[left],dir_order,fieldsort,field,delimiter_char) > 0)
				swap((void *)&a[i],(void *)&a[++last]);
		}
		else
			if((*comp)(a[i],a[left],dir_order,fieldsort,field,delimiter_char) < 0)
				swap((void *)&a[i],(void *)&a[++last]);


	swap((void *)&a[last],(void *)&a[left]);
	qsort_(a,left,last -1,reverse,dir_order,fieldsort,field,delimiter_char,(*comp));
	qsort_(a,last+1,right,reverse,dir_order,fieldsort,field,delimiter_char,(*comp));
}

#include <ctype.h>

int isdir(int c)//checks if a given character is not a symbole
{
	return (tolower(c) >= 'a' && tolower(c) <= 'z'|| 
		isdigit(c) || c == ' ')? 1:0;
}

void skiptofield(char **s1,char **s2,int field,char delimiter_char);

int numcmp(char *s1,char *s2,int dir_order,int fieldsort,int field,char delimiter_char)
{
	if(fieldsort)
		skiptofield(&s1,&s2,field,delimiter_char);

	double n1 = atof(s1);
	double n2 = atof(s2);

	if(n1 > n2)
		return 1;
	else if(n1 < n2)
		return -1;
	else
		return 0;
}

int strCmp(char *s1,char *s2,int dir_order,int fieldsort,int field,char delimiter_char)
{
	if(fieldsort)
		skiptofield(&s1,&s2,field,delimiter_char);
	while(*s1 && *s2)
		if(!isdir(*s1) && dir_order)
			s1++;
		else if(!isdir(*s2) && dir_order)
			s2++;
		else if(*s1 != *s2)
			return *s1 - *s2;
		else s1++,s2++;
	return 0;
}

int strfcmp(char *s1,char *s2,int dir_order,int fieldsort,int field,char delimiter_char)
{
	if(fieldsort)
		skiptofield(&s1,&s2,field,delimiter_char);

	while(*s1 && *s2)
		if(!isdir(*s1))
			s1++;
		else if(!isdir(*s2))
			s2++;
		else if(tolower(*s1) != tolower(*s2))
			return tolower(*s1) - tolower(*s2);
		else s1++,s2++;
	return 0;
}

void swap(void **a,void **b)
{
	void *tmp = *a;
	*a = *b;
	*b = tmp;
}

int isnum(char *s)
{
	int c;
	while((c = *s++))
		if(!isdigit(c))
			return 0;
	return 1;
}

int length(char *s)
{
	int n = 0;
		while(*s++)
			n++;
	return n;
}

void skiptofield(char **s1,char **s2,int field,char delimiter_char)//moves the string pointer to the beginning
{																   //of the wanted field
	int i;
	for(i = 1;i < field;i++)
	{
		while(*(*s1)++ != '\0' && **s1 != delimiter_char)
			;
		while(**s1 == delimiter_char)
			*(*s1)++;

		while(*(*s2)++ != '\0' && **s2 != delimiter_char)
			;
		while(**s2 == delimiter_char)
			*(*s2)++;
	}
}
