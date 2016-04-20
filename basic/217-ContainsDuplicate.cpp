/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-01-19 08:55
Description : Given an array of integers, find if the array contains any duplicates. Your function should return true if any value appears at least twice in the array, and it should return false if every element is distinct.
Source      : https://leetcode.com/problems/contains-duplicate/
*******************************************/
#include <vector.h>
#include <stdbool.h>
//AC - 1620mc;
bool containsDuplicate0(int* nums, int size)
{
    for(int i = 0; i < size; i++)
        for(int j = i+1; j < size; j++)
            if(nums[i] == nums[j])
                return true;
    return false;
}

void swap(int* p, int* q)
{
    int t = *p; *p = *q; *q = t;
}

void swiftSort(int* a, int low, int high)
{
    int l = low, h = high;
    int v = a[l+(h-l)/2];
    while(l <= h)
    {
        while(a[l] < v) l++;
        while(a[h] > v) h--;
        if(l <= h)
        {
            swap(a+l, a+h);
            l++, h--;
        }
    }
    if(h > low)
        swiftSort(a, low, h);
    if(l < high)
        swiftSort(a, l, high);
}

//AC - 12ms;
bool containsDuplicate1(int* nums, int size)
{
    swiftSort(nums, 0, size-1);
    for(int i = 1; i < size; i++)
        if(nums[i] == nums[i-1])
            return true;
    return false;
}


bool containsDuplicate2(vector<int>& nums)
{
    return nums.size() > set<int>(nums.begin(), nums.end());
}

