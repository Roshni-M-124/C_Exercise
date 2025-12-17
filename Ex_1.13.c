#include<stdio.h>
#define MAXWL 20
#define MAXNOW 25
int main()
{
int c ,i,j,nc=0,nw=0;
int word[MAXNOW]={0};
while((c=getchar())!=EOF)
{
 if(c==' '||c=='\t' ||c=='\n')
 {
  if (nc > 0)
  {             
     word[nw++] = nc;
     nc = 0;
  }
}
  else
   nc++;
}
if (nc > 0)
  word[nw++] = nc;
for(i=MAXWL;i>=1;i--)
{
for(j=0;j<=nw;j++)
{
  if(word[j]>=i)
  putchar('*');  
  else
  putchar(' ');
}
putchar('\n');
}
return 0;
}

  
