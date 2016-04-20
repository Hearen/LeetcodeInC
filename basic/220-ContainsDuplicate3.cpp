/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-01-21 09:09
Description : Given an array of integers, find out whether there are two distinct indices i and j in the array such that the difference between nums[i] and nums[j] is at most t and the difference between i and j is at most k.
Source      : https://leetcode.com/problems/contains-duplicate-iii/
*******************************************/
#include <math.h>
#include <stdbool.h>
#include <vector.h>
//AC - 8ms;
void swap(int* p, int* q)
{
    int t=*p; *p=*q; *q=t;
}

void sort(int* nums, int* indexes, int begin, int end)
{
    int l=begin, r=end;
    int v = nums[(l+r)/2];
    while(l <= r)
    {
        while(nums[l] < v) l++;
        while(nums[r] > v) r--;
        if(l <= r)
        {
            swap(nums+l, nums+r);
            swap(indexes+l, indexes+r);
            l++; r--;
        }
    }
    if(begin < r)
        sort(nums, indexes, begin, r);
    if(l < end)
        sort(nums, indexes, l, end);
}
bool containsNearbyAlmostDuplicate1(int* nums, int size, int k, int t)
{
    int *indexes = (int*)malloc(sizeof(int)*size);
    for(int i = 0; i < size; i++)
        indexes[i] = i;
    sort(nums, indexes, 0, size-1);
    for(int i = 0; i < size; i++)
    {
        int top = nums[i]+t;
        for(int j = i+1; j < size && nums[j] <= top; j++)
            if(abs(indexes[i] - indexes[j]) <= k)
                return true;
    }
    return false;
}

//using set.lower_bound to check the range;
bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, int t) 
{
    set<int> window; // set is ordered automatically 
    for (int i = 0; i < nums.size(); i++) 
    {
        if (i > k) window.erase(nums[i-k-1]); // keep the set contains nums i j at most k
        /*|x - nums[i]| <= t  ==> -t <= x - nums[i] <= t;*/
        auto pos = window.lower_bound(nums[i] - t); // x-nums[i] >= -t ==> x >= nums[i]-t 
        /*x - nums[i] <= t ==> |x - nums[i]| <= t    */
        if (pos != window.end() && *pos - nums[i] <= t) return true;
        window.insert(nums[i]);
    }
    return false;
}
