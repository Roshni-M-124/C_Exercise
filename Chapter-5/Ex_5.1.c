#include <ctype.h>
#include<stdio.h>

#define SIZE 1000
#define BUFSIZE 100

int getch(void);
void ungetch(int);
int getint(int *);

char buf[BUFSIZE];
int bufp = 0;

int main()
{
    int n,s,array[SIZE];
    for(n=0;n<SIZE && getint(&array[n]) != EOF; n++)
        ;
    for(s=0;s<n; s++)
        printf("%d",array[s]);
    return 0;
}

int getint(int *pn)
{
    int c, sign;
    while (isspace(c = getch()))
        ;
    if (!isdigit(c) && c != EOF && c != '+' && c != '-') 
    {
        ungetch(c);
        return 0;
    }
    sign = 1;
    if (c == '+' || c == '-') {
        sign = (c == '-') ? -1 : 1;
        c = getch();
        if (!isdigit(c)) {
            ungetch(c);
            ungetch(sign == -1 ? '-' : '+');
            return 0;
        }
    }
    for (*pn = 0; isdigit(c); c = getch())
        *pn = 10 * *pn + (c - '0');
    *pn *= sign;
    if (c != EOF)
        ungetch(c);
    return c;
}

int getch(void)
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)
{
    if(bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}

