/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-02-27 22:19
Description : Follow up for "Find Minimum in Rotated Sorted Array":
What if duplicates are allowed?
Would this affect the run-time complexity? How and why?
Suppose a sorted array is rotated at some pivot unknown to you beforehand.
(i.e., 0 1 2 4 5 6 7 might become 4 5 6 7 0 1 2).
Find the minimum element.
The array may contain duplicates.
Source      : https://leetcode.com/problems/find-minimum-in-rotated-sorted-array-ii/
*******************************************/
//AC - 4ms;
int findMin0(int* nums, int size) //linear solution;
{
    int c=0, n=0, nn=0;
    while(c < size)
    {
        n = c + 1;
        nn = n + 1;
        if(n<size && nums[n]<nums[c])
            return nums[n];
        if(nn<size && nums[nn]<nums[n])
            return nums[nn];
        c = nn;
    }
    return nums[0];
}

int findMin1(int* nums, int size)
{
    if(size == 1) return nums[0];
    int l=0, r=size-1, m=0;
    while(nums[l] >= nums[r]) //ensure the landscape to be reversed;
    {
        m = (l+r)>>1;
        if(r-l == 1) break;
        if(nums[m] > nums[l]) l = m;
        else if(nums[m] < nums[l]) r = m;
        else l++; //quite essential;
    }
    return nums[l]>nums[r]? nums[r]:nums[l];
}

int findMin(int* nums, int size)
{
    int l=0, r=size-1, m=0;
    while(l < r)
    {
        m = l+(r-l)/2;
        if(nums[m] > nums[r]) l = m+1;
        else if(nums[m] < nums[r]) r = m; //keep the middle element;
        else r--; 
    }
    return nums[l];
}
