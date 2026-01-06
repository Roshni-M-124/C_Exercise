#include<stdio.h>
#include<string.h>

int get_line(char *s, int lim);

int main(int argc, char * argv[])
{
  FILE * fp1;
  char p[100],s[100];
  char *r1;
  strcpy(p,argv[1]);
  if(argc>1)
  {
    fp1=fopen(argv[2],"r");
    r1=fgets(s,100,fp1);
    while(r1!=NULL)
    {
      char *t1=s;
      char *t2=p;      
      for(*t1;*t1!='\0';t1++)
      {
        if(*t1==*t2)
        {
        while(*t1==*t2 && *t2!='\0')
        {
          ++t1;
          ++t2;
        }
        if(*t2=='\0')
        {
          printf("%s\n",s);
          break;
        }
        }
      }
      r1=fgets(s,100,fp1);
     } 
  }    
  else
  {
  char line[100];
  int c;
  c=get_line(line,100);
  while(c!=0)
  {
    char *t1=s;
    char *t2=p;      
    for(*t1;*t1!='\0';t1++)
    {
      if(*t1==*t2)
      {
      while(*t1==*t2 && *t2!='\0')
      {
        ++t1;
        ++t2;
      }
      if(*t2=='\0')
      {
        printf("%s\n",s);
        break;
      }
      }
      }
      c=get_line(line,100);
     }
  }
  return 0;
 }
          
int get_line(char *s, int lim)
{
    int c;
    char *start = s;
    while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
        *s++ = c;
    if (c == '\n')
        *s++ = c;
    *s = '\0';
    return s - start;
}       
