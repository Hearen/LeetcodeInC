#include"utils.h"
/*
 *Merging sort features:
 *require space N, time NlogN;
 *ignore the sequence of the sorting sequence;
 *access the elements in sequence;
 *it's a stable sorting method.
 */


void sort(int *a, int l, int r)
{
    if(r - l < 10)
    {
        insertionSort(a, l, r);
        return;
    }
    int m = (l + r) / 2;
    sort(a, l, m);
    sort(a, m + 1, r);
    merge(a, l, m, r);
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
