#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#define _READ 01
#define _WRITE 02
#define _EOF  04

typedef struct {
    int cnt;
    char *ptr;
    char *base;
    int flag;
    int fd;
} MY_FILE;

int fseek_custom(MY_FILE *fp, long offset, int origin);

int main() {
    MY_FILE fp;
    char buf[100];
    fp.fd = open("testfile.txt", O_RDWR | O_CREAT, 0644);
    fp.flag = _READ | _WRITE; fp.base = buf; fp.ptr = buf; fp.cnt = 0;
    fseek_custom(&fp, 10, SEEK_SET);
    write(fp.fd, "HelloWorld", 10);
    fseek_custom(&fp, 0, SEEK_SET);
    int n = read(fp.fd, buf, 20);
    for (int i = 0; i < n; i++)
    printf("%d", buf[i]);
    printf("\n");
    if(n>0)
    { 
    buf[n]='\0';
    write(1, buf, n);
    }
    close(fp.fd);
    return 0;
}

int fseek_custom(MY_FILE *fp, long offset, int origin)
{
    if (!fp)
        return EOF;
    if (fp->flag & _READ)
    {
        fp->cnt = 0;
        fp->ptr = fp->base;
    }
    if (lseek(fp->fd, offset, origin) == -1)
        return EOF;
    fp->flag &= ~_EOF;
    return 0;
}


