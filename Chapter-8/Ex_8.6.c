#include <stdio.h>
#include <stdlib.h>

void *calloc_custom(unsigned n, unsigned size)
{
    unsigned total;
    unsigned char *p;
    total = n * size;
    p = malloc(total);
    if (p == NULL)
        return NULL;
    for (unsigned i = 0; i < total; i++)
        p[i] = 0;
    return (void *)p;
}

int main()
{
    int *arr;
    int n = 5;
    arr = calloc_custom(n, sizeof(int));
    if (arr == NULL)
        return 1;
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    free(arr);
    return 0;
}

