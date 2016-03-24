/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-03-23 21:07
Description : Follow up for "Search in Rotated Sorted Array":
What if duplicates are allowed?
Would this affect the run-time complexity? How and why?

Write a function to determine if a given target is in the array.
Source      : https://leetcode.com/problems/search-in-rotated-sorted-array-ii/
*******************************************/
#include <cstdbool.h>
bool search0(int* nums, int size, int target)
{
    int l=0, r=size-1;
    while(l < r)
    {
        int m = (l+r)/2;
        if(nums[m] == target) return true;
        while(nums[l]==nums[m] && l!=m) l++;
        while(nums[r]==nums[m] && r!=m) r--;
        if(nums[l] <= nums[m])
        {
            if(nums[l]<=target && target<nums[m]) r = m-1;
            else l = m+1;
        }
        else
        {
            if(nums[m]<target && target<=nums[r]) l = m+1;
            else r = m-1;
        }
    }
    return nums[l]==target;
}

bool search(int* nums, int size, int target)
{
    int l=0, r=size-1;
    int m = 0;
    while(l < r)
    {
        m = (l+r)/2;
        if(nums[m] == target) return true;
        if(nums[m] > nums[r])
        {
            if(nums[m]>target && nums[l]<=target) r = m;
            else l = m+1;
        }
        else if(nums[m] < nums[r])
        {
            if(nums[m]<target && nums[r]>=target) l = m+1;
            else r = m;
        }
        else r--;
    }
    return nums[l]==target;
}
