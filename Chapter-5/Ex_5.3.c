#include<stdio.h>
#define MAXLINE 1000

int get_line(char line[],int lim);
void str_cat(char *,char *);

int main()
{
    int len;
    char s[MAXLINE],t[MAXLINE];
    printf("Enter s:");
    get_line(s,MAXLINE);
    printf("Enter t:");
    get_line(t,MAXLINE);
    str_cat(s,t);
    printf("%s\n",s);
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

void str_cat(char *s,char *t)
{
    while(*s!='\0')
        s++;
    s--;            
    while((*s=*t)!='\0')
    {   
        s++;
        t++;
    }
}
