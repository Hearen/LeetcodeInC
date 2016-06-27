/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : Mon, 27 Jun 2016 19:17 CST
Description : Given an array nums containing n + 1 integers where each integer is between 1 and n (inclusive), prove that at least one duplicate number must exist. Assume that there is only one duplicate number, find the duplicate one.

Note:
You must not modify the array (assume the array is read only).
You must use only constant, O(1) extra space.
Your runtime complexity should be less than O(n^2).
There is only one duplicate number in the array, but it could be repeated more than once.
Source      : https://leetcode.com/problems/find-the-duplicate-number/
*******************************************/
class Solution {
public:
    //Binary search - amazing;
	int findDuplicate(vector<int>& nums) 
	{
        int l = 1, h = nums.size()-1;
        while(l < h)
        {
            int count = 0;
            int m = (h+l)/2;
            for(int i = 0; i < nums.size(); ++i)
                if(nums[i]>=l && nums[i]<=m) count++;
            if(count <= m-l+1) l = m+1;
            else h = m;
        }
        return l;
    }

	//similar to find the start of the loop in a linked list;
	//the integer is the pointer while the index is the link;
    int findDuplicate(vector<int>& nums) {
        int slow = nums[0], fast = nums[nums[0]];
        while(slow != fast)
        {
            slow = nums[slow];
            fast = nums[nums[fast]];
        }
        fast = 0;
        while(fast != slow)//find the start of the loop which means at least two integer are the same value;
        {
            slow = nums[slow];
            fast = nums[fast];
        }
        return slow;
    }
};
