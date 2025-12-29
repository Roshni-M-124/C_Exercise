#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<ctype.h>

#define MAXLINES 5000
#define MAXLEN 1000

char *lineptr[MAXLINES];
int numeric = 0;  
int reverse = 0;
int fold = 0;
int directory = 0;

int readlines(char *lineptr[], int maxlines);
void writelines(char *lineptr[], int nlines);
void quicksort(void *v[], int left, int right, int (*comp)(void *, void *));
int numcmp(char *, char *);
int str_cmp(char *s, char *t);
int compare(void *a, void *b);
int get_line(char *s, int lim);
void swap(void *v[], int i, int j);

int main(int argc, char *argv[])
{
    int nlines;
    for (int i = 1; i < argc; i++) 
    {
        if (str_cmp(argv[i], "-n") == 0)
            numeric = 1;
        else if (str_cmp(argv[i], "-r") == 0)
            reverse = 1;
        else if (str_cmp(argv[i],"-f") == 0)
            fold = 1;
        else if (str_cmp(argv[i],"-d") == 0)
            directory = 1;
    }
    if ((nlines = readlines(lineptr, MAXLINES)) >= 0) 
    {
        quicksort((void **)lineptr, 0, nlines - 1, compare);
        writelines(lineptr, nlines);
        return 0;
    } 
    else
    {
        printf("Input too big to sort\n");
        return 1;
    }
}

void quicksort(void *v[], int left, int right, int (*comp)(void *, void *))
{
    int i, last;
    if (left >= right)
        return;
    swap(v, left, (left + right)/2);
    last = left;
    for (i = left + 1; i <= right; i++)
        if ((*comp)(v[i], v[left]) < 0)
            swap(v, ++last, i);
    swap(v, left, last);  
    quicksort(v, left, last - 1, comp);
    quicksort(v, last + 1, right, comp);
}

int compare(void *a, void *b)
{
    int result;
    if (numeric)
        result = numcmp(a, b);
    else
        result = str_cmp(a, b);
    return reverse ? -result : result;
}

void swap(void *v[], int i, int j)
{
    void *temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

void writelines(char *lineptr[], int nlines)
{
    while (nlines-- > 0)
        printf("%s\n", *lineptr++);
}

int readlines(char *lineptr[], int maxlines)
{
    int len, nlines = 0;
    char *p, line[MAXLEN];
    while ((len = get_line(line, MAXLEN)) > 0) 
    {
        if (nlines >= maxlines || (p = malloc(len)) == NULL)
            return -1;
        else 
        {
            line[len - 1] = '\0';  
            strcpy(p, line);
            lineptr[nlines++] = p;
        }
    }
    return nlines;
}

int get_line(char *s, int lim)
{
    int c;
    char *start = s;
    while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
        *s++ = c;
    if (c == '\n')
        *s++ = c;
    *s = '\0';
    return s - start;
}

int numcmp(char *s1, char *s2)
{
    double v1 = atof(s1);
    double v2 = atof(s2);
    if (v1 < v2) 
      return -1;
    else if (v1 > v2) 
      return 1;
    else
      return 0;
}

int str_cmp(char *s, char *t)
{
    if(fold)
    {
        int a, b;
        a = tolower(*s);
        b = tolower(*t);
        for( ; a == b ; )
        {
            if(directory)
            {
                while(*s && !isalpha(*s) && !isdigit(*s) && *s != ' ')
                    s++;
                while(*t && !isalpha(*t) && !isdigit(*t) && *t != ' ')
                    t++;
            }
            if(*s == '\0' || *t == '\0')
                break;
            a = tolower(*s);
            b = tolower(*t);
            if(a != b)
                return a - b;
            s++;
            t++;
        }
        return tolower(*s) - tolower(*t);
    }
    else
    {
        for( ; *s == *t ; )
        {
            if(directory)
            {
                while(*s && !isalpha(*s) && !isdigit(*s) && *s != ' ')
                    s++;
                while(*t && !isalpha(*t) && !isdigit(*t) && *t != ' ')
                    t++;
            }
            if(*s == '\0' || *t == '\0')
                break;
            if(*s != *t)
                return *s - *t;
            s++;
            t++;
        }
        return *s - *t;
    }
}

