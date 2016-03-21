/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-01-20 08:08
Description : Given an array and a value, remove all instances of that value in place and return the new length.
Do not allocate extra space for another array, you must do this in place with constant memory.
The order of elements can be changed. It doesn't matter what you leave beyond the new length.
Example:
Given input array nums = [3,2,2,3], val = 3
Your function should return length = 2, with the first two elements of nums being 2.
Source      : https://leetcode.com/problems/remove-element/
*******************************************/
//AC - 0ms;
int removeElement0(int* nums, int size, int val)
{
    int l = 0, r = size-1;
    while(l <= r)
    {
        while(l <= r && nums[l] != val) l++;
        while(nums[r] == val) r--;
        if(l < r)
        {
            int t = nums[l];
            nums[l] = nums[r];
            nums[r] = t;
            r--;
        }
    }
    return l;
}

//AC - 0ms;
int removeElement(int* nums, int size, int val)
{
    int index = 0;
    for(int i = 0; i < size; i++)
        if(nums[i] != val)
            nums[index++] = nums[i];
    return index;
}
