#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

#define EOF     (-1)
#define BUFSIZ  1024
#define OPEN_MAX 20
#define PERMS   0666

typedef struct _iobuf
{
    int cnt;       
    char *ptr;      
    char *base;     
    int fd;         
    int read;
    int write;
    int unbuf;
    int eof;
    int err;
} FILE;

FILE _iob[OPEN_MAX] = {
    { 0, NULL, NULL, 0, 1, 0, 0, 0, 0 }, 
    { 0, NULL, NULL, 1, 0, 1, 0, 0, 0 }, 
    { 0, NULL, NULL, 2, 0, 1, 1, 0, 0 }  
};

#define stdin  (&_iob[0])
#define stdout (&_iob[1])
#define stderr (&_iob[2])

FILE *fopen(const char *name, const char *mode);
int _fillbuf(FILE *fp);

#define getc(p) (--(p)->cnt >= 0 ? (unsigned char)*(p)->ptr++ : _fillbuf(p))

FILE *fopen(const char *name, const char *mode)
{
    int fd;
    FILE *fp;
    if (*mode != 'r' && *mode != 'w' && *mode != 'a')
        return NULL;
    for (fp = _iob; fp < _iob + OPEN_MAX; fp++)
        if (!fp->read && !fp->write)
            break;
    if (fp >= _iob + OPEN_MAX)
        return NULL;
    if (*mode == 'w')
        fd = creat(name, PERMS);
    else if (*mode == 'a') 
    {
        if ((fd = open(name, O_WRONLY)) == -1)
            fd = creat(name, PERMS);
        lseek(fd, 0L, SEEK_END);
    } 
    else
        fd = open(name, O_RDONLY);
    if (fd == -1)
        return NULL;
    fp->fd = fd;
    fp->cnt = 0;
    fp->base = NULL;
    fp->ptr = NULL;
    fp->read  = (*mode == 'r');
    fp->write = (*mode != 'r');
    fp->unbuf = 0;
    fp->eof   = 0;
    fp->err   = 0;
    return fp;
}

int _fillbuf(FILE *fp)
{
    int bufsize;
    if (!fp->read || fp->eof || fp->err)
        return EOF;
    bufsize = fp->unbuf ? 1 : BUFSIZ;
    if (fp->base == NULL)
    {
        fp->base = (char *)malloc(bufsize);
        if (fp->base == NULL)
        {
            fp->err = 1;
            return EOF;
        }
    }
    fp->ptr = fp->base;
    fp->cnt = read(fp->fd, fp->ptr, bufsize);
    if (fp->cnt <= 0)
    {
        if (fp->cnt == 0)
            fp->eof = 1;
        else
            fp->err = 1;
        fp->cnt = 0;
        return EOF;
    }
    fp->cnt--;
    return (unsigned char)*fp->ptr++;
}

int main(int argc, char *argv[])
{
    FILE *fp;
    int c;
    if (argc < 2)
    {
        write(1,"Usage: ./a.out filename\n", 25);
        return 1;
    }
    fp = fopen(argv[1], "r");
    if (fp == NULL)
    {
        write(1, "Failed to open file\n", 20);
        return 1;
    }
    while ((c = getc(fp)) != EOF) 
    {
        write(1, &c, 1); 
    }
    return 0;
}
