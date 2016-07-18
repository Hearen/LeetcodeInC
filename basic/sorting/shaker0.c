#include"utils.h"


void sort(int * nums, int size)
{
    bool isSorted = false;
    int index0 = 0, index1 = size - 1;
    for(int k = 0; k < size; k++)
    {
        if(k % 2 == 0)
        {
            for(int i = index0; i < index1; i++)
            {
                isSorted = true;
                for(int j = index1; j > i; j--)
                {
                    if(nums[j] < nums[j - 1])
                    {
                        isSorted = false;
                        swap(nums + j, nums + j - 1);
                    }
                }
                if(isSorted)
                    break;
            }
            index0++;
        }
        else
        {
            for(int i = index0; i < index1 - 1; i++)
            {
                isSorted = true;
                for(int j = index0; j < index1 - i; j++)
                {
                    if(nums[j] > nums[j+1])
                    {
                        isSorted = false;
                        swap(nums + j, nums + j);
                    }
                }
                if(isSorted)
                    break;
            }
            index1--;
        }
        if(isSorted)
            break;
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
