#include<stdio.h>
#include<fcntl.h>
#include <unistd.h>
#include<stdarg.h>
#include<stdlib.h>

#define PERMS 0666

void error(char *,...);

int main(int argc, char *argv[])
{
  int f1,f2,f3,n;
  char buf[BUFSIZ];
  if(argc<4)
    error("Usage: ./a.out file1 file2 outfile");
  if((f1=open(argv[1],O_RDONLY,0))==-1)
    error("can't open %s", argv[1]);
  if((f2=open(argv[2],O_RDONLY,0))==-1)
    error("can't open %s", argv[2]);  
  if((f3=creat(argv[3],PERMS))==-1)
    error("can't create %s, mode %03o",argv[2], PERMS);
  while((n=read(f1,buf,BUFSIZ))>0)
  {
    if (write(f3, buf, n) != n)
      error("write error on file %s", argv[3]);
  }
  while((n=read(f2,buf,BUFSIZ))>0)
  {
    if (write(f3, buf, n) != n)
      error("write error on file %s", argv[3]);
  }
  return 0;
}  
  
void error(char *fmt, ...)
{
  va_list args;
  va_start(args, fmt);
  fprintf(stderr, "error: ");
  vfprintf(stderr, fmt, args);
  fprintf(stderr, "\n");
  va_end(args);
  exit(1);
}  
