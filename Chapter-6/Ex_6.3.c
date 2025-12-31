#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAXWORD   100
#define MAXLINES  1000

struct tnode 
{
    char *word;
    int lines[MAXLINES];
    int count;
    struct tnode *left;
    struct tnode *right;
};

struct tnode *addtree(struct tnode *, char *);
struct tnode *talloc();
void treeprint(struct tnode *);
int getword(char *, int);
char *str_dup(char *);
int iskeyword(char *);
int isnoise(char *);

char *keywords[] = {"auto","break","case","char","const","continue","default",
    "do","double","else","enum","extern","float","for","goto","if","int","long",
    "register","return","short","signed","sizeof","static","struct","switch",
    "typedef","union","unsigned","void","volatile","while" };

#define NKEYS (sizeof(keywords) / sizeof(char *))

char *noisewords[] = { "the","and","as","so","of","to","a","in","is","it","for","on" };

int main()
{
    struct tnode *root = NULL;
    char word[MAXWORD];
    while (getword(word, MAXWORD) != EOF) 
    {
        if (isalpha(word[0]) && !iskeyword(word) && !isnoise(word))
            root = addtree(root, word);
    }
    treeprint(root);
    return 0;
}

int getword(char *word, int lim)
{
    int c,d;
    char *w = word;
    while (isspace(c = getchar()))
    {
        if (c == '\n')
            lineno++;
    }
     if (c == '"') 
    {            
        while ((c = getchar()) != '"' && c != EOF)
            ;
        return getword(word, lim);
    }
    if (c == '/') 
    {               
        if ((d = getchar()) == '/') 
        {
            while ((c = getchar()) != '\n' && c != EOF)
             ;
            return getword(word, lim);
        } 
        else if (d == '*') 
        {
            while ((c = getchar()) != EOF)
             if (c == '*' && (d = getchar()) == '/')
                    break;
            return getword(word, lim);
        } 
        else
        {
            ungetc(d, stdin);
        }
     }
    if (!isalpha(c) && c != '_')
        return c;
    *w++ = c;
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

int iskeyword(char *word)
{
    for (int i = 0; i < NKEYS; i++)
        if (strcmp(word, keywords[i]) == 0)
            return 1;
    return 0;
}

int isnoise(char *word)
{
    for (int i = 0; i < NNOISE; i++)
        if (strcmp(word, noisewords[i]) == 0)
            return 1;
    return 0;
}

struct tnode *talloc()
{
    return (struct tnode *)malloc(sizeof(struct tnode));
}

struct tnode *addtree(struct tnode *p, char *w)
{
    int cond;
    if (p == NULL)
    {
        p = talloc();
        p->word = str_dup(w);
        p->lines[0] = lineno;
        p->count = 1;
        p->left = p->right = NULL;
    }
    else if ((cond = strcmp(w, p->word)) == 0)
    {
        if (p->lines[p->count - 1] != lineno)
            p->lines[p->count++] = lineno;
    }
    else if (cond < 0)
        p->left = addtree(p->left, w);
    else
        p->right = addtree(p->right, w);

    return p;
}

void treeprint(struct tnode *p)
{
    if (p != NULL) {
        treeprint(p->left);

        printf("%s: ", p->word);
        for (int i = 0; i < p->count; i++)
            printf("%d ", p->lines[i]);
        printf("\n");
        treeprint(p->right);
    }
}

char *str_dup(char *s)
{
    char *p = (char *)malloc(strlen(s) + 1);
    if (p != NULL)
        strcpy(p, s);
    return p;
}

