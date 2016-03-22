/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-03-22 21:20
Description : 
w up for "Remove Duplicates":
What if duplicates are allowed at most twice?
For example,
Given sorted array nums = [1,1,1,2,2,3],

Your function should return length = 5, with the first five elements of nums being 1, 1, 2, 2 and 3. It doesn't matter what you leave beyond the new length.
Source      : https://leetcode.com/problems/remove-duplicates-from-sorted-array-ii/
*******************************************/
int removeDuplicates (int *nums, int numsSize)
{
    int currentValue = nums[numsSize - 1] + 1;
    int count = 0;
    int sumCount = 0;
    int *a = (int*)malloc(sizeof(int)*numsSize);
    for (int i = 0; i < numsSize; i++)
    a[i] = nums[i];
    for (int i = 0; i < numsSize; i++)
    {
        if (currentValue != a[i])
            count = 1, currentValue = a[i];
        else if (currentValue == a[i])
            count++;
        if (count < 3)
            nums[sumCount++] = a[i];

    }
    return sumCount;
}
