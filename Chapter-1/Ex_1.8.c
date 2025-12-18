#include<stdio.h>
int main()
{
int c,nl,b,t;
nl=0;
b=0;
t=0;
while ((c = getchar()) != EOF)
{
  if (c == '\n')
    ++nl;
  if (c == ' ')
    ++b;
  if (c =='\t')
    ++t;
}
printf("No of lines = %d\n", nl);
printf("No of blanks = %d\n", b);
printf("No of Tabs = %d\n", t);
}
