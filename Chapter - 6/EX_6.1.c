#include<ctype.h>
#include<stdio.h>

int getword(char *word, int lim)
{
    int c, d;
    char *w = word;
    while (isspace(c = getch()))
        ;
    if (c == EOF)
        return EOF;
    *w++ = c;
    if (isalpha(c) || c == '_') 
    {
        for (; --lim > 0; w++) 
        {
            c = getch();
            if (!isalnum(c) && c != '_') 
            {
                ungetch(c);
                break;
            }
            *w = c;
        }
        *w = '\0';
        return word[0];
    }
    if (c == '"')
    {
        for (; --lim > 0; w++) 
        {
            *w = getch();
            if (*w == '\\')
            {      
                *++w = getch();
                --lim;
            } 
            else if (*w == '"') 
            {
                w++;
                break;
            }
        }
        *w = '\0';
        return word[0];
    }
    if (c == '\'') 
    {
        *w++ = getch();
        if (*(w - 1) == '\\')
            *w++ = getch();
        *w++ = getch();
        *w = '\0';
        return word[0];
    }
    if (c == '/') 
    {
        d = getch();
        if (d == '/')
        {         
            while ((c = getch()) != '\n' && c != EOF)
                ;
            word[0] = '\0';
            return '\n';
        } 
        else if (d == '*') 
        {  
            while ((c = getch()) != EOF) 
            {
                if (c == '*' && (d = getch()) == '/')
                    break;
                ungetch(d);
            }
            word[0] = '\0';
            return ' ';
        } 
        else
        {
            ungetch(d);
        }
    }
    if (c == '#') 
    {
        while ((c = getch()) != '\n' && c != EOF)
            ;
        word[0] = '\0';
        return '\n';
    }
    *w = '\0';
    return c;
}

