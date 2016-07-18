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
    int unit = 20;
    if(r - l < unit)
    {
        insertionSort(a, l, r);
        return;
    }
    for(int i = l; i < r; i += unit)
        insertionSort(a, i, min(i + unit - 1, r));
    for(int m = unit; m < r - l; m += m)
        for(int i = l; i <= r - m; i += 2 * m)//the range is rather critical!
            merge(a, i, m + i - 1, min(i + 2 * m - 1, r));
}


void main()
{
    int numbers[SIZE];
    randomIntArray(numbers, SIZE, 0, MAX);
    printArray(numbers, SIZE);
    checkAscending(numbers, SIZE);
    printf("\nAfter sorting:\n***********************\n");
    sort(numbers, 0, SIZE - 1);
    printArray(numbers, SIZE);
    checkAscending(numbers, SIZE);
    /*printf("\nAfter insertion sorting:\n***********************\n");*/
    /*insertionSort(numbers, 0, SIZE - 1);*/
    /*printArray(numbers, SIZE);*/
    /*checkAscending(numbers, SIZE);*/
}
