#include"utils.h"
int partition(int *nums, int l ,int r)
{
    int i = l;
    int j = r;
    int v = nums[(i+j)/2];
    while(i <= j)
    {
        while(nums[i] < v) i++;
        while(nums[j] > v) j--;
        if(i <= j)
        {
            swap(nums + i, nums + j);
            i++;
            j--; 
        } 
    }
    return i; 
}

void sort(int *nums, int l, int r)
{
    int i = partition(nums, l, r);
    if(l < i - 1) sort(nums, l, i - 1);
    if(r > i) sort(nums, i, r);
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
