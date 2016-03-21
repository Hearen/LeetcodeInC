/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-03-21 11:15
Description : Given an array S of n integers, find three integers in S such that the sum is closest to a given number, target. Return the sum of the three integers. You may assume that each input would have exactly one solution.

For example, given array S = {-1 2 1 -4}, and target = 1.
The sum that is closest to the target is 2. (-1 + 2 + 1 = 2).
Source      : https://leetcode.com/problems/3sum-closest/
*******************************************/
#include<stdio.h>

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
            l++, r--;
        }
    }
    if(begin < r)
        sort(nums, begin, r);
    if(l < end)
        sort(nums, l, end);
}

int abs (int a)
{
  return a > 0 ? a : -a;
}

//Accepted
//Using the sequence of the sum to search;
int threeSumClosest(int *nums, int size, int target)
{
    int l, r, t;
    int closestSum = nums[0]+nums[1]+nums[2];
    sort(nums, 0, size-1);
    for(int i = 0; i < size-2; i++)
    {
        l = i+1;
        r = size-1;
        while(r > l)
        {
            t = nums[i]+nums[l]+nums[r];
            if(t > target) r--;
            else if(t < target) l++;
            else return t;
            if(abs(target-t) < abs(target-closestSum))
                closestSum = t;
        }
    }
    return closestSum;
}

