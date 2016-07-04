/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : Thu, 30 Jun 2016 20:54 CST
Description : Given an unsorted integer array, find the first missing positive integer.
For example,
Given [1,2,0] return 3,
and [3,4,-1,1] return 2.

Your algorithm should run in O(n) time and uses constant space.
Source      : https://leetcode.com/problems/first-missing-positive/
*******************************************/
class Solution {
public:
	//a value of nums[i] should be placed in position nums[i]-1, 
    //using while instead of if in case of the latter are exchanged to 
    //the traversed positions;
    int firstMissingPositive(vector<int>& nums) 
    {
        int size = nums.size();
        for(int i = 0; i < size; ++i)
            while(nums[i]>0 && nums[i]<=size && nums[nums[i]-1]!=nums[i])
                swap(nums[nums[i]-1], nums[i]);
        for(int i = 0; i < size; ++i)
            if(nums[i] != i+1)
                return i+1;
        return size+1;
    }
};
