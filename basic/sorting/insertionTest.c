#include"utils.h"

void sort(int * nums, int size)
{
    int i, j, min = 0;
    for(i = 1; i < size; i++)
        if(nums[min] > nums[i])
            min = i;
    swap(nums, nums + min);

    int tmp = 0;
    for(i = 2; i < size; i++)
    {
        tmp = nums[i];
        j = i;
        while(tmp < nums[j - 1])
        {
            nums[j] = nums[j - 1];
            j--;
        }
        nums[j] = tmp;
    }
}

void main()
{
    int numbers[SIZE];
    randomIntArray(numbers, SIZE, 0, MAX);
    printArray(numbers, SIZE);
    checkAscending(numbers, SIZE);
    printf("After sorting:\n***********************\n");
    sort(numbers, SIZE);
    printArray(numbers, SIZE);
    checkAscending(numbers, SIZE);
}
