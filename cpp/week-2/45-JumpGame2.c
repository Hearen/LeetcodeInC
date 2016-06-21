/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-01-18 09:25
Description : 
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
