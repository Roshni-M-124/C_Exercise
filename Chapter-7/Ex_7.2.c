#include<stdio.h>
#include<string.h>
#include<ctype.h>

int main()
{
  int c,count=0;
  while((c=getchar())!=EOF)
  {
    count++;
    if(count%80 ==0)
    {
      printf("\n");
      count = 0;
     } 
    if(c=='\n')
    {
      printf("\n");
      count = 0;
    } 
    else if(isprint(c))
    {
      printf("%c",c);
      count+=1;
    }  
    else
    {
      printf("\\%03o",c);
      count +=4;
     } 
  }  
     return 0;
 }    
