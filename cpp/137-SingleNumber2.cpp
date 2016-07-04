/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : Thu, 23 Jun 2016 14:59 CST
Description : Given an array of integers, every element appears three times except for one. Find that single one.
Note:
Your algorithm should have a linear runtime complexity. Could you implement it without using extra memory?
Source      : https://leetcode.com/problems/single-number-ii/
*******************************************/
class Solution {
public:
    //inspired by logical circuit design and boolean algebra;
    //counter - unit of 3;
    //current   incoming  next
    //a b            c    a b
    //0 0            0    0 0
    //0 1            0    0 1
    //1 0            0    1 0
    //0 0            1    0 1
    //0 1            1    1 0
    //1 0            1    0 0
    //a = a&~b&~c | ~a&b&c;
    //b = ~a&b&~c | ~a&~b&c;
    //return a|b since the single number can appear once or twice;
    int singleNumber(vector<int>& nums) 
    {
        int t = 0, a = 0, b = 0;
        for(int i = 0; i < nums.size(); ++i)
        {
            t = (a&~b&~nums[i]) | (~a&b&nums[i]);
            b = (~a&b&~nums[i]) | (~a&~b&nums[i]);
            a = t;
        }
        return a | b;
    }

    //direct method - calculate each bit and find the single one;
    int singleNumber(vector<int>& nums) 
    {
        int mask = 1, ret = 0, count = 0;
        int size = sizeof(int)*8;
        for(int i = 0; i < size; ++i)
        {
            count = 0;
            for(int j = 0; j < nums.size(); ++j)
                if(mask & nums[j]) count++;
            if(count % 3) ret |= mask;
            mask <<= 1;
        }
        return ret;
    }
};
