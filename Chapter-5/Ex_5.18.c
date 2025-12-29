#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXTOKEN 100
#define BUFSIZE  100

enum { NAME, PARENS, BRACKETS };
enum { NO, YES };

void dcl();
void dirdcl();
void errmsg(char *);
void skiptoeol();
int  gettoken();
int  getch();
void ungetch(int);

int  tokentype;
char token[MAXTOKEN];
char name[MAXTOKEN];
char datatype[MAXTOKEN];
char out[1000];
int  prevtoken = NO;

char buf[BUFSIZE];
int  bufp = 0;

int main()
{
    while (gettoken() != EOF) 
    {
        strcpy(datatype, token);
        out[0] = '\0';
        dcl();
        if (tokentype != '\n')
            errmsg("syntax error\n");
        printf("%s: %s %s\n", name, out, datatype);
    }
    return 0;
}

void dcl()
{
    int ns = 0;
    while (gettoken() == '*')
        ns++;
    dirdcl();
    while (ns-- > 0)
        strcat(out, " pointer to");
}

void dirdcl()
{
    int type;
    if (tokentype == '(')
    {
        dcl();
        if (tokentype != ')')
        {
            errmsg("error: missing )\n");
        }
    }
    else if (tokentype == NAME)
    {
        strcpy(name, token);
    }
    else 
    {
        errmsg("error: expected name or (dcl)\n");
    }
    while ((type = gettoken()) == PARENS || type == BRACKETS) 
    {
        if (type == PARENS)
            strcat(out, " function returning");
        else {
            strcat(out, " array");
            strcat(out, token);
            strcat(out, " of");
        }
    }
}

void errmsg(char *msg)
{
    printf("%s", msg);
    name[0] = '\0';     
    out[0]  = '\0';   
    skiptoeol();       
    prevtoken = NO;
}

void skiptoeol()
{
    int c;
    while ((c = getch()) != '\n' && c != EOF)
        ;
    tokentype = '\n';
}

int gettoken()
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
        } else 
        {
            ungetch(c);
            return tokentype = '(';
        }
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

int getch()
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)
{
    if (bufp < BUFSIZE)
        buf[bufp++] = c;
}

