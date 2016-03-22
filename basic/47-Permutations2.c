/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-01-13 20:22
Description : Given a collection of numbers that might contain duplicates, return all possible unique permutations.

For example,
[1,1,2] have the following unique permutations:
[1,1,2], [1,2,1], and [2,1,1].
Source      : https://leetcode.com/problems/permutations-ii/
*******************************************/
#include <stdbool.h>
void swap(int* p, int* q)
{
    int t = *p; *p = *q; *q = t;
}

void shellSort(int *nums, int size)
{
    int h = 1;
    for(; h <= size/9; h = 3 * h + 1);
    for(; h > 0; h /= 3)
    {
        for(int i = h; i < size; i++)
        {
            int tmp = nums[i];
            int j = i;
            while(j >= h && tmp < nums[j - h])//This condition is quite critical;
            {
                nums[j] = nums[j - h];
                j -= h;
            }
            nums[j] = tmp;
        }
    }
}

//AC - 4ms;
//Get the next bigger permutation;
int** permuteUnique(int* nums, int size, int* returnSize)
{
    *returnSize = 0;
    int count = 1;
    for(int i = 1; i <= size; i++)
        count *= i;
    int** arr = (int**)malloc(sizeof(int*)*count);
    shellSort(nums, size);
    arr[*returnSize] = (int*)malloc(sizeof(int)*size);
    for(int i = 0; i < size; i++)
        arr[*returnSize][i] = nums[i];
    (*returnSize)++;
    int i = size-1, j = 0;
    while(true)
    {
        for(i=size-1; i > 0; i--) //search for a pair of neighbors while i+1 is bigger than i;
           if(nums[i-1] < nums[i]) 
               break;
        if(i == 0) //reach the end;
            break;
        for(j=size-1; j > i-1 ;j--) //search for a element after i-1 which is bigger than i-1;
            if(nums[j] > nums[i-1])
                break;
        swap(nums+i-1, nums+j);
        j = size-1;
        while(i<j) //reverse all the elements after i-1;
        {
            swap(nums+i++, nums+j--);
        }
        arr[*returnSize] = (int*)malloc(sizeof(int)*size);
        for(int i = 0; i < size; i++) //collect the next bigger permutation;
            arr[*returnSize][i] = nums[i];
        (*returnSize)++;
    }
    return arr;
}
