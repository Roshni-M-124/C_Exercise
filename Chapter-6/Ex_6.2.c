#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>

#define DEFAULT 6
#define MAXWORD 100

struct tnode
{
  char *word;
  struct tnode *left;
  struct tnode *right;
};

struct tnode *addtree (struct tnode *, char *);
struct tnode *talloc ();
void treeprint (struct tnode *,int);
int getword (char *,int);
char * str_dup (char *);
int strn_cmp (char *, char *, int);
int iskeyword (char *);

char *keywords[] = {"auto","break","case","char","const","continue","default","do",
    "double","else","enum","extern","float","for","goto","if","int","long","register",
    "return","short","signed","sizeof","static","struct","switch","typedef","union",
    "unsigned","void","volatile","while", };

#define NKEYS (sizeof(keywords)/sizeof(char *))

int main(int argc,char *argv[])
{
 int prefix;
 prefix = (argc>1)? atoi(argv[1]) : DEFAULT;
 
 struct tnode *root = NULL;
 char word[MAXWORD];
 
 while((getword(word,MAXWORD))!=EOF)
 {
 if (isalpha(word[0]) && !iskeyword(word))
    root = addtree(root,word);
 }
 treeprint(root,prefix);
 return 0;
}

int getword (char *word,int lim)
{
    int c, d;
    char *w = word;
    while (isspace(c = getchar()))
        ;
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
        if (!isalnum(*w = getchar()) && *w != '_') {
            ungetc(*w, stdin);
            break;
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

struct tnode *talloc ()
{
 return (struct tnode *)malloc(sizeof(struct tnode));
}

struct tnode *addtree (struct tnode *p, char *w)
{
  int comp;
  if(p==NULL)
  {
    p = talloc();
    p-> word = str_dup(w);
    p->left = NULL;
    p-> right = NULL;
  }
  else if ((comp = strcmp (p->word,w))<0)
    p->right = addtree(p->right,w);
  else if (comp > 0)
    p->left =  addtree(p->left,w);
  return p;
}    
    
void treeprint (struct tnode *p,int prefix)
{
    static char *last = NULL;
    if (p != NULL) 
    {
        treeprint(p->left, prefix);
        if (last == NULL || strn_cmp(last, p->word, prefix) != 0) 
            printf("\n");
        printf("%s\n", p->word);
        last = p->word;
        treeprint(p->right, prefix);
    }
}

char * str_dup (char *s)
{
 char *p = (char *)malloc(strlen(s)+1);
 if(p!=NULL)
    strcpy(p,s);
 return p;
} 

int strn_cmp (char *s1, char *s2, int n)
{
  for(int i=0;i<n;i++)
  {
      if(*s1==*s2 && *s1!=0 && *s2 !=0)
      {
        s1++;
        s2++;
      }  
      else
        return *s1 - *s2;
  }
  return 0;
}  
