/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2015-12-27 09:34
Description : Suppose a sorted array is rotated at some pivot unknown to you beforehand.
(i.e., 0 1 2 4 5 6 7 might become 4 5 6 7 0 1 2).
Find the minimum element.
You may assume no duplicate exists in the array.
Source      : https://leetcode.com/problems/find-minimum-in-rotated-sorted-array/
*******************************************/
#include <limits.h>
//AC - 0ms;
int findMin1(int* nums, int size)
{
    int low = 0, high = size-1;
    int mid;
    while(low <= high)
    {
        mid = (low+high) >> 1;
        if(nums[mid] > nums[high])
            low = mid+1;
        else
            high = mid;
    }
    return low;
}
