#include <stdio.h>
#include <stdlib.h>

#define MAXLINE 100
#define TABINC  8
#define YES 1
#define NO  0

void settab(int argc, char *argv[], char tab[]);
int  tabpos(int pos, char tab[]);
void detab(char tab[]);

int main(int argc, char *argv[])
{
    char tab[MAXLINE + 1];

    settab(argc, argv, tab);
    detab(tab);

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

void detab(char tab[])
{
    int c, pos = 1;

    while ((c = getchar()) != EOF) {
        if (c == '\t') {
            do {
                putchar(' ');
                pos++;
            } while (tabpos(pos - 1, tab) != YES);
        } else if (c == '\n') {
            putchar(c);
            pos = 1;
        } else {
            putchar(c);
            pos++;
        }
    }
}

