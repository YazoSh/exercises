// ./a.out <plaintext> <key>

#include <stdio.h>

int main(int argc,char* argv[])
{
    char* ptext = argv[1];
    char* key = argv[2];
    #define EC 26
    //string charecter counter
    int cnum = 0;
    for(int i = 0; ptext[i] != '\0';i++)
    {
        cnum++;
    }

    //key charecter counter
    int knum = 0;
    for(int i = 0;key[i] != '\0';i++)
    {
        knum++;
    }


    //turn key to lowercase
    for(int i = 0;i <= knum;i++)
    {
        if(key[i] >= 'A' && key[i] <= 'Z')
            {
                key[i] = key[i] - ('A' - 'a');
            }
    }



    //coder
    int k = 0;
    for(int i = 0;i < cnum;i++)
    {
        if(ptext[i] >= 'a' && ptext[i] <= 'z')
        {
            ptext[i] = ((ptext[i] + key[k] - 'a' - 'a') % EC) + 'a';
            k++;
            if(k == knum)
            {
                k = 0;
            }
        }
        else if(ptext[i] >= 'A' && ptext[i] <= 'Z')
        {
            ptext[i] = ((ptext[i] + key[k] - 'a' - 'A') % EC) + 'A' ;
            k++;
            if(k == knum )
            {
                k = 0;
            }
        }
    }

    //print result
    printf("coded text:%s\n",ptext);
}
