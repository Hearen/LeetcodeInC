#include"utils.h"

void sort(int *a, int l, int r)
{
    int i = l, j = r;
    if(j - i < 20)
    {
        insertionSort(a, i, j);
        return;
    }
    int mid = (i + j) / 2;
    swap(a + i, minP(a + i, minP(a + mid, a + j)));
    swap(a + j, maxP(a + j, a + mid));
    int v = a[mid];
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
