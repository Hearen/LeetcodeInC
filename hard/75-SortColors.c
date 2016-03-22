/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-01-04 08:01
Description : Given an array with n objects colored red, white or blue, sort them so that objects of the same color are adjacent, with the colors in the order red, white and blue.
Here, we will use the integers 0, 1, and 2 to represent the color red, white, and blue respectively.

Note:
You are not suppose to use the library's sort function for this problem.
Follow up:
A rather straight forward solution is a two-pass algorithm using counting sort.
First, iterate the array counting number of 0's, 1's, and 2's, then overwrite array with total number of 0's, then 1's and followed by 2's.

Could you come up with an one-pass algorithm using only constant space?
Source      : https://leetcode.com/problems/sort-colors/
*******************************************/
#define FOO
void swap(int* p, int* q)
{
    int t = *p; *p = *q; *q = t;
}

//AC - 0ms;
void sortColors(int* nums, int size)
{
    int p, l, r, q;
    p = l = 0, q = r = size-1;
    while(l <= r)
    {
        while(l < size && nums[l] == 0) l++;
        while(r > -1 && nums[r] == 2) r--;
        if(l < size && nums[l] == 1 && l <= q)
            swap(nums+(l++), nums+(p++)); 
        if(r > -1 && nums[r] == 1 && r >= p)
            swap(nums+(r--), nums+(q--));
        else if(l <= r && nums[r] == 0 && nums[l] == 2)
        {
            swap(nums+r, nums+l);
            r--, l++;
        }
    }
    nums[p] == 1? p : p--;
    nums[q] == 1? q : q++;
    while(l > -1 && p > -1)
        swap(nums+l--, nums+p--);
    while(r < size && q < size)
        swap(nums+r++, nums+q++);
}
