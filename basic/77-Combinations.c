/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-03-03 15:01
Description : Given two integers n and k, return all possible combinations of k numbers out of 1 ... n.
For example,
If n = 4 and k = 2, a solution is:

[
[2,4],
[3,4],
[2,3],
[1,2],
[1,3],
[1,4],
]
Source      : https://leetcode.com/problems/combinations/
*******************************************/
void traverse(int* nums, int size, int begin, int k, int* stack, int top, int*** arr, int** colSize, int* returnSize)
{
    if(top+1==k)
    {
        *returnSize += 1;
        *colSize = (int*)realloc(*colSize, sizeof(int)*(*returnSize));
        (*colSize)[*returnSize-1] = k;
        *arr = (int**)realloc(*arr, sizeof(int*)*(*returnSize));
        (*arr)[*returnSize-1] = (int*)malloc(sizeof(int)*k);
        for(int i = 0; i < k; i++)
            (*arr)[*returnSize-1][i] = stack[i];
        return ;
    }
    for(int i = begin; i < size; i++)
    {
        stack[top+1] = nums[i];
        traverse(nums, size, i+1, k, stack, top+1, arr, colSize, returnSize);
    }
}

//AC - 4ms;
int** combine(int n, int k, int** colSize, int* returnSize)
{
    int *nums = (int*)malloc(sizeof(int)*n);
    for(int i = 0; i < n; i++)
        nums[i] = i+1;
    int *stack = (int*)malloc(sizeof(int)*k);
    int top = -1;
    *returnSize = 0;
    int **arr = (int**)malloc(sizeof(int*));
    traverse(nums, n, 0, k, stack, top, &arr, colSize, returnSize);
    return arr;
}
