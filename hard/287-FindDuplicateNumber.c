/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2015-12-27 11:33
Description : Given an array nums containing n + 1 integers where each integer is between 1 and n (inclusive), prove that at least one duplicate number must exist. Assume that there is only one duplicate number, find the duplicate one.

Note:
You must not modify the array (assume the array is read only).
You must use only constant, O(1) extra space.
Your runtime complexity should be less than O(n^2).
There is only one duplicate number in the array, but it could be repeated more than once.
Source      : https://leetcode.com/problems/find-the-duplicate-number/
*******************************************/
//AC - 8ms - using linear space;
int findDuplicate0(int* nums, int size)
{
    int* arr = (int*)malloc(sizeof(int)*size);
    memset(arr, 0, sizeof(int)*size);
    for(int i = 0; i < size; i++)
    {
        arr[nums[i]]++;
        if(arr[nums[i]] > 1)
            return nums[i];
    }
    return 0;
}

//nlogn time cost constant space cost;
int findDuplicate(int* nums, int size)
{
    int l=1, h=size-1;
    while(l < h)
    {
        int m = (l+h)/2;
        int count = 0;
        for(int i = 0; i < size; i++)
            if(nums[i]>=l && nums[i]<=m) count++;
        if(count <= m-l+1) l = m+1;
        else h = m;
    }
    return l;
}

//AC - 4ms - using constant space and linear time;
//similar to find the start of the loop in a linked list;
//the integer is the pointer while the index is the link;
int findDuplicate1(int* nums, int size)
{
    if(size > 0)
    {
        int slow = nums[0];
        int fast = nums[nums[0]];
        while(slow != fast) //check the existence of the loop;
        {
            slow = nums[slow];
            fast = nums[nums[fast]];
        }
        fast = 0;
        while(slow != fast) //find the start of the loop which means at least two integer are the same value;
        {
            slow = nums[slow];
            fast = nums[fast];
        }
        return slow;
    }
    return -1;
}
