#include <stdio.h>
#include <stdarg.h>
#include <ctype.h>

void minscanf(char *fmt, ...)
{
    va_list ap;
    char *p, *sval;
    char tempfmt[10];
    int i, *ival;
    unsigned *uval;
    double *dval;
    va_start(ap, fmt);
    for (p = fmt; *p; p++) 
    {
        i = 0;
        if (*p != '%') 
        {
            tempfmt[i++]=*p;
            continue;
        }
        tempfmt[i++] = '%';
        while (*(p + 1) && !isalpha(*(p + 1)))
            tempfmt[i++] = *++p;
        tempfmt[i++] = *++p;
        tempfmt[i] = '\0';
        switch (*p)
        {
        case 'd':
        case 'i':
            ival = va_arg(ap, int*);
            scanf(tempfmt, ival);
            break;
        case 'u':
        case 'o':
        case 'x':
        case 'X':
            uval = va_arg(ap, unsigned*);
            scanf(tempfmt, uval);
            break;
        case 'f':
            dval = va_arg(ap, double*);
            scanf(tempfmt, dval);
            break;
        case 's':
            sval = va_arg(ap, char *);
            scanf(tempfmt, sval);
            break;
        case 'c':
            ival = va_arg(ap, int*);
            scanf(tempfmt, ival);
            break;
        default:
            break;
        }
    }
    va_end(ap);
}

int main()
{
    int i;
    float d;
    char s[50];
    printf("Enter values (int float string):\n");
    minscanf("%d %f %s", &i, &d, s);
    printf("scanned values:\n");
    printf("i = %d\n", i);
    printf("d = %f\n", d);
    printf("s = %s\n", s);
    return 0;
}
