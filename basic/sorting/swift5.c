#include"utils.h"
void sort(int *a, int l, int r)
{
    int i, j, v;
    i = l, j = r;
    v = a[(i + j)/2];
    if(j - i < 20)
    {
        insertionSort(a, i, j);
        return;
    }
    while(i <= j)
    {
        while(a[i] < v)
            i++;
        while(a[j] > v)
            j--;
        if(i <= j)
        {
            swap(a + i, a + j);
            i++;
            j--;
        }
    }
    if(j > l)
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
