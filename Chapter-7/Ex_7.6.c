#include<stdio.h>
#include<string.h>

void fcomp(FILE *, FILE *);

int main(int argc,char *argv[])
{
  FILE *fp1,*fp2;
  if (argc < 3)
  {
    printf("FORMAT: %s file1 file2\n", argv[0]);
    return 1;
  }
  fp1=fopen(argv[1],"r");
  fp2=fopen(argv[2],"r");
  if (fp1 == NULL || fp2 == NULL)
  {
    printf("Error opening file\n");
    return 1;
  }
  fcomp(fp1,fp2);
  return 0;
}

void fcomp(FILE *f1, FILE *f2)
{
  char s1[100], s2[100];
  int line = 1;
  while (1)
  {
    char *r1 = fgets(s1, 100, f1);
    char *r2 = fgets(s2, 100, f2);
    if (r1 == NULL && r2 == NULL) 
    {
        printf("Files are identical\n");
        return;
    }
    if (r1 == NULL || r2 == NULL) 
    {
        printf("Files differ in length at line %d\n", line);
        return;
    }
    if (strcmp(s1, s2) != 0) 
    {
        printf("Difference at line %d:\n", line);
        printf("File1: %d", s1);
        printf("File2: %s", s2);
        return;
    }
    line++;
  }
}

  
