/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-01-02 20:29
Description : Given a collection of integers that might contain duplicates, nums, return all possible subsets.
Note:
Elements in a subset must be in non-descending order.
The solution set must not contain duplicate subsets.
For example,
If nums = [1,2,2], a solution is:

[
[2],
[1],
[1,2,2],
[2,2],
[1,2],
[]
]
Source      : https://leetcode.com/problems/subsets-ii/
*******************************************/
void search(int* nums, int size, int begin, int* stack, int top, int** columnSizes, int* count, int** table)
{
    if(begin != 0 && top == -1)
        return;
    (*columnSizes)[*count] = top+1;
    table[*count] = (int*)malloc(sizeof(int)*(top+1));
    for(int i = 0; i <= top; i++)
        table[*count][i] = stack[i];
    (*count)++;
    for(int i = begin; i < size; i++)
    {
        if(i == begin || nums[i] != nums[i-1])
        {
            stack[++top] = nums[i];
            search(nums, size, i+1, stack, top, columnSizes, count, table);
            top--;
        }
    }
}

//AC - 4ms;
int** subsetsWithDup(int* nums, int size, int** columnSizes, int* returnSize)
{
    int i, min = 0;
    for(i = 0; i < size; i++)
        if(nums[i] < nums[min])
            min = i;
    int t = nums[min];
    nums[min] = nums[0];
    nums[0] = t;
    for(i = 1; i < size; i++)
    {
        t = nums[i];
        int j = i;
        while(t < nums[j-1])
        {
            nums[j] = nums[--j];
        }
        nums[j] = t;
    }
    *returnSize = 1;
    for(int i = 0; i < size; i++)
        *returnSize *= 2;
    *columnSizes = (int*)malloc(sizeof(int)*(*returnSize));
    int** table = (int**)malloc(sizeof(int*)*(*returnSize));
    int* stack = (int*)malloc(sizeof(int)*size);
    int top = -1;
    int tmp = 0;
    int* count = &tmp;
    search(nums, size, 0, stack, top, columnSizes, count, table);
    *returnSize = *count;
    return table;
}
