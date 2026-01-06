#include<stdio.h>

#define MAXLINE 50

int main(int argc, char * argv[])
{
  FILE *fp1,*fp2;
  fp1=fopen(argv[1],"r");
  fp2=fopen(argv[2],"r");
  if (fp1 == NULL)
  { 
    fprintf(stderr, "Cannot open %s\n", argv[1]);
    return 1;
  }
  if (fp2 == NULL) 
  { 
    fprintf(stderr, "Cannot open %s\n", argv[2]);
    return 1;
 }
  int line=1,page=1;
  char *r1;
  char s[100];
  r1=fgets(s,100,fp1);
  printf("%s    PAGE : %d\n",argv[1],page);
  while(r1!=NULL)
  {
    if(line%MAXLINE==0)
    {
    printf("\f");
    page++;
    printf("%s    PAGE : %d\n",argv[1],page);
    line=1;
    }
    printf("%s",s);
    r1 = fgets(s, 100, fp1);
    line++;
  }  
  r1=fgets(s,100,fp2);
  line=1;
  page=1;
  printf("%s    PAGE : %d\n",argv[2],page);
  while(r1!=NULL)
  {
    if(line%MAXLINE==0)
    {
    printf("\f");
    page++;
    printf("%s    PAGE : %d\n",argv[2],page);
    line=1;
    }
    printf("%s",s);
    r1 = fgets(s, 100, fp2);
    line++;
  }
 return 0;
 }
    
  
