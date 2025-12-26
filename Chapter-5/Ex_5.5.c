#include<stdio.h>
#define MAXLINE 1000

void mstrncpy(char *s, char *t, int n);
void mstrncat(char *s, char *t, int n);
int mstrncmp(char *s, char *t, int n);
int get_line(char s[],int lim);

int main()
{
    char s[MAXLINE], t[MAXLINE], dest[MAXLINE];
    int n, ret;
    printf("Enter s : ");
    get_line(s, MAXLINE);
    printf("Enter t : ");
    get_line(t, MAXLINE);
    printf("Enter n: ");
    scanf("%d", &n);
    
    mstrncpy(s, t, n);
    printf("After strncpy: %s\n", s);
    getchar();
    mstrncat(s, t, n);
    printf("After strncat: %s\n",s);
    
    printf("\nEnter s for strncmp : ");
    get_line(s, MAXLINE);
    printf("Enter t for strncmp: ");
    get_line(t, MAXLINE);
    ret = mstrncmp(s, t, n);
    printf("Result of strncmp: %d\n", ret);

    return 0;
}
int get_line(char s[],int lim)
{
    int c,i;
    for(i=0;i<lim-1 && (c=getchar()) !=EOF && c!='\n';++i)
        s[i] = c;
    s[i] = '\0';
    return i;
}
void mstrncpy(char *s, char *t, int n)
{
    int i = 0;
    while (i < n && t[i] != '\0') 
    {
        s[i] = t[i];
        i++;
    }
    while (i < n) {
        s[i] = '\0';
        i++;
    }
}

void mstrncat(char *s, char *t, int n)
{
    while(*s) 
     s++;
    s--;
    while(n-- >0) 
    {
        *s++ = *t++;
    }
    *s = '\0';
}


int mstrncmp(char *s, char *t, int n)
{
  for(; *s== *t; s++,t++)
        if( *s == '\0' || --n <=0)
            return 0;
    return *s - *t;

}

