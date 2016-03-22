/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-02-25 11:31
Description : Given a set of candidate numbers (C) and a target number (T), find all unique combinations in C where the candidate numbers sums to T.
The same repeated number may be chosen from C unlimited number of times.
Note:
All numbers (including target) will be positive integers.
Elements in a combination (a1, a2, … , ak) must be in non-descending order. (ie, a1 ≤ a2 ≤ … ≤ ak).
The solution set must not contain duplicate combinations.
For example, given candidate set 2,3,6,7 and target 7, 
A solution set is: 
[7] 
[2, 2, 3] 
Source      : https://leetcode.com/problems/combination-sum/
*******************************************/
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
            int t = nums[l];
            nums[l] = nums[r];
            nums[r] = t;
            l++;
            r--;
        }
    }
    if(begin < r)
        sort(nums, begin, r);
    if(l < end)
        sort(nums, l, end);
}

void helper(int* nums, int size, int target, int* stack, int top, int*** arr, int** colSizes, int* returnSize)
{
    if(target == 0) //valid set, collect the stack;
    {
        *returnSize += 1;
        *colSizes = (int*)realloc(*colSizes, sizeof(int)*(*returnSize));
        (*colSizes)[*returnSize-1] = top+1;
        *arr = (int**)realloc(*arr, sizeof(int*)*(*returnSize));
        (*arr)[*returnSize-1] = (int*)malloc(sizeof(int)*(top+1));
        for(int i = 0; i <= top; i++)
            (*arr)[*returnSize-1][i] = stack[i];
        return ;
    }
    for(int i = 0; i < size; i++)
    {
        if(nums[i] > target) break; //needless to check further;
        if(nums[i]>=stack[top]) //ensure ascending order;
        {
            stack[top+1] = nums[i];
            helper(nums, size, target-nums[i], stack, top+1, arr, colSizes, returnSize);
        }
    }
}

//AC - 4ms;
int** combinationSum(int* nums, int size, int target, int** colSizes, int* returnSize)
{
    sort(nums, 0, size-1);
    int** arr = (int**)malloc(sizeof(int*));
    *returnSize = 0;
    int* stack = (int*)malloc(sizeof(int)*(target/nums[0]+1));
    int top = -1;
    helper(nums, size, target, stack, top, &arr, colSizes, returnSize);
    return arr;
}
