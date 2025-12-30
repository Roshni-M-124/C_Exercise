#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXTOKEN 100
#define MAXOUT   10000
#define BUFSIZE  100

enum { NAME, PARENS, BRACKETS };
enum { NO, YES };

int tokentype;
char token[MAXTOKEN];
char out[MAXOUT];

int prevtoken = NO;
int gettoken();
int nexttoken();
int getch();
void ungetch(int);
char buf[BUFSIZE];
int bufp = 0;

int main(void)
{
    int type;
    char temp[MAXOUT];
    while (gettoken() != EOF)
    {
        strcpy(out, token);
        while ((type = gettoken()) != '\n')
        {
            if (type == PARENS || type == BRACKETS)
            {
                strcat(out, token);
            }
            else if (type == '*')
            {
                int next = nexttoken();
                temp[0] = '\0';
                if (next == PARENS || next == BRACKETS)
                {
                    strcat(temp, "(*");
                    strcat(temp, out);
                    strcat(temp, ")");
                }
                else
                {
                    strcat(temp, "*");
                    strcat(temp, out);
                }
                strcpy(out, temp);
            }
            else if (type == NAME)
            {
                temp[0] = '\0';
                strcat(temp, token);
                strcat(temp, " ");
                strcat(temp, out);
                strcpy(out, temp);
            }
            else
            {
                printf("invalid input at %s\n", token);
            }
        }
        printf("%s\n", out);
    }
    return 0;
}

int nexttoken(void)
{
    int type = gettoken();
    prevtoken = YES;
    return type;
}

int gettoken(void)
{
    int c;
    char *p = token;
    if (prevtoken == YES)
    {
        prevtoken = NO;
        return tokentype;
    }
    while ((c = getch()) == ' ' || c == '\t')
        ;

    if (c == '(')
    {
        if ((c = getch()) == ')')
        {
            strcpy(token, "()");
            return tokentype = PARENS;
        }
        ungetch(c);
        return tokentype = '(';
    }
    else if (c == '[')
    {
        *p++ = c;
        while ((*p++ = getch()) != ']')
            ;
        *p = '\0';
        return tokentype = BRACKETS;
    }
    else if (isalpha(c))
    {
        *p++ = c;
        while (isalnum(c = getch()))
            *p++ = c;
        *p = '\0';
        ungetch(c);
        return tokentype = NAME;
    }
    else
    {
        return tokentype = c;
    }
}

int getch(void)
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)
{
    if (bufp < BUFSIZE)
        buf[bufp++] = c;
}

