#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAXWORD 100

struct tnode {
    char *word;
    int count;
    struct tnode *left;
    struct tnode *right;
};

struct cnode {
    char *word;
    int count;
    struct cnode *left;
    struct cnode *right;
};

struct tnode *addtree1(struct tnode *, char *);
struct cnode *addtree2(struct cnode *, char *, int);
struct tnode *talloc1();
struct cnode *talloc2();
void inserttree(struct tnode *, struct cnode **);
void treeprint(struct cnode *);
int getword(char *, int);
char *str_dup(char *);

int main()
{
    struct tnode *root1 = NULL;   
    struct cnode *root2 = NULL;   
    char word[MAXWORD];
    while (getword(word, MAXWORD) != EOF) 
    {
        if (isalpha(word[0]))
            root1 = addtree1(root1, word);
    }
    inserttree(root1, &root2);
    treeprint(root2);
    return 0;
}

int getword(char *word, int lim)
{
    int c;
    char *w = word;
    while (isspace(c = getchar()))
        ;
    if (c == EOF)
        return EOF;
    if (!isalpha(c)) 
    {
        *w = '\0';
        return c;
    }
    *w++ = c;
    for (; --lim > 0; w++) 
    {
        c = getchar();
        if (!isalnum(c)) 
        {
            ungetc(c, stdin);
            break;
        }
        *w = c;
    }
    *w = '\0';
    return word[0];
}

struct tnode *talloc1()
{
    return (struct tnode *)malloc(sizeof(struct tnode));
}

struct tnode *addtree1(struct tnode *p, char *w)
{
    int comp;
    if (p == NULL) 
    {
        p = talloc1();
        p->word = str_dup(w);
        p->count = 1;
        p->left = p->right = NULL;
    }
    else if ((comp = strcmp(w, p->word)) == 0) 
    {
        p->count++;
    }
    else if (comp < 0)
        p->left = addtree1(p->left, w);
    else
        p->right = addtree1(p->right, w);

    return p;
}

struct cnode *talloc2()
{
    return (struct cnode *)malloc(sizeof(struct cnode));
}

struct cnode *addtree2(struct cnode *p, char *w, int count)
{
    if (p == NULL) 
    {
        p = talloc2();
        p->word = w;
        p->count = count;
        p->left = p->right = NULL;
    }
    else if (count > p->count)
        p->left = addtree2(p->left, w, count);
    else if (count < p->count)
        p->right = addtree2(p->right, w, count);
    else if (strcmp(w, p->word) < 0)
        p->left = addtree2(p->left, w, count);
    else
        p->right = addtree2(p->right, w, count);

    return p;
}

void inserttree(struct tnode *p, struct cnode **root2)
{
    if (p != NULL) 
    {
        inserttree(p->left, root2);
        *root2 = addtree2(*root2, p->word, p->count);
        inserttree(p->right, root2);
    }
}

void treeprint(struct cnode *p)
{
    if (p != NULL)
    {
        treeprint(p->left);
        printf("%d %s\n", p->count, p->word);
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

