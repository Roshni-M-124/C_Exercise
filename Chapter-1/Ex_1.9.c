#include<stdio.h>
int main()
{
int c,lastc='A';
while((c=getchar())!=EOF)
{
  if(c!=' ')
    putchar(c);
  else if(lastc!=' ')
    putchar(c);
  lastc=c;
}
}


