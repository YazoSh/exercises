#include <stdio.h>
#include <stdarg.h>

#define CHAR   1
#define	SINT   2
#define INT    3
#define LINT   4
#define FLOAT  5
#define DOUBLE 6

void reverse(char *s)
{
	char *e;
	for(e = s; *e; e++)
		;
	e--;

	char tmp;
	while(s < e)
	{
		tmp = *s;
		*s++ = *e;
		*e-- = tmp;
	}

}

int abso(char type, void *d)
{
	int sign = 1;
	switch(type){
		case FLOAT:
			(*(float *)d < 0)? *(float *)d *= -1, sign = -1: *(float *)d;
                        break;
		case DOUBLE:
			(*(double *)d < 0)? *(double *)d *= -1, sign = -1: *(double *)d;
			break;
		case SINT:
			 (*(short *)d < 0)? *(short *)d *= -1, sign = -1: *(short *)d;
			 break;
		case INT:	
			 (*(int *)d < 0)? *(int *)d *= -1, sign = -1: *(int *)d;
			 break;
		case LINT:
			 (*(long *)d < 0)? *(long *)d *= -1, sign = -1: *(long *)d;
			break;
	}
	return sign;
}

void ntos(char *b, char type, void *d)
{
	char sign  = 0, *s = b;
	if(abso(type, d) < 0)
		sign = '-'; 
	double frac;
	int dec, fracpart;

	switch(type){
		case CHAR:
			do{
				*b++ = *(char *)d % 10 + '0';
				*(char *)d /= 10;
			}while(*(char *)d > 0);
			break;
		case SINT:
			do{
				*b++ = *(short *)d % 10 + '0';
				*(short *)d /= 10;
			}while(*(short *)d > 0);
			break;
		case INT:
			do{
				*b++ = *(int *)d % 10 + '0';
				*(int *)d /= 10;
			}while(*(int *)d > 0);
			break;
		case LINT:
			do{
				*b++ = *(long *)d % 10 + '0';
				*(long *)d /= 10;
			}while(*(long *)d > 0);
			break;
		case FLOAT:
			frac = (*(float *)d - (int)(*(float *)d)) * 10;
                        for(int i = 0; (i < 5) && (int)frac % 10; i++,frac *= 10)
				;	 
			 fracpart = (int)frac;
			dec = (int)(*(float *)d);

			do{
				*b++ = fracpart % 10 + '0';
				fracpart /= 10;
			}while(fracpart > 0);
			*b++ = '.';
			do{
				*b++ = dec % 10 + '0';
				dec /= 10;
			}while(dec > 0);
			break;
		case DOUBLE:
                          frac = (*(double *)d - (int)(*(double *)d)) * 10;
                          for(int i = 0; (i < 5) && (int)frac % 10; i++,frac *= 10)
				;	  
			  fracpart = (int)frac;
		 	  
			  dec = (int)(*(double *)d);
                          do{
                                  *b++ = fracpart % 10 + '0';
                                  fracpart /= 10;
                          }while(fracpart > 0);
                          *b++ = '.';
			  do{
                                  *b++ = dec % 10 + '0';
                                  dec /= 10; 
                          }while(dec > 0);
                          break;
		}
		(sign)?*b++ = sign:1;
		*b = '\0';
		reverse(s);
}

void mprint(char *fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	char *p;

	for(p = fmt; *p; p++)
	{
		if(*p != '%')
			putchar(*p);
		else switch(*++p)
		{
			case 'd': break;
			// TODO
		}
	}	
}

int main()
{
	char s[100];
	double n = -134.342;
        ntos(s,DOUBLE,(void *)(&n));
	printf("%s\n",s);
}
