#include <stdio.h>
#include <stdarg.h>

enum {INT, LINT, ULINT, HULINT, UINT, DOUBLE, OCTAL, hex, HEX};

void reverse(char *s)
{
	char *e, tmp;
	for(e = s; *e; e++)
		;
	while(s < e)
	{
		tmp = *s;
		*s++ = *--e;
		*e = tmp;
	}
}

int abso(char type, void *d)
{
	int sign = 1;
	switch(type){
		case DOUBLE:
			(*(double *)d < 0)? *(double *)d *= -1, sign = -1: *(double *)d;
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

void addpadding(char **s, int n, char c)
{
	for(int i = n; n > 0; n--)
		*(*s)++ = c; 
}
int precision = 6;
void ntos(char *b, char type, void *d)
{
	char sign  = 0, *s = b;
	char capital = 0;
	if(abso(type, d) < 0)
		sign = '-'; 
	if(type == HEX)
		capital = 1;

	union {
		double frac;
		unsigned long fracpart;
		}u;
	int dec;

	switch(type){
		case INT:
			do{
				*b++ = *(int *)d % 10 + '0';
				*(int *)d /= 10;
			}while(*(int *)d > 0);
			addpadding(&b , precision - (b - s), '0');
			break;
		case LINT:
			do{
				*b++ = *(long *)d % 10 + '0';
				*(long *)d /= 10;
			}while(*(long *)d > 0);
			addpadding(&b , precision - (b - s), '0');
			break;
		case UINT:
			do{
				*b++ = *(unsigned *)d % 10 + '0';
				*(unsigned *)d /= 10;
			}while(*(unsigned *)d > 0 );
			addpadding(&b , precision - (b - s), '0');
			break;
		case ULINT:
                        do{
                                *b++ = *(unsigned long *)d % 10 + '0';
                                *(unsigned long*)d /= 10;
                        }while(*(unsigned long*)d > 0 );
			addpadding(&b , precision - (b - s), '0');
                        break;
		case OCTAL:
			do{
				*b++ = *(int *)d % 8 + '0';
				*(int *)d /= 8; 
			}while(*(int *)d > 0);
			addpadding(&b , precision - (b - s), '0');
			break;
		case hex:
		case HEX:
			do{
				*b++ = *(int *)d % 16 + ((*(int *)d % 16 < 10)? '0' :
					 (capital)? 'A' - 10:'a' - 10);
				*(int *)d /= 16;
			}while(*(int *)d > 0);
			addpadding(&b , precision - (b - s), '0');
			break;
		case HULINT:
                        do{
  	                        *b++ = *(unsigned long *)d % 16 + 
					((*(unsigned long *)d % 16 < 10)? '0': 'a' - 10);
	                        *(unsigned long*)d /= 16;
                        }while(*(unsigned long*)d > 0 );
			addpadding(&b , precision - (b - s), '0');
                        break;
		case DOUBLE:
                        u.frac = (*(double *)d - (int)(*(double *)d));
                        for(int i = 0; i < precision; i++,u.frac *= 10)
				;	  
			u.fracpart = (int)u.frac;
			dec = (int)(*(double *)d);
                        do{
                                *b++ = u.fracpart % 10 + '0';
                                u.fracpart /= 10;
                        }while(u.fracpart > 0);
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

#define RIGHT 0
#define LEFT 1

void printpadding(int n, char c)
{
	for(int i = n; i > 0; i--)
		putchar(c);
}

void putarr(char *s, int minwidth, char adj)
{
	union {
		int length;
		int space;
		} u = {0};

	while(s[u.length])
		u.length++;
	u.space = minwidth - u.length;

	if(adj == RIGHT) printpadding(u.space, ' ');
		
	while(*s) putchar(*s++);

	if(adj == LEFT) printpadding(u.space, ' ');
}

void mprintf(char *fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	char *p, *sp, buff[100];
	union {
		char cval;
		short sval;
		int ival;
		long lval;
		unsigned uval;
		unsigned long ulval;
		double dval;
		} u;

	for(p = fmt; *p; p++)
	{
		char adj = RIGHT;
		int minwidth = 0;
		precision = 6;	

		if(*p != '%')
		{
			putchar(*p);
			continue;
		}
		if(*++p == '-')
			adj = LEFT, ++p;	
		#define _isnum(a) (a >= '0' && a <= '9')?1:0
		if(_isnum(*p))	
		{
			sp = buff;
			while(_isnum(*p))
				*sp++ = *p++;
			*sp = '\0';
			sp = buff;
			while(*sp)
				minwidth = minwidth * 10 + *sp++ - '0';
		}
		if(*p == '.')
		{
			p++;
			sp = buff;
			while (_isnum(*p))
				*sp++ = *p++;
			*sp = '\0';
			sp = buff;
			precision = 0;
			while(*sp)
				precision = precision * 10 + *sp++ - '0';	
		}
		#undef _isnum
		switch(*p)
		{
			case 'i':
			case 'd':
				u.ival = va_arg(ap, int);		
				ntos(buff, INT, (void *)(&u.ival));
				putarr(buff, minwidth, adj);
				break;
			case 'o':
				u.uval = va_arg(ap, int);
				ntos(buff, OCTAL, (void *)(&u.uval));
				putarr(buff, minwidth, adj);
				break;
			case 'x':
			case 'X':
				u.uval = va_arg(ap, int);
				ntos(buff, (*p == 'x')?hex:HEX, (void *)(&u.uval));	
				putarr(buff, minwidth, adj);
				break;
			case 'p':
				u.ulval = (unsigned long)va_arg(ap, void *);
				buff[0] = '0';buff[1] = 'x';
				ntos(buff + 2, HULINT, (void *)(&u.ulval));
				putarr(buff, minwidth, adj);
				break;
			case 'u':
				u.uval = va_arg(ap, int);
				ntos(buff, UINT, (void *)(&u.uval));
				putarr(buff, minwidth, adj);
				break;
			case 'c':
				putchar(va_arg(ap, int));
				break;
			case 'f':
				u.dval = va_arg(ap, double);
				ntos(buff, DOUBLE, (void *)(&u.dval));
				putarr(buff, minwidth, adj);
				break;
			case 's':
				putarr(va_arg(ap, char *), minwidth, adj);
				break;
			default:
				putchar(*p);
		}
	}	
	va_end(ap);
}

int main()
{
	int x = 5;
	mprintf("%.4o %s\n%p\n", 69, "\"nigga string\"", &x);
	mprintf(":%-6.2f:\n",89.65);
}
