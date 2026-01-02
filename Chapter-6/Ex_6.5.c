#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASHSIZE 101

struct nlist {
    struct nlist *next;   
    char *name;           
    char *defn;           
};

static struct nlist *hashtab[HASHSIZE];

unsigned hash(char *s);
struct nlist *lookup(char *s);
struct nlist *install(char *name, char *defn);
int undef(char *name);

unsigned hash(char *s)
{
    unsigned hashval = 0;
    while (*s != '\0')
        hashval = *s++ + 31 * hashval;
    return hashval % HASHSIZE;
}

struct nlist *lookup(char *s)
{
    struct nlist *np;
    for (np = hashtab[hash(s)]; np != NULL; np = np->next)
        if (strcmp(s, np->name) == 0)
            return np;   
    return NULL;          
}

struct nlist *install(char *name, char *defn)
{
    struct nlist *np;
    unsigned hashval;
    if ((np = lookup(name)) == NULL)
    {
        np = (struct nlist *) malloc(sizeof(*np));
        if (np == NULL)
            return NULL;
        np->name = strdup(name);
        if (np->name == NULL)
            return NULL;
        hashval = hash(name);
        np->next = hashtab[hashval];
        hashtab[hashval] = np;
    }
    else 
    {
        free(np->defn);
    }
    np->defn = strdup(defn);
    if (np->defn == NULL)
        return NULL;
    return np;
}

int undef(char *name)
{
    struct nlist *np = NULL;
    struct nlist *prev = NULL;
    for(np = hashtab[hash(name)]; np!=NULL; np=np->next)
    {
        if((strcmp(name,np->name))==0)
        {
         if (prev == NULL)
                hashtab[hash(name)] = np->next;
         else
                prev->next = np->next;

         free(np->name);
         free(np->defn);
         free(np);
         return 1;
        }
        prev=np;
     }
     return 0;
 }    
    
int main(void)
{
    install("IN", "1");
    install("OUT", "0");
    install("IN", "5");   
    struct nlist *p;
    int n;
    p = lookup("IN");
    if (p != NULL)
        printf("IN = %s\n", p->defn);
        
    p = lookup("OUT");
    if (p != NULL)
        printf("OUT = %s\n", p->defn);
        
    n = undef("OUT");
    if(n==1)
        printf("UNDEF SUCCESSFUL\n");
    else
        printf("UNDEF UNSUCCESSFUL\n");
        
    p = lookup("OUT");
    if (p != NULL)
        printf("OUT = %s\n", p->defn); 
        
    p = lookup("UNKNOWN");
    if (p == NULL)
        printf("UNKNOWN not found\n");
    return 0;
}

