#include<stdio.h>

#define swap(t,x,y) {t temp;temp=(x);(x)=(y);(y)=temp;}
int main()
{
    char x,y;
    x='c';
    y='p';
    printf("x= %c \t y= %c\n",x,y);
    swap(char,x,y);
    printf("x=%c \t y=%c\n",x,y);
}
