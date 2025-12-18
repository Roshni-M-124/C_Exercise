#include<stdio.h>
#define MAXLINE 1000

int getline(char line[],int lim);
void copy(char to[],char from[]);

int main()
{
int len,max=0;
char line[MAXLINE],maxline[MAXLINE];
while((len=getline(line,MAXLINE))>0)
{
  if(len>max)
  {
  max=len;
  copy(maxline,line);
  }
  if(max>0)
    printf("%s",maxline);
}
int getline(char s[],int lim)
{
int i,c;
for (i=0;i<lim-1;i++)
{
 c=getchar();
 if( c==EOF)
 break;
 if(c=='\n')
 break;
    s[i]=c;
}
if(c=='\n')
{
s[i]=c;
++i;
}
s[i]='\0';
return i;
}
void copy(char to[],char from[])
{
    int i=0;
    while((to[i]=from[i]) != '\0')
    ++i;
}
