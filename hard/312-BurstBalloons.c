/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-02-17 21:14
Description : Given n balloons, indexed from 0 to n-1. Each balloon is painted with a number on it represented by array nums. You are asked to burst all the balloons. If the you burst balloon i you will get nums[left] * nums[i] * nums[right] coins. Here left and right are adjacent indices of i. After the burst, the left and right then becomes adjacent.
Find the maximum coins you can collect by bursting the balloons wisely.

Note: 
(1) You may imagine nums[-1] = nums[n] = 1. They are not real therefore you can not burst them.
(2) 0 ≤ n ≤ 500, 0 ≤ nums[i] ≤ 100

Example:
Given [3, 1, 5, 8]
Return 167
nums = [3,1,5,8] --> [3,5,8] -->   [3,8]   -->  [8]  --> []
coins =  3*1*5      +  3*5*8    +  1*3*8      + 1*8*1   = 167
Source      : https://leetcode.com/problems/burst-balloons/
*******************************************/
//AC - 12ms - bottom-up method to calculate the max using DP;
int maxCoins(int* nums, int size)
{
    int *nums1 = (int*)malloc(sizeof(int)*(size+2));
    nums1[0] = nums1[size+1] = 1;
    for(int i = 0; i < size; i++)
        nums1[i+1] = nums[i];
    size += 2;
    int** maxs = (int**)malloc(sizeof(int*)*size); //maxs store the max result between index i and j exclusively;
    for(int i = 0; i < size; i++)
    {
        maxs[i] = (int*)malloc(sizeof(int)*size);
        memset(maxs[i], 0, sizeof(int)*size);
    }
    for(int i = 2; i < size; i++) //the length from the leftmost to the rightmost in sub-ranges;
    {
        for(int left = 0; left+i < size; left++) //valid sub-ranges from leftmost to rightmost;
        {
            int right = left+i;
            for(int j = left+1; j < right; j++) //select the best splitting index in the sub-range;
            {
                int t = maxs[left][j]+maxs[j][right]+nums1[left]*nums1[right]*nums1[j];
                if(t > maxs[left][right])
                    maxs[left][right] = t;
            }
        }
    }
    return maxs[0][size-1]; //the max between the first and last - extra 1;
}
