/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-02-13 16:21
Description : After robbing those houses on that street, the thief has found himself a new place for his thievery so that he will not get too much attention. This time, all houses at this place are arranged in a circle. That means the first house is the neighbor of the last one. Meanwhile, the security system for these houses remain the same as for those in the previous street.
Given a list of non-negative integers representing the amount of money of each house, determine the maximum amount of money you can rob tonight without alerting the police.
Source      : https://leetcode.com/problems/house-robber-ii/
*******************************************/
int rob0(int* nums, int size)
{
    if(size == 0)
        return 0;
    if(size == 1)
        return nums[0];
    int *profits = (int*)malloc(sizeof(int)*size);
    profits[0] = nums[0];
    profits[1] = nums[1] > nums[0] ? nums[1] : nums[0];
    for(int i = 2; i < size; i++)
    {
        int profit = profits[i-2] + nums[i];
        if(profits[i-1] > profit)
            profit = profits[i-1];
        profits[i] = profit;
    }
    return profits[size-1];
}

//AC - 0ms;
int rob1(int* nums, int size)
{
    if(size == 0)
        return 0;
    if(size == 1)
        return nums[0];
    int profit0 = rob0(nums, size-1);
    int profit1 = rob0(nums+1, size-1);
    return profit0 > profit1? profit0 : profit1;
}

//AC - 0ms - using constant space;
int rob2(int* nums, int size)
{
    if(size == 0) return 0;
    if(size == 1) return nums[0];
    int pre0=0, cur0=0;
    for(int i = 0; i < size-1; i++) //including the first;
    {
        int t = pre0; //t will be profits[i-2] here;
        pre0 = cur0;
        if(t+nums[i] > cur0) cur0 = t+nums[i];
    }

    int pre1=0, cur1=0;
    for(int i = 1; i < size; i++) //excluding the first and including the last;
    {
        int t = pre1; //t will be profits[i-2] here;
        pre1 = cur1;
        if(t+nums[i] > cur1) cur1 = t+nums[i];
    }
    return cur0>cur1? cur0:cur1;
}

//AC - 0ms - actually there are only four different states we need to record;
int rob(int* nums, int size)
{
    if(size == 1) return nums[0];
    int inFirst=nums[0], exFirst=0; //including the first element, but include or exclude the current;
    int inNoFirst=0, exNoFirst=0;//excluding the first, but include or exclude the current;
    for(int i = 1; i < size; i++)
    {
        int preInFirst = inFirst; //handling the first included case;
        inFirst = exFirst+nums[i];
        exFirst = preInFirst > exFirst? preInFirst:exFirst;
        int preInNoFirst = inNoFirst; //handle the first excluded case;
        inNoFirst = exNoFirst+nums[i];
        exNoFirst = preInNoFirst > exNoFirst? preInNoFirst:exNoFirst;
    }
    return inNoFirst > exFirst? inNoFirst:exFirst;
}
