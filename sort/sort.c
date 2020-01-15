/* 
	sorts lines of text from standered input 
	uses the quick sort algorithm
	you can use www.generatedata.com to get test data 
*/

#include <stdio.h>
#include <string.h>

#define MAXLINES 5000 //max numeber of inpute lines
#define MAXLEN 1000 //max length for each input line

char *lineptr[MAXLINES];

int readlines(char *lineptr[],char buffer[]);
void writelines(char *lineptr[],int nlines);

void qsort();

int main(void)
{
	#define MAXBUFF (MAXLINES * MAXLEN)
	char buffer[MAXBUFF];
	int nlines;

	if((nlines = readlines(lineptr,buffer)) >= 0)
	{
		qsort(lineptr,0,nlines-1);
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

char *alloc(int n);

int readlines(char *lineptr[],char buffer[])
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
void qsort(char *a[],int left,int right)
{
	if(left >= right)
		return;

	void swap(char **a,char **b);

	swap(&a[(left+right)/2],&a[left]);
	int last = left;
	for(int i = last+1;i <= right;i++)
		if(strcmp(a[i],a[left]) < 0)  //a[i] < a[left]
			swap(&a[i],&a[++last]);

	swap(&a[last],&a[left]);
	qsort(a,left,last -1);
	qsort(a,last+1,right);
}

void swap(char **a,char **b)
{
	char *tmp = *a;
	*a = *b;
	*b = tmp;
}
