#include<stdio.h>

int get_line(char s[],int lim);
void reverse(char s[],int i,int j);
int main()
{
int l;
char s[100];
l=get_line(s,100);
reverse(s,0,l);
printf("%s",s);
}

int get_line(char s[],int lim)
{
int i,c;
for(i=0;i<lim-1 && ((c=getchar())!=EOF) && c!='\n';i++)
  s[i]=c;
s[i]='\0';
return i-1;
}

void reverse(char s[],int i,int j)
{
int t;
if(i<=j)
{
 reverse(s,i+1,j-1);
 t=s[i];
 s[i]=s[j];
 s[j]=t;
 }
}


