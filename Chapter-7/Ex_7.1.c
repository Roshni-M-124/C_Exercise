#include<stdio.h>
#include<string.h>
#include<ctype.h>

int main(int argc , char * argv[])
{
    if(argc>=1)
    {
      int c;
      if(strcmp("./upper",argv[0])==0)
      {
        while((c=getchar())!=EOF)
            putchar(toupper(c));
      }
      else if(strcmp("./lower",argv[0])==0)
      {
        while((c=getchar())!=EOF)
            putchar(tolower(c));
       }
     }
     return 0;
 }    
