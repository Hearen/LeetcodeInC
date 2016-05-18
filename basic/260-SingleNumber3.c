/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-02-12 08:10
Description : Given an array of numbers nums, in which exactly two elements appear only once and all the other elements appear exactly twice. Find the two elements that appear only once.
For example:
Given nums = [1, 2, 1, 3, 2, 5], return [3, 5].
Note:
The order of the result is not important. So in the above example, [5, 3] is also correct.
Your algorithm should run in linear runtime complexity. Could you implement it using only constant space complexity?
Source      : https://leetcode.com/problems/single-number-iii/
*******************************************/
//AC - 4ms;
int* singleNumber(int* nums, int size, int* returnSize)
{
    *returnSize = 2;
    int *arr = (int*)malloc(sizeof(int)*2);
    memset(arr, 0, sizeof(int)*2);
    int ret = 0;
    for(int i = 0; i < size; i++) //get the xor-ed result of the two distincts;
        ret ^= nums[i];
    int splitter = ret & -ret; //find the first 'true' bit;
    for(int i = 0; i < size; i++)
    {
        if(splitter & nums[i])
            arr[0] ^= nums[i];
        else
            arr[1] ^= nums[i];
    }
    return arr;
}
