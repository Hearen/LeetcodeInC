/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-02-12 15:02
Description : Find the contiguous subarray within an array (containing at least one number) which has the largest product.
For example, given the array [2,3,-2,4],
the contiguous subarray [2,3] has the largest product = 6.
Source      : https://leetcode.com/problems/maximum-product-subarray/
*******************************************/
//AC - 4ms;
#define MAX(a, b) (a)>(b)? (a):(b)
#define MIN(a, b) (a)<(b)? (a):(b)
int maxProduct(int* nums, int size)
{
    int max = nums[0];
    for(int i=1, imax=max, imin=max; i < size; i++)
    {
        int t;
        if(nums[i] < 0) //min and max should be recorded since min can be max when negated again;
            t = imax, imax = imin, imin = t;
        t = imax*nums[i];
        imax = MAX(nums[i], t); //make sure the continuity;
        t = imin*nums[i];
        imin = MIN(nums[i], t);
        max = MAX(imax, max);
    }
    return max;
}
