#include"utils.h"

int partition(int *nums, int low, int high)
{
    int mid = (low + high)/2;
    int tmp = nums[mid];
    int i = low, j = high;
    while(1)
    {
        while(nums[i] < tmp) i++;
        while(nums[j] > tmp) j--;
        if(j <= i) break;
        swap(nums + i, nums + j);
    }
    swap(nums + i, nums + j);
    return i;
}

void sort(int *nums, int low, int high)
{
    if(low > high) return;
    int mid = partition(nums, low, high);
    sort(nums, low, mid - 1);
    sort(nums, mid + 1, high);
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
