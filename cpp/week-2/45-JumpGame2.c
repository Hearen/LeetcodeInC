/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : Wed, 22 Jun 2016 15:55 CST
Description : Given an array of non-negative integers, you are initially positioned at the first index of the array.
Each element in the array represents your maximum jump length at that position.
Your goal is to reach the last index in the minimum number of jumps.
For example:
Given array A = [2,3,1,1,4]
The minimum number of jumps to reach the last index is 2. (Jump 1 step from index 0 to 1, then 3 steps to the last index.)
Note:
You can assume that you can always reach the last index.
Source      : https://leetcode.com/problems/jump-game-ii/
*******************************************/
class Solution {
public:
    //AC - 16ms - greedy method selecting the proper factor to be greedy for;
    int jump(vector<int>& nums) 
    {
        int i = 0, jumps = 0, size = nums.size();
        if(size == 1) return 0;
        while(i < size)
        {
            if(i+nums[i] > size-2) return ++jumps; //the last jump to or over the last;
            int next = 0, maxDes = 0;
            for(int j = i+1; j <= i+nums[i]; ++j) //searching for the most potential position;
            {
                if(nums[j]+j > maxDes) 
                    next = j, maxDes = nums[j]+j;
            }
            i = next; //jump to the most potential position;
            jumps++; //count the jump;
        }
        return 0; //for compilation matter, actually this statement will never be invoked;
    }
};
