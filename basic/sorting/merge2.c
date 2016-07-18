#include"utils.h"

/*
 *Merging sort features:
 *require space N, time NlogN;
 *ignore the sequence of the sorting sequence;
 *access the elements in sequence;
 *it's a stable sorting method.
 */


//checking the reasoning and initial state can ensure the recursive correctness;
void mergeSort(int *a, int *aux, int l, int r)
{
    if(l >= r) return ;
    int m = (l + r) / 2;
    mergeSort(aux, a, l, m);
    mergeSort(aux, a, m + 1, r);
    mergeAB(a, aux, l, m, r);
}

void sort(int *a, int l, int r)
{
    int *aux = (int*)malloc(sizeof(int)*(r-l+1));
    memcpy(aux, a, sizeof(int)*(r-l+1));
    mergeSort(a, aux, l, r);
}

int main()
{
    int numbers[] = {0};
    int size = randomIntArray(&numbers, SIZE, 0, MAX);
    printArray(numbers, size);
    checkAscending(numbers, size);
    printf("After sorting:\n***********************\n");
    sort(numbers, 0, size - 1);
    printArray(numbers, size);
    checkAscending(numbers, size);
    return 0;
}
