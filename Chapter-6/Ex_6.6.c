#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>

#define HASHSIZE 101
#define MAXWORD 100

struct nlist{
    struct nlist *next;
    char *name;
    char *defn;
};

static struct nlist *hashtab[HASHSIZE];

unsigned hash(char *s);
struct nlist *install(char *, char *);
struct nlist *lookup(char *);
int getword(char *, int);

int main()
{
    char word[MAXWORD];
    char name[MAXWORD];
    char defn[MAXWORD];
    struct nlist *np;
    int c;
    while ((c = getword(word, MAXWORD)) != EOF)
    {
        if (word[0] == '#')
        {
        getword(word, MAXWORD);
        if (strcmp(word, "define") == 0)
        {
            getword(name, MAXWORD);
            getword(defn, MAXWORD);
            install(name, defn);
            while ((c = getword(word, MAXWORD)) != '\n' && c != EOF)
                ;
        }
        }
        else if (isalpha(word[0]) || word[0] == '_')
        {
            if ((np = lookup(word)) != NULL)
                printf("%s", np->defn);
            else
                printf("%s", word);
        }
        else
            printf("%s", word);
    }
    return 0;
}

unsigned hash(char *s)
{
    unsigned hashval = 0;
    while (*s)
        hashval = *s++ + 31 * hashval;
    return hashval % HASHSIZE;
}

struct nlist *install(char *s, char *d)
{
    struct nlist *np;
    unsigned h;
    if ((np = lookup(s)) == NULL)
    {
        np = (struct nlist *)malloc(sizeof(*np));
        if (np == NULL)
            return NULL;
        np->name = strdup(s);
        if (np->name == NULL)
            return NULL;
        h = hash(s);
        np->next = hashtab[h];
        hashtab[h] = np;
    }
    else
        free(np->defn);
    np->defn = strdup(d);
    if (np->defn == NULL)
        return NULL;
    return np;
}

struct nlist *lookup(char *s)
{
    struct nlist *np;
    for (np = hashtab[hash(s)]; np != NULL; np = np->next)
        if (strcmp(np->name, s) == 0)
            return np;
    return NULL;
}

int getword(char *word, int lim)
{
    int c;
    char *w = word;
    while ((c = getchar()) == ' ' || c == '\t')
        ;
    if (c == EOF)
        return EOF;
    if (c == '\n')
    {
        *w++ = '\n';
        *w = '\0';
        return '\n';
    }
    *w++ = c;
    if (!isalpha(c) && c != '_')
    {
        *w = '\0';
        return c;
    }
    for (; --lim > 0; w++)
    {
        c = getchar();
        if (!isalnum(c) && c != '_')
        {
            ungetc(c, stdin);
            break;
        }
        *w = c;
    }
    *w = '\0';
    return word[0];
}

