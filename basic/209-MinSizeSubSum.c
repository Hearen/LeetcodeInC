/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2015-12-25 15:40
Description : Given an array of n positive integers and a positive integer s, find the minimal length of a subarray of which the sum ≥ s. If there isn't one, return 0 instead.
For example, given the array [2,3,1,2,4,3] and s = 7,
the subarray [4,3] has the minimal length under the problem constraint.
Source      : https://leetcode.com/problems/minimum-size-subarray-sum/
*******************************************/
//AC - 0ms;
int minSubArrayLen(int s, int* nums, int size)
{
    int l=0, r=0; //l pointing to the first element of the subarray while the r pointing to the next element;
    int sum = 0;
    while(r < size) //initialize the l and r pointers;
    {
        sum += nums[r++];
        if(sum >= s) break;
    }
    if(sum < s) return 0; //there is no such sum that can be equal to or greater than s;
    int min = r-l;
    while(r <=size)
    {
        if(r < size) sum += nums[r++];
        while(sum-nums[l]>=s && l<r)  sum -= nums[l++];
        if(sum < s) sum += nums[--l]; //only when the current sum is less, add the last left-most element to ensure its validity;
        if(r-l < min) min = r-l;
        if(r == size) return min;
    }
}
