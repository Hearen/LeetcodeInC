/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-02-12 14:49
Description : Find the contiguous subarray within an array (containing at least one number) which has the largest sum.
For example, given the array [−2,1,−3,4,−1,2,1,−5,4],
the contiguous subarray [4,−1,2,1] has the largest sum = 6.
Source      : https://leetcode.com/problems/maximum-subarray/
*******************************************/
#include <limits.h>
//AC - 4ms;
int maxSubArray(int* nums, int size)
{
    int sum = 0;
    int max = INT_MIN;
    for(int i = 0; i < size; i++)
    {
        if(sum >= 0)
            sum += nums[i];
        else
            sum = nums[i];
        if(sum > max)
            max = sum;
    }
    return max;
}
