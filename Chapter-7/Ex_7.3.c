#include <stdio.h>
#include <stdarg.h>
#include <ctype.h>

void minprintf(char *fmt, ...)
{
    va_list ap;
    char *p, *sval;
    char tempfmt[10];
    int i, ival;
    unsigned uval;
    double dval;
    va_start(ap, fmt);
    for (p = fmt; *p; p++) 
    {
        if (*p != '%') 
        {
            putchar(*p);
            continue;
        }
        i = 0;
        tempfmt[i++] = '%';
        while (*(p + 1) && !isalpha(*(p + 1)) && *(p + 1) != '%')
            tempfmt[i++] = *++p;
        tempfmt[i++] = *++p;
        tempfmt[i] = '\0';
        switch (*p)
        {
        case 'd':
        case 'i':
            ival = va_arg(ap, int);
            printf(tempfmt, ival);
            break;
        case 'u':
        case 'o':
        case 'x':
        case 'X':
            uval = va_arg(ap, unsigned);
            printf(tempfmt, uval);
            break;
        case 'f':
            dval = va_arg(ap, double);
            printf(tempfmt, dval);
            break;
        case 's':
            sval = va_arg(ap, char *);
            printf(tempfmt, sval);
            break;
        case 'c':
            ival = va_arg(ap, int);
            printf(tempfmt, ival);
            break;
        case '%':
            putchar('%');
            break;
        default:
            fputs(tempfmt, stdout);
            break;
        }
    }
    va_end(ap);
}

int main()
{
    minprintf("Int: %6d\n", 42);
    minprintf("Float: %8.2f\n", 3.14159);
    minprintf("Hex: %#x\n", 255);
    minprintf("String: %-10s END\n", "hello");
    minprintf("Char: %c\n", 'A');
    return 0;
}

