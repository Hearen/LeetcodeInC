/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-02-12 15:02
Description : Find the contiguous subarray within an array (containing at least one number) which has the largest product.
For example, given the array [2,3,-2,4],
the contiguous subarray [2,3] has the largest product = 6.
Source      : https://leetcode.com/problems/maximum-product-subarray/
*******************************************/
#include <limits.h>
//AC - 4ms;
#define MAX(a, b) (a)>(b)? (a):(b)
#define MIN(a, b) (a)<(b)? (a):(b)
int maxProduct0(int* nums, int size)
{
    if(!size) return 0;
    int *maxProducts = (int*)malloc(sizeof(int)*size);
    int *minProducts = (int*)malloc(sizeof(int)*size);
    int max = maxProducts[0] = minProducts[0] = nums[0];
    for(int i = 1; i < size; i++)
    {
        maxProducts[i] = MAX(MAX(maxProducts[i-1]*nums[i], minProducts[i-1]*nums[i]), nums[i]);
        minProducts[i] = MIN(MIN(maxProducts[i-1]*nums[i], minProducts[i-1]*nums[i]), nums[i]);
        max = MAX(max, maxProducts[i]);
    }
    return max;
}
int maxProduct1(int* nums, int size)
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

int maxProduct(int* nums, int size)
{
    int lProduct=1, rProduct=1;
    int max = INT_MIN;
    for(int i = 0; i < size; i++)
    {
        lProduct *= nums[i];
        rProduct *= nums[size-i-1];
        max = MAX(max, MAX(lProduct, rProduct));
        lProduct = !lProduct? 1:lProduct;
        rProduct = !rProduct? 1:rProduct;
    }
    return max;
}
