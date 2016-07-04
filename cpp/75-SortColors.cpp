/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : Mon, 27 Jun 2016 20:48 CST
Description : Given an array with n objects colored red, white or blue, sort them so that objects of the same color are adjacent, with the colors in the order red, white and blue.
Here, we will use the integers 0, 1, and 2 to represent the color red, white, and blue respectively.
Note:
You are not suppose to use the library's sort function for this problem.
Source      : https://leetcode.com/problems/sort-colors/
*******************************************/
class Solution {
public:
    //two passes;
	void sortColors(vector<int>& nums) 
    {
        int count0 = 0, count1 = 0, count2 = 0;
        for(int i = 0; i < nums.size(); ++i)
        {
            switch(nums[i])
            {
                case 0: count0++; break;
                case 1: count1++; break;
                case 2: count2++; break;
            }
        }
        fill(nums.begin(), nums.end(), 0);
        for(int i = 0; i < nums.size(); ++i)
        {
            if(i >= count0) nums[i]++;
            if(i >= count0+count1) nums[i]++;
        }
    }

    //one pass;
    void sortColors(vector<int>& nums) 
    {
        int j = 0, k = nums.size()-1;
        for(int i = 0; i <= k; ++i)
        {
            if(nums[i]==0 && i!=j)
                swap(nums[i--], nums[j++]);
            else if(nums[i]==2 && i!=k)
                swap(nums[i--], nums[k--]);
        }
    }
    

    //one pass;
	void sortColors(vector<int>& nums) 
    {
        int i0 = 0, i1 = 0, i2 = 0;
        for(int i = 0; i < nums.size(); ++i)
        {
            if(nums[i] == 0) nums[i2++] = 2, nums[i1++] = 1, nums[i0++] = 0;
            else if(nums[i] == 1) nums[i2++] = 2, nums[i1++] = 1;
            else nums[i2++] = 2;
        }
    }
};
