/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-01-22 16:47
Description : You are a professional robber planning to rob houses along a street. Each house has a certain amount of money stashed, the only constraint stopping you from robbing each of them is that adjacent houses have security system connected and it will automatically contact the police if two adjacent houses were broken into on the same night.
Given a list of non-negative integers representing the amount of money of each house, determine the maximum amount of money you can rob tonight without alerting the police.
Source      : https://leetcode.com/problems/house-robber/
*******************************************/
//AC - 0ms;
int rob(int* nums, int size)
{
    if(size == 0)
        return 0;
    if(size == 1)
        return nums[0];
    int *arr = (int*)malloc(sizeof(int)*size);
    arr[0] = nums[0];
    if(nums[1] > nums[0])
        arr[1] = nums[1];
    else
        arr[1] = nums[0];
    for(int i = 2; i < size; i++)
    {
        int count = arr[i-2]+nums[i];
        if(count < arr[i-1])
            count = arr[i-1];
        arr[i] = count;
    }
    return arr[size-1];
}
