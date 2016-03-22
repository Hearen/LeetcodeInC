/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-01-13 20:07
Description : Given a collection of distinct numbers, return all possible permutations.

For example,
[1,2,3] have the following permutations:
[1,2,3], [1,3,2], [2,1,3], [2,3,1], [3,1,2], and [3,2,1].
Source      : https://leetcode.com/problems/permutations/
*******************************************/
void swap(int* p, int* q)
{
    int t = *p; *p = *q; *q = t;
}
void search(int* nums, int size, int*** arr, int* returnSize, int begin, int end)
{
    if(begin == end)
    {
        (*returnSize)++;
        *arr = (int**)realloc(*arr, sizeof(int*)*(*returnSize));
        (*arr)[*returnSize-1] = (int*)malloc(sizeof(int)*size);
        for(int i = 0; i < size; i++)
            (*arr)[*returnSize-1][i] = nums[i];
        return;
    }
    for(int i = begin; i <= end; i++)
    {
        swap(nums+begin, nums+i); //try to use each element as the head;
        search(nums, size, arr, returnSize, begin+1, end);
        swap(nums+begin, nums+i);
    }
}

//AC - 4ms;
int** permute(int* nums, int size, int* returnSize)
{
    *returnSize = 0;
    int** arr = (int**)malloc(sizeof(int*));
    search(nums, size, &arr, returnSize, 0, size-1);
    return arr;
}
