/*******************************************
author: lhearen
e-mail: lhearen@126.com
time  :	2015-12-02 21:29
description: 
Source: https://leetcode.com/problems/two-sum/
*******************************************/
//using another index array to record the indexes' changes;
//using the sequence of the sum to find the target;
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))
void swap(int* p, int* q)
{
    int t=*p; *p=*q; *q=t;
}
void sort(int* nums, int* indexes, int begin, int end)
{
    int l=begin, r=end;
    int v = nums[l+(r-l)/2];
    while(l <= r)
    {
        while(nums[l] < v) l++;
        while(nums[r] > v) r--;
        if(l <= r)
        {
            swap(nums+l, nums+r);
            swap(indexes+l, indexes+r);
            l++;
            r--;
        }
    }
    if(begin < r)
        sort(nums, indexes, begin, r);
    if(l < end)
        sort(nums, indexes, l, end);
}
int* twoSum(int *nums, int size, int target)
{
    int* indexes = (int*)malloc(sizeof(int)*size);
    for(int i = 0; i < size; i++)
        indexes[i] = i;
    sort(nums, indexes, 0, size-1);
    int* result = (int*)malloc(sizeof(int)*2);
    int l=0, r=size-1;
    while(l < r)
    {
        while(nums[l]+nums[r] < target) l++;
        while(nums[l]+nums[r] > target) r--;
        if(nums[l]+nums[r] == target)
        {
            result[0] = MIN(indexes[l], indexes[r]);
            result[1] = MAX(indexes[l], indexes[r]);
            return result;
        }
    }
}
