/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-03-21 10:45
Description : Given an array of integers, return indices of the two numbers such that they add up to a specific target.
You may assume that each input would have exactly one solution.
Example:
Given nums = [2, 7, 11, 15], target = 9,
Because nums[0] + nums[1] = 2 + 7 = 9,
return [0, 1].
Source      : https://leetcode.com/problems/two-sum/ 
*******************************************/
//using another index array to record the indexes' changes;
//using the sequence of the sum to find the target;
//a trick method when using high-level language is to use hashmap to directly search the left;
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
