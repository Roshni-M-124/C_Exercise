#include <stdio.h>
void m_itoa(int n,char s[]);
int main()
{
int n;
scanf("%d",&n);
char s[10];
m_itoa(n,s);
printf("%s",s);
}

void m_itoa(int n,char s[])
{
static int i=0;
if (n < 0) {
s[i++]='-';
n = -n;
}
if (n / 10)
m_itoa(n / 10,s);
s[i++]=(n%10)+'0';
s[i] = '\0'; 
}
