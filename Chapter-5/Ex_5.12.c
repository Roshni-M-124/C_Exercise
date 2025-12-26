#include<stdio.h>
#include<stdlib.h>

#define MAXLINE 100
#define TABINC  8
#define YES 1
#define NO  0

void entab(int argc,char *argv[],char *tab);
void detab(char *tab);
int tabpos(int pos,char *tab);

int main(int argc,char *argv[])
{
    char tab[MAXLINE+1];
    entab(argc,argv,tab);
    detab(tab);
    return 0;
}

void entab(int argc,char *argv[],char *tab)
{
    int i,inc,pos;

    if(argc <= 1)
    {
        for(i = 1; i <= MAXLINE; i++)
            if(i % TABINC == 0)
                tab[i] = YES;
            else
                tab[i] = NO;
    }
    else if(argc == 3 && *argv[1] == '-' && *argv[2] == '+')
    {
        pos = atoi(&(*++argv)[1]);
        inc = atoi(&(*++argv)[1]);

        for(i = 1; i <= MAXLINE; i++)
            if(i != pos)
                tab[i] = NO;
            else
            {
                tab[i] = YES;
                pos += inc;
            }
    }
    else
    {
        for(i = 1; i <= MAXLINE; i++)
            tab[i] = NO;

        while(--argc > 0)
        {
            pos = atoi(*++argv);
            if(pos > 0 && pos <= MAXLINE)
                tab[pos] = YES;
        }
    }
}

void detab(char *tab)
{
    int c,pos = 1;
    int nb = 0;
    int nt = 0;

    while((c = getchar()) != EOF)
    {
        if(c == ' ')
        {
            if(tabpos(pos,tab) == NO)
                ++nb;
            else
            {
                nb = 0;
                ++nt;
            }
            ++pos;
        }
        else
        {
            for(; nt > 0; nt--)
                putchar('\t');
            for(; nb > 0; nb--)
                putchar(' ');

            putchar(c);

            if(c == '\n')
                pos = 1;
            else if(c == '\t')
                while(tabpos(pos++,tab) != YES)
                    ;
            else
                ++pos;
        }
    }
}

int tabpos(int pos,char *tab)
{
    if(pos > MAXLINE)
        return YES;
    else
        return tab[pos];
}

