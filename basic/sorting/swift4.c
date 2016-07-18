#include"utils.h"

void sort(int *a, int l, int r)
{
    stackInit();
    int i, j, v;
    int l0, r0;
    push(l, r);
    while(!isEmpty())
    {
        r0 = j = pop();
        l0 = i = pop();
        v = a[(i+j)/2];
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
        if(j-l0 > r0-i)
        {
            if(j > l0)
                push(l0, j);
            if(i < r0)
                push(i, r0);
        }
        else
        {
            if(i < r0)
                push(i, r0);
            if(j > l0)
                push(l0, j);
        }
    }
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
