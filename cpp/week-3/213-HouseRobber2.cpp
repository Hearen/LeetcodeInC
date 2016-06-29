/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : Wed, 29 Jun 2016 18:48 CST
Description : You are a professional robber planning to rob houses along a street. Each house has a certain amount of money stashed, the only constraint stopping you from robbing each of them is that adjacent houses have security system connected and it will automatically contact the police if two adjacent houses were broken into on the same night.
Given a list of non-negative integers representing the amount of money of each house, determine the maximum amount of money you can rob tonight without alerting the police.

After robbing those houses on that street, the thief has found himself a new place for his thievery so that he will not get too much attention. This time, all houses at this place are arranged in a circle. That means the first house is the neighbor of the last one. Meanwhile, the security system for these houses remain the same as for those in the previous street.
Given a list of non-negative integers representing the amount of money of each house, determine the maximum amount of money you can rob tonight without alerting the police.
Source      : https://leetcode.com/problems/house-robber-ii/
*******************************************/
class Solution {
private:
    int rob1(vector<int>& nums, int begin, int end) 
    {
        int size = end-begin+1;
        if(size == 1) return nums[begin];
        int robbed[size]{0};
        robbed[0] = nums[begin];
        robbed[1] = nums[begin+1];
        int maxRob = max(robbed[0], robbed[1]);
        for(int i = 2; i < size; ++i) //robbed[i] is the maximum ends with house[i] (house[i] is robbed too);
        {
            robbed[i] = robbed[i-1];
            for(int j = i-2; j >= 0; --j)
                robbed[i] = max(robbed[i], robbed[j]+nums[i+begin]);
            maxRob = max(maxRob, robbed[i]);
        }
        return maxRob;
    }
public:
    int rob(vector<int>& nums) 
    {
        int size = nums.size();
        if(!size) return 0;
        if(size == 1) return nums[0];
        return max(rob1(nums, 0, size-2), rob1(nums, 1, size-1));
    }

    int rob(vector<int>& nums) 
    {
        int size = nums.size();
        if(size == 0) return 0;
        if(size == 1) return nums[0];
        if(size == 2) return max(nums[0], nums[1]);
        int pre = nums[0], cur = max(nums[0], nums[1]);
        int t = 0, withFirst = 0;    
        for(int i = 2; i < size-1; ++i)
        {
            t = pre;
            cur = max(pre=cur, t+nums[i]); //cur is the maximum till house[i] (house[i] is robbed or not, god knows, we just care about the maximum);
        }
        withFirst = cur;
        pre = nums[1], cur = max(nums[1], nums[2]);
        for(int i = 3; i < size; ++i)
        {
            t = pre;
            cur = max(pre=cur, t+nums[i]);
        }
        return max(withFirst, cur);
    }
};
