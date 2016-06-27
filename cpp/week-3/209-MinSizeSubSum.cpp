/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2015-12-25 15:40
Description : Given an array of n positive integers and a positive integer s, find the minimal length of a subarray of which the sum ≥ s. If there isn't one, return 0 instead.
For example, given the array [2,3,1,2,4,3] and s = 7,
the subarray [4,3] has the minimal length under the problem constraint.
Source      : https://leetcode.com/problems/minimum-size-subarray-sum/
*******************************************/
class Solution {
public:
    //using two pointers;
    int minSubArrayLen(int s, vector<int>& nums) 
    {
        int size = nums.size(), l = 0, r = 0, sum = 0;
        while(r<size && sum<s) sum += nums[r++];
        if(sum < s) return 0;
        int minLen = r-l;
        while(r <= size)
        {
            if(r < size) sum += nums[r++];
            while(l<size && sum>s) sum -= nums[l++];
            if(sum < s) sum += nums[--l];
            minLen = min(minLen, r-l);
            if(r == size) break;
        }
        return minLen;
    }
};
