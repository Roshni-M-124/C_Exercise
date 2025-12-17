#include<stdio.h>
#define MAXNOW 25
int main()
{
int c,i,j,max=0;
int letter[26]={0};
while((c=getchar())!=EOF)
{
if (c >= 'A' && c <= 'Z')
    letter[c - 'A']++;
else if (c >= 'a' && c <= 'z')
    letter[c - 'a']++;
}
for(i=0;i<26;i++)
{
if(letter[i]>max)
max=letter[i];
}
for(i=max;i>=1;i++)
{
for(j=0;j<26;j++)
{
if(letter[j]>=i)
putchar('*');
else
putchar(' ');
}
putchar('\n');
}
return 0;
}

