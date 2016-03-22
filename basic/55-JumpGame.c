/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-02-20 20:56
Description : Given an array of non-negative integers, you are initially positioned at the first index of the array.
Each element in the array represents your maximum jump length at that position.
Determine if you are able to reach the last index.
For example:
A = [2,3,1,1,4], return true.

A = [3,2,1,0,4], return false.
Source      : https://leetcode.com/problems/jump-game/
*******************************************/
#include <stdbool.h>

//AC - 4ms;
bool canJump1(int* nums, int size)
{
    if(size < 2) return true;
    for(int cur=size-2; cur > -1; cur--)
    {
        if(nums[cur] == 0)
        {
            int len = 1;
            while(len > nums[cur])
            {
                len++;
                cur--;
                if(cur < 0) return false;
            }
        }
    }
    return true;
}

//AC - 4ms;
bool canJump(int* nums, int size)
{
    int max = 0;
    for(int i = 0; i < size; i++, max--)
    {
        max = max > nums[i]? max : nums[i];
        if(max<1 && i!=size-1) return false;
    }
    return true;
}
