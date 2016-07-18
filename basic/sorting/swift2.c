#include"utils.h"

void sort(int *a, int l, int r)
{
    int v = a[(l+r)/2];
    int i = l, j = r;
    while(i <= j)
    {
        while(a[i] < v)
            i++;
        while(a[j] > v)
            j--;
        if(i <= j)
        {
            swap(a+i, a+j);
            i++;
            j--;
        }
    }
    if(l < j)
        sort(a, l, j);
    if(i < r)
        sort(a, i, r);
}

void main()
{
    int numbers[SIZE];
    randomIntArray(numbers, SIZE, 0, MAX);
    printArray(numbers, SIZE);
    checkAscending(numbers, SIZE);
    printf("After sorting:\n***********************\n");
    sort(numbers, 0, SIZE - 1);
    printArray(numbers, SIZE);
    checkAscending(numbers, SIZE);
}
