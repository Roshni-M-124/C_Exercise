#include<stdio.h>
#include <ctype.h>
#define MAXLINE 100

void mgetline(char s[],int maxlimit);
void expand(char s1[],char s2[]);

int main(void)
{
    char s1[MAXLINE],s2[MAXLINE];
    mgetline(s1,MAXLINE);
    expand(s1,s2);
    printf("%s",s2);
    return 0;
}

void mgetline(char s[],int lim)
{
    int i,c;
    for(i=0;i<lim-1 && (c=getchar())!=EOF && c!='\n';++i)
        s[i]=c;
    if(c=='\n')
        s[i++]=c;
    s[i]='\0';
}
void expand(char s1[], char s2[])
{
    int i, j;
    char c, prev;

    i = j = 0;
    prev = '\0';

    for (i = 0; s1[i] != '\0'; i++) {
        c = s1[i];
        if (c == '-' && prev != '\0' && s1[i+1] != '\0') {
            char next = s1[i+1];

        if ( (islower(prev) && islower(next) && prev < next) ||(isupper(prev) && isupper(next) && prev <next)||                 (isdigit(prev) && isdigit(next) && prev < next) ) {

        for (int k = prev + 1; k <= next; k++)
                    s2[j++] = k;

                prev = '\0';
                i++;   
                continue;
            }
        }
        s2[j++] = c;
        prev = c;
    }
    s2[j] = '\0';
}

