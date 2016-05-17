/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-01-12 08:48
Description : Given an array nums, write a function to move all 0's to the end of it while maintaining the relative order of the non-zero elements.
For example, given nums = [0, 1, 0, 3, 12], after calling your function, nums should be [1, 3, 12, 0, 0].
Note:
You must do this in-place without making a copy of the array.
Minimize the total number of operations.
Source      : https://leetcode.com/problems/move-zeroes/
*******************************************/
//AC - 8ms - there are extra space in the front always;
void moveZeroes(int* nums, int size)
{
    int index = 0;
    for(int i = 0; i < size; i++)
        if(nums[i] != 0)
            nums[index++] = nums[i];
    while(index < size)
        nums[index++] = 0;
}
