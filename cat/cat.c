#include <stdio.h>

int main(int argc, char **argv)
{
	FILE *input = (argc > 1)?NULL:stdin;
	// adds one to the arg counter so it would run at least one time
	// if no argunments are passed
	// kinda hacky but f it
	(argc == 1)?argc++:argc;	
	while(--argc)
	{
		if(!input)
			input = fopen(*++argv,"r");
		if(input == NULL)
		{
			fprintf(stderr,"File:\"%s\" couldn\'t be opened!\n", *argv);
			continue;
		}
		int c;
		while((c = getc(input)) > 0)
			putc(c, stdout);
		fclose(input);
		input = NULL;
	}
	return 0;
}
