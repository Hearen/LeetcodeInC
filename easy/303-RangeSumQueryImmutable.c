/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-02-12 09:18
Description : Given an integer array nums, find the sum of the elements between indices i and j (i ≤ j), inclusive.
Example:
Given nums = [-2, 0, 3, -5, 2, -1]
sumRange(0, 2) -> 1
sumRange(2, 5) -> -1
sumRange(0, 5) -> -3
Note:
You may assume that the array does not change.
There are many calls to sumRange function.
Source      : https://leetcode.com/problems/range-sum-query-immutable/
*******************************************/
struct NumArray
{
    int* sums;
};

struct NumArray* NumArrayCreate(int* nums, int size)
{
    struct NumArray *t = (struct NumArray*)malloc(sizeof(struct NumArray));
    int space = sizeof(int)*(size+1);
    t->sums = (int*)malloc(space);
    memset(t->sums, 0, sizeof(int));
    for(int i = 0; i < size; i++)
        t->sums[i+1] = t->sums[i] + nums[i];
    return t;
}

//AC - 568ms;
int sumRange(struct NumArray* numArray, int i, int j)
{
    int *sums = numArray->sums;
    return sums[j+1] - sums[i];
}

void NumArrayFree(struct NumArray* numArray)
{
    free(numArray->sums);
    free(numArray);
}
