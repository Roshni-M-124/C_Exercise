#include <stdio.h>
#include <unistd.h>
#include <limits.h>

#define MAXBYTES 10240U
#define NALLOC   1024

typedef long Align;

union header {
    struct {
        union header *ptr;
        unsigned size;
    } s;
    Align x;
};

typedef union header Header;

static Header base;
static Header *freep = NULL;
static unsigned maxalloc = 0;

void myfree(void *ap);

static Header *morecore(unsigned nu)
{
    char *cp;
    Header *up;
    if (nu < NALLOC)
        nu = NALLOC;
    if (nu > UINT_MAX / sizeof(Header))
        return NULL;
    cp = sbrk(nu * sizeof(Header));
    if (cp == (char *)-1)
        return NULL;
    if (nu > maxalloc)
        maxalloc = nu;
    up = (Header *)cp;
    up->s.size = nu;
    myfree((void *)(up + 1));
    return freep;
}

void *mymalloc(unsigned nbytes)
{
    Header *p, *prevp;
    unsigned nunits;
    if (nbytes == 0 || nbytes > MAXBYTES)
        return NULL;
    if (nbytes > UINT_MAX - sizeof(Header))
        return NULL;
    nunits = (nbytes + sizeof(Header) - 1) / sizeof(Header) + 1;
    if ((prevp = freep) == NULL)
    {
        base.s.ptr = freep = prevp = &base;
        base.s.size = 0;
    }
    for (p = prevp->s.ptr; ; prevp = p, p = p->s.ptr) 
    {

        if (p != &base &&(p->s.size == 0 || p->s.size > maxalloc))
            return NULL;
        if (p->s.size >= nunits) 
        {
            if (p->s.size == nunits)
                prevp->s.ptr = p->s.ptr;
            else
            {
                p->s.size -= nunits;
                p += p->s.size;
                p->s.size = nunits;
            }
            freep = prevp;
            return (void *)(p + 1);
        }
        if (p == freep)
            if ((p = morecore(nunits)) == NULL)
                return NULL;
    }
}

void myfree(void *ap)
{
    Header *bp, *p;
    if (ap == NULL)
        return;
    if ((unsigned long)ap % sizeof(Header) != 0)
        return;
    bp = (Header *)ap - 1;
    if (bp->s.size == 0 || bp->s.size > maxalloc)
        return;
    for (p = freep; !(bp > p && bp < p->s.ptr); p = p->s.ptr)
        if (p >= p->s.ptr && (bp > p || bp < p->s.ptr))
            break;
    if (bp + bp->s.size == p->s.ptr) 
    {
        bp->s.size += p->s.ptr->s.size;
        bp->s.ptr = p->s.ptr->s.ptr;
    } 
    else
        bp->s.ptr = p->s.ptr;
    if (p + p->s.size == bp) 
    {
        p->s.size += bp->s.size;
        p->s.ptr = bp->s.ptr;
    } 
    else
        p->s.ptr = bp;
    freep = p;
}

int main()
{
    int *p = mymalloc(1000);
    if (!p)
    {
        printf("alloc failed\n");
        return 1;
    }
    p[0] = 10;
    p[1] = 20;
    printf("%d %d\n", p[0], p[1]);
    myfree(p);
    return 0;
}

