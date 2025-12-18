#include<stdio.h>

int binsearch(int x,int v[],int n);
int main()
{
    int arr[]={2,4,6,7,9,40,45,46,48,50,52};
    printf("%d",binsearch(40,arr,11));

    return 0;
}
int binsearch(int x,int v[],int n)
{
    int low,high,mid;
    low=0;
    high=n-1;
    mid = ( low + high ) / 2;
    while(low < high && x != v[mid])
    {
        if( x > v[mid])
            low = mid+1;
        else
            high = mid -1;

        mid = ( low + high)/2;
    }
    if(x==v[mid])
        return mid;
    else
        return -1;
}
