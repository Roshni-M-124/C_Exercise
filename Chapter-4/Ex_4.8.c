#include <stdio.h>

int buf = EOF;   
int getch(void)
{
    if (buf != EOF) {
        int c = buf;
        buf = EOF;
        return c;
    }
    return getchar();
}

void ungetch(int c)
{
    if (buf != EOF)
        printf("ungetch: too many characters\n");
    else
        buf = c;
}

