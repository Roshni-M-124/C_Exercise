#include<stdio.h>
#include<string.h>
#define abs(x) ( (x) > 0 ? (x): -(x))
#define MAXLIMIT 100

void itoa(int n,char s[],int w);
void reverse(char s[]);

int main()
{
    int number,width;
    char str[MAXLIMIT];
    number= 10;
    width=1;
    itoa(number,str,width);
    printf("%s",str);
    return 0;
}

void itoa(int n,char s[],int w)
{
    int i,sign;
    sign=n;
    i = 0;
    do
    {
        s[i++]= abs(n%10) + '0';
    }while((n/=10)!=0);
    if( sign < 0)
        s[i++]='-';
    while(i<w)
        s[i++]=' ';
    s[i]='\0';
    reverse(s);
}

void reverse(char s[])
{
    int i,j,c;
    for(i=0,j=strlen(s)-1;i<j;i++,j--)
    {
        c=s[i];
        s[i]=s[j];
        s[j]=c;
    }
}
