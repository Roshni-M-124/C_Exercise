#include<stdio.h>
#include<ctype.h>

#define NUMBER '0'

int getch();

int getop(char s[])
{
int i=0,c;
static int lastchar=0;
if(lastchar==0)
    c=getch();
else
{
    c=lastchar;
    lastchar=0;
}
while((s[0]=c)==' ' || c=='\t')
    c=getch();
s[1]='\0';
if(!isdigit(c) && c!='.')
    return c;
if(isdigit(c))
    while(isdigit(s[++i]=c=getch())
    ;
if(c=='.')
    while(isdigit(s[++i]=c=getch())
    ;
s[i]='\0';
if(c!=EOF)
    lastchar=c;
return NUMBER;
}
