#include<stdio.h>
unsigned rightrot(unsigned x,int n);
int main()
{
    printf("%u",(unsigned)rightrot((unsigned)8,(int)1));
    return 0;
}
unsigned rightrot(unsigned x, int n)
{
    int w = sizeof(unsigned) * 8;   
    n = n % w;                      
    return (x >> n) | (x << (w - n));
}

