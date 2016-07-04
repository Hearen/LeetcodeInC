/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : Thu, 30 Jun 2016 11:06 CST
Description : Given an array of n integers where n > 1, nums, return an array output such that output[i] is equal to the product of all the elements of nums except nums[i].
Solve it without division and in O(n).
For example, given [1,2,3,4], return [24,12,8,6].
Follow up:
Could you solve it with constant space complexity? (Note: The output array does not count as extra space for the purpose of space complexity analysis.)
Source      : https://leetcode.com/problems/product-of-array-except-self/
*******************************************/
class Solution {
public:
    //normal method using linear space;
    vector<int> productExceptSelf(vector<int>& nums) 
    {
        if(nums.empty()) return vector<int>();
        int size = nums.size();
        int lProducts[size], rProducts[size];
        lProducts[0] = 1, rProducts[size-1] = 1;
        for(int i = 1; i < size; ++i)
        {
            lProducts[i] = nums[i-1]*lProducts[i-1];
            rProducts[size-i-1] = nums[size-i]*rProducts[size-i];
        }
        vector<int> v(size);
        for(int i = 0; i < size; ++i)  
            v[i] = lProducts[i]*rProducts[i];
        return v;
    }
	
    //actually we can do it with constant extra space;
	vector<int> productExceptSelf(vector<int>& nums) 
    {
        if(nums.empty()) return vector<int>();
        int size = nums.size(), t = 1;
        vector<int> v(size);
        v[0] = 1;
        for(int i = 1; i < size; ++i) v[i] = v[i-1]*nums[i-1];
        for(int i = size-2; i >= 0; --i)
            v[i] *= (t *= nums[i+1]);
        return v;
    }
};
