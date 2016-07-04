/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : Mon, 04 Jul 2016 15:52 CST
Description : Given a sorted array of integers, find the starting and ending position of a given target value.
Your algorithm's runtime complexity must be in the order of O(log n).
If the target is not found in the array, return [-1, -1].
For example,
Given [5, 7, 7, 8, 8, 10] and target value 8,
return [3, 4].
Source      : https://leetcode.com/problems/search-for-a-range/
*******************************************/
class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) 
    {
        int size = nums.size();
        vector<int> v{-1, -1};
        if(size == 0) return v;
        int l = 0, r = size-1, m = 0;
        while(l <= r)
        {
            m = (l+r)>>1;
            if(nums[m] >= target) { r = m-1; if(nums[m] == target) v[0] = m; }
            else l = m+1;
        }
        l = 0, r = size-1;
        while(l <= r)
        {
            m = (l+r)>>1;
            if(nums[m] <= target) { l = m+1; if(nums[m] == target) v[1] = m; }
            else r = m-1;
        }
        return v;
    }
};
