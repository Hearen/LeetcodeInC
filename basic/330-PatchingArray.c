/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-02-22 20:00
Description : Given a sorted positive integer array nums and an integer n, add/patch elements to the array such that any number in range [1, n] inclusive can be formed by the sum of some elements in the array. Return the minimum number of patches required.
Example 1:
nums = [1, 3], n = 6
Return 1.
Combinations of nums are [1], [3], [1,3], which form possible sums of: 1, 3, 4.
Now if we add/patch 2 to nums, the combinations are: [1], [2], [3], [1,3], [2,3], [1,2,3].
Possible sums are 1, 2, 3, 4, 5, 6, which now covers the range [1, 6].
So we only need 1 patch.
Example 2:
nums = [1, 5, 10], n = 20
Return 2.
The two patches can be [2, 4].
Example 3:
nums = [1, 2, 2], n = 5
Return 0.
Source      : https://leetcode.com/problems/patching-array/
*******************************************/
//AC - 4ms;
int minPatches(int* nums, int size, int n)
{
    int count=0, index=0;
    long long top = 0;
    while(top < n)
    {
        if(index<size && nums[index]<=(top+1)) //use elements in nums to reach as big as possible;
            top += nums[index++];
        else
        {
            count++;
            top = 2*top+1; //add as much as possible - add top+1 here to reach 2*top+1;
        }
    }
    return count;
}
