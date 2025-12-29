#include <stdio.h>
#include <stdlib.h>

#define MAXLINE 100
#define TABINC  8

#define YES 1
#define NO  0

void settab(int argc, char *argv[], char tab[]);
int  tabpos(int pos, char tab[]);
void entab(char tab[]);

int main(int argc, char *argv[])
{
    char tab[MAXLINE + 1];

    settab(argc, argv, tab);
    entab(tab);

    return 0;
}

void settab(int argc, char *argv[], char tab[])
{
    int i, pos;

    if (argc <= 1) 
    {   
        for (i = 1; i <= MAXLINE; i++)
            tab[i] = (i % TABINC == 0) ? YES : NO;
    } 
    else 
    {           
        for (i = 1; i <= MAXLINE; i++)
            tab[i] = NO;
        while (--argc > 0) {
            pos = atoi(*++argv);
            if (pos > 0 && pos <= MAXLINE)
                tab[pos] = YES;
        }
    }
}

int tabpos(int pos, char tab[])
{
    if (pos > MAXLINE)
        return YES;
    return tab[pos];
}

void entab(char tab[])
{
    int c, pos = 1;
    int nb = 0, nt = 0;

    while ((c = getchar()) != EOF) {
        if (c == ' ') {
            if (tabpos(pos, tab) == YES) {
                nt++;
                nb = 0;
            } else {
                nb++;
            }
            pos++;
        } else {
            while (nt-- > 0)
                putchar('\t');
            while (nb-- > 0)
                putchar(' ');

            if (c == '\n')
                pos = 1;
            else if (c == '\t')
                while (tabpos(pos++, tab) != YES)
                    ;
            else
                pos++;

            putchar(c);
            nt = nb = 0;
        }
    }
}

