/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-01-20 08:21
Description : Given a sorted array, remove the duplicates in place such that each element appear only once and return the new length.
Do not allocate extra space for another array, you must do this in place with constant memory.
For example,
Given input array nums = [1,1,2],
Your function should return length = 2, with the first two elements of nums being 1 and 2 respectively. It doesn't matter what you leave beyond the new length.
Source      : https://leetcode.com/problems/remove-duplicates-from-sorted-array/
*******************************************/

//AC - 12ms;
int removeDuplicates1(int* nums, int size)
{
    if(size == 0)
        return 0;
    int pre = 0;
    for(int cur = 1; cur < size; cur++)
        if(nums[cur] != nums[pre])
            nums[++pre] = nums[cur];
    return pre+1;
}
