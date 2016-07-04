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
class Solution 
{
public:
    //AC - 16ms - forward searching the max index reachable;
    bool canJump(vector<int>& nums) 
    {
        int maxEnd = 0;
        for(int i = 0; i<nums.size() && i<=maxEnd; ++i)
            maxEnd = max(maxEnd, i+nums[i]);
        return maxEnd >= nums.size()-1;
    }

    //AC - 16ms - forward searching for the jump length;
    bool canJump(vector<int>& nums) 
    {
        for(int i = 0, des = 0; i < nums.size()-1; ++i, des--)
        {
            des = max(des, nums[i]);
            if(des<1 && i!=nums.size()-1) return false;
        }
        return true;
    }

    //AC - 16ms - backwards searching for the valid start index;
    bool canJump(vector<int>& nums) 
    {
        int validStart = nums.size()-1;
        for(int i = validStart-1; i >= 0; --i)
            if(i+nums[i] >= validStart) validStart = i;
        return validStart == 0;
    }

    //AC - 16ms - backwards searching for zero jump length and then make sure it can be jumped over;
    bool canJump(vector<int>& nums) 
    {
        int d = 0;
        for(int i = nums.size()-2; i >= 0; --i)
        {
            if(nums[i] == 0)
            {
                int d = 1;
                while(d > nums[i])
                {
                    d++;
                    i--;
                    if(i < 0) return false;
                }
            }
        }
        return true;
    }
};

