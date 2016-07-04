/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : Thu, 30 Jun 2016 07:51 CST
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
class Solution {
public:
    //searching for the best splitting index (the last bursting balloon, 
    //since it's the last to burst then the left and right balloons are 
    //separated and affect each other no more);
    int maxCoins(vector<int>& nums) 
    {
        nums.insert(nums.begin(), 1);
        nums.insert(nums.end(), 1);
        int size = nums.size();
        int dp[size][size]; //the maximal coins from index i to j inclusively;
        memset(dp, 0, sizeof(int)*size*size);
        for(int d = 2; d < size; ++d)
        {
            for(int l = 0; l+d <size; ++l)
            {
                int r = l+d;
                for(int j = l+1; j < r; ++j) //balloon j is the last to burst;
                    dp[l][r] = max(dp[l][r], dp[l][j]+dp[j][r]+nums[l]*nums[j]*nums[r]);
            }
        }
        return dp[0][size-1];
    }
};
