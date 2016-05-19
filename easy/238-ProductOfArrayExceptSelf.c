/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-02-26 15:34
Description : Given an array of n integers where n > 1, nums, return an array output such that output[i] is equal to the product of all the elements of nums except nums[i].
Solve it without division and in O(n).
For example, given [1,2,3,4], return [24,12,8,6].
Follow up:
Could you solve it with constant space complexity? (Note: The output array does not count as extra space for the purpose of space complexity analysis.)
Source      : https://leetcode.com/problems/product-of-array-except-self/
*******************************************/
//AC - 36ms;
int* productExceptSelf(int* nums, int size, int* returnSize)
{
    int* arr = (int*)malloc(sizeof(int)*size); //the result array;
    arr[0] = 1;
    for(int i = 1; i < size; i++) //collect the product of left side;
        arr[i] = arr[i-1] * nums[i-1];
    int t = nums[size-1]; //using t to collect the right side;
    for(int i = size-2; i > -1; i--) //merge t and arr, we get the product except self;
    {
        arr[i] *= t;
        t *= nums[i];
    }
    *returnSize = size;
    return arr;
}
