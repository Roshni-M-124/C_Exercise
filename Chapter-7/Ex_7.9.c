#include<stdio.h>

#define isupperm(c) ((c)>='A' && (c)<='Z')?1:0

int isupperf(char c)
{
  if(c >='A' && c<='Z')
    return 1;
  else
    return 0;
}    

int main()
{
  char *p="THIS IS A String";
  printf("Char\tMacro\tFunction\n");
  for (; *p != '\0'; p++)
     printf("%c\t%d\t%d\n", *p, isupperm(*p), isupperf(*p));
 return 0;
 }
