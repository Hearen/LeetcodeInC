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
void search(int* nums, int size, int begin, int* stack, int top, int** columnSizes, int* returnSize, int*** table)
{
    if(begin!=0 && top==-1) return ;
    (*returnSize)++;
    *columnSizes = (int*)realloc(*columnSizes, sizeof(int)*(*returnSize));
    (*columnSizes)[*returnSize-1] = top+1;
    *table = (int**)realloc(*table, sizeof(int*)*(*returnSize));
    (*table)[*returnSize-1] = (int*)malloc(sizeof(int)*(top+1));
    for(int i = 0; i <= top; i++)
        (*table)[*returnSize-1][i] = stack[i];
    for(int i = begin; i < size; i++)
    {
        if(i == begin || nums[i] != nums[i-1])
        {
            stack[++top] = nums[i];
            search(nums, size, i+1, stack, top, columnSizes, returnSize, table);
            top--;
        }
    }
}

void sort(int* nums, int begin, int end)
{
    int l=begin, r=end;
    int v = nums[l+(r-l)/2];
    while(l <= r)
    {
        while(nums[l] < v) l++;
        while(nums[r] > v) r--;
        if(l <= r)
        {
            int t=nums[l]; nums[l]=nums[r]; nums[r]=t;
            l++;
            r--;
        }
    }
    if(begin < r)
        sort(nums, begin, r);
    if(l < end)
        sort(nums, l, end);
}

//AC - 4ms;
int** subsetsWithDup(int* nums, int size, int** columnSizes, int* returnSize)
{
    sort(nums, 0, size-1);
    *columnSizes = (int*)malloc(sizeof(int));
    int** table = (int**)malloc(sizeof(int*));
    int* stack = (int*)malloc(sizeof(int)*size);
    int top = -1;
    search(nums, size, 0, stack, top, columnSizes, returnSize, &table);
    return table;
}
