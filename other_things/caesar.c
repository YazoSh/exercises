/*
./a.out <plain text> <key(an int)>
*/

#include <stdio.h>

int main(int argc,char* argv[])
{
    //charecter counter
    char* ptext = argv[1];
    int key = argv[2][0] - '0';
    int cnum = 0;
    #define EC 26
    for(int i = 0;ptext[i] != '\0';i++)
    {
        cnum++;
    }

    //coder
    for(int i = 0;i <= cnum;i++)
    {
        if(ptext[i] >= 'a' && ptext[i] <= 'z')
        {
            ptext[i] = ((ptext[i] + key - 'a') % EC) + 'a';
        }

        else if(ptext[i] >= 'A' && ptext[i] <= 'Z')
        {
            ptext[i] = ((ptext[i] + key - 'A') % EC) + 'A';
        }

    }
    printf("cipherd text: %s\n",ptext);
}
