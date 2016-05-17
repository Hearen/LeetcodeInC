/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-02-27 21:35
Description : Given an array containing n distinct numbers taken from 0, 1, 2, ..., n, find the one that is missing from the array.
For example,
Given nums = [0, 1, 3] return 2.
Note:
Your algorithm should run in linear runtime complexity. Could you implement it using only constant extra space complexity?
Source      : https://leetcode.com/problems/missing-number/
*******************************************/
#include <bool.h>
//AC - 12ms - using O(n) space;
int missingNumber0(int* nums, int size)
{
    bool *arr = (int*)malloc(sizeof(bool)*(size+1));
    memset(arr, 0, sizeof(bool)*(size+1));
    for(int i = 0; i < size; i++)
        arr[nums[i]] = true;
    for(int i = 0; i <= size; i++)
        if(!arr[i])
            return i;
}

//AC - 16ms;
int missingNumber1(int* nums, int size)
{
    int sum = (size*(size+1))/2;
    int t = 0;
    for(int i = 0; i < size; i++) t += nums[i];
    return sum-t;
}

//AC - 12ms;
//a^a=0 and 0^b=b;
int missingNumber(int* nums, int size)
{
    int t = size;
    for(int i = 0; i < size; i++)
        t ^= nums[i]^i;
    return t;
}

