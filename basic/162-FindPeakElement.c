/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2015-12-27 11:07
Description : A peak element is an element that is greater than its neighbors.
Given an input array where num[i] ≠ num[i+1], find a peak element and return its index.
The array may contain multiple peaks, in that case return the index to any one of the peaks is fine.
You may imagine that num[-1] = num[n] = -∞.
For example, in array [1, 2, 3, 1], 3 is a peak element and your function should return the index number 2.
Source      : https://leetcode.com/problems/find-peak-element/
*******************************************/
#include <limits.h>
//AC - 0ms;
int findPeakElement0(int* nums, int numsSize)
{
    int pre = INT_MIN, post = INT_MIN;
    for(int i = 0; i < numsSize; i++)
    {
        if(i == 0)
            pre = INT_MIN;
        else
            pre = nums[i-1];
        if(i == numsSize-1)
            post = INT_MIN;
        else
            post = nums[i+1];
        if(nums[i] > pre && nums[i] > post)
            return i;
    }
    return 0;
}

int findPeakElement1(int* nums, int size)
{
    for(int i = 1; i < size; i++)
        if(nums[i] < nums[i-1]) return i-1;
    return size-1;
}

int findPeakElement(int* nums, int size)
{
    int l=0, r=size-1;
    while(l < r)
    {
        int m0 = (l+r)/2;
        int m1 = m0+1;
        if(nums[m0] < nums[m1]) l = m1;
        else r = m0;
    }
    return l;
}

