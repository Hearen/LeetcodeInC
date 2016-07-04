/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : Thu, 30 Jun 2016 07:56 CST
Description : Find the contiguous subarray within an array (containing at least one number) which has the largest product.
For example, given the array [2,3,-2,4],
the contiguous subarray [2,3] has the largest product = 6.
Source      : https://leetcode.com/problems/maximum-product-subarray/
*******************************************/
class Solution {
public:
    //min can turn max when encountering another negative number
    //so we have to record all the min and max values;
	int maxProduct(vector<int>& nums) 
    {
        int size = nums.size(), maxProduct = nums[0];
        int maxProducts[size]{0}, minProducts[size]{0};
        maxProducts[0] = minProducts[0] = nums[0];
        for(int i = 1; i < size; ++i)
        {
            maxProducts[i] = max(maxProducts[i-1]*nums[i], max(minProducts[i-1]*nums[i], nums[i]));
            minProducts[i] = min(maxProducts[i-1]*nums[i], min(minProducts[i-1]*nums[i], nums[i]));
            maxProduct = max(maxProduct, maxProducts[i]);
        }
        return maxProduct;
    }

    //actually we only need two variables to record the
    //previous min and max products;
	int maxProduct(vector<int>& nums) 
    {
        int size = nums.size();
        int minProduct = nums[0], maxProduct = nums[0], ret = nums[0];
        for(int i = 1; i < size; ++i)
        {
            if(nums[i] < 0) swap(minProduct, maxProduct);
            maxProduct = max(maxProduct*nums[i], nums[i]);
            minProduct = min(minProduct*nums[i], nums[i]);
            ret = max(ret, maxProduct);
        }
        return ret;
    }

    //another solution using constant space too;
    //traversing from left to right and meantime from right to left
    //to calculate the possible max products since the subsequence will be 
    //from left to right or right to left anyway but in two directions 
    //in case of neglecting the other half [3, -1, 4];
    int maxProduct(vector<int>& nums) 
    {
        int lProduct = 1, rProduct = 1;
        int size = nums.size(), maxProduct = nums[0];
        for(int i = 0; i < size; ++i)
        {
            lProduct *= nums[i];
            rProduct *= nums[size-i-1];
            maxProduct = max(maxProduct, max(lProduct, rProduct));
            if(lProduct == 0) lProduct = 1;
            if(rProduct == 0) rProduct = 1;
        }
        return maxProduct;
    }
};
