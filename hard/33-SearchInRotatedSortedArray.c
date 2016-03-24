/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-03-21 16:46
Description : Suppose a sorted array is rotated at some pivot unknown to you beforehand.
(i.e., 0 1 2 4 5 6 7 might become 4 5 6 7 0 1 2).
You are given a target value to search. If found in the array return its index, otherwise return -1.
You may assume no duplicate exists in the array.
Source      : https://leetcode.com/problems/search-in-rotated-sorted-array/
*******************************************/
int searchIndex0(int* nums, int begin, int end, int target)
{
    if(end < begin) return -1;
    int m = (begin+end)/2;
    int mid = nums[m];
    if(nums[m] == target) return m;
    else
    {
        int right = searchIndex(nums, m+1, end, target);
        return right==-1? searchIndex(nums, begin, m-1, target) : right;
    }
}

//AC - 0ms;
int search0(int* nums, int size, int target)
{
    return searchIndex(nums, 0, size-1, target);
}

int search1(int* nums, int size, int target)
{
    int l=0, r=size-1;
    while(l < r)
    {
        int m = (l+r)/2;
        if(nums[m] == target) return m;
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
    return nums[l]==target? l : -1;
}

//AC - 0ms;
//actually the rotating process is a right-moving process;
int search(int* nums, int size, int target)
{
    int l=0, r=size-1;
    while(l < r) //searching for the rotating position;
    {
        int m=(l+r)/2;
        if(nums[m]>nums[r]) l=m+1;
        else r=m;
    }
    int s = l;
    l=0, r=size-1;
    while(l <= r)
    {
        int m = (l+r)/2;
        int real = (m+s)%size;
        if(nums[real] == target) return real;
        if(nums[real] < target) l=m+1;
        else r=m-1;
    }
    return -1;
}
