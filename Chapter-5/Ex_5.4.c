#include<stdio.h>
#define MAXLINE 1000

int get_line(char line[],int lim);
int strend(char *s,char *t);

int main()
{
    char s[MAXLINE],t[MAXLINE];
    int ret;
    printf("Enter s:");
    get_line(s,MAXLINE);
    printf("Enter t:");
    get_line(t,MAXLINE);
    ret = strend(s,t);
    printf("%d\n",ret);
    return 0;
}

int get_line(char s[],int lim)
{
    int c,i;
    for(i=0;i<lim-1 && (c=getchar()) !=EOF && c!='\n';++i)
        s[i] = c;
    if(c == '\n')
    {
        s[i] = c;
        ++i;
    }
    s[i] = '\0';
    return i;
}

int strend(char *s, char *t)
{   
    char *bt = t;  
    while (*s)
        s++;
    while (*t)
        t++;
    while (t > bt)
    {
        if (*--s != *--t)
            return 0;
    }
   return 1;
}

