#include <unistd.h>
#include <stdlib.h>

#define EOF        (-1)
#define BUFSIZ     1024
#define OPEN_MAX   20

#define _READ   01
#define _WRITE  02
#define _UNBUF  04
#define _EOF    010
#define _ERR    020

typedef struct _iobuf {
    int cnt;        
    char *ptr;      
    char *base;     
    int flag;       
    int fd;         
} FILE;

FILE _iob[OPEN_MAX] = {
    { 0, NULL, NULL, _READ,  0 },   
    { 0, NULL, NULL, _WRITE, 1 },  
    { 0, NULL, NULL, _WRITE | _UNBUF, 2 }  
};

int _flushbuf(int c, FILE *fp)
{
    int num_written, bufsize;
    char *buf;
    if ((fp->flag & (_WRITE | _ERR)) != _WRITE)
        return EOF;
    if (fp->base == NULL && !(fp->flag & _UNBUF))
    {
        if ((buf = (char *)malloc(BUFSIZ)) == NULL) 
        {
            fp->flag |= _UNBUF;
        } 
        else 
        {
            fp->base = buf;
            fp->ptr = buf;
            fp->cnt = BUFSIZ - 1;
        }
    }
    if (fp->flag & _UNBUF)
    {
        if (c == EOF)
            return EOF;
        if (write(fp->fd, &c, 1) != 1) 
        {
            fp->flag |= _ERR;
            return EOF;
        }
        return c;
    }
    bufsize = fp->ptr - fp->base;
    if (bufsize > 0) 
    {
        num_written = write(fp->fd, fp->base, bufsize);
        if (num_written != bufsize) 
        {
            fp->flag |= _ERR;
            return EOF;
        }
    }
    fp->ptr = fp->base;
    fp->cnt = BUFSIZ - 1;
    if (c != EOF) 
    {
        *fp->ptr++ = c;
        fp->cnt--;
    }
    return c;
}

int fflush(FILE *fp)
{
    int i;
    if (fp == NULL) 
    {
        for (i = 0; i < OPEN_MAX; i++) 
        {
            if ((_iob[i].flag & _WRITE) &&
                fflush(&_iob[i]) == EOF)
                return EOF;
        }
        return 0;
    }
    if (!(fp->flag & _WRITE))
        return 0;
    return (_flushbuf(EOF, fp) == EOF) ? EOF : 0;
}

int fclose(FILE *fp)
{
    int rc;
    if (fp == NULL)
        return EOF;
    rc = fflush(fp);
    if (close(fp->fd) == -1)
        rc = EOF;
    if (fp->base != NULL)
        free(fp->base);
    fp->cnt = 0;
    fp->ptr = NULL;
    fp->base = NULL;
    fp->flag = 0;
    fp->fd = -1;
    return rc;
}

int main(void)
{
    FILE *fp = &_iob[1];   
    _flushbuf('H', fp);
    _flushbuf('i', fp);
    _flushbuf('\n', fp);
    fflush(fp);
    fclose(fp);
    return 0;
}
