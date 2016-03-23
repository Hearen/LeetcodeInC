/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-03-03 19:53
Description : The gray code is a binary numeral system where two successive values differ in only one bit.
Given a non-negative integer n representing the total number of bits in the code, print the sequence of gray code. A gray code sequence must begin with 0.
For example, given n = 2, return [0,1,3,2]. Its gray code sequence is:

00 - 0
01 - 1
11 - 3
10 - 2
Note:
For a given n, a gray code sequence is not uniquely defined.

For example, [0,2,3,1] is also a valid gray code sequence according to the above definition.

For now, the judge is able to judge based on one instance of gray code sequence. Sorry about that.
Source      : https://leetcode.com/problems/gray-code/
*******************************************/
//AC - 0ms;
//convert a unsigned binary number to reflected binary Gray Code (num >> 1) ^ num;
int grayCode(int n, int* returnSize)
{
    *returnSize = 0;
    int *arr = (int*)malloc(sizeof(int));
    n = 1<<n;
    for(int i = 0; i < n; i++)
    {
        *returnSize += 1;
        arr = (int*)realloc(arr, sizeof(int)*(*returnSize));
        arr[*returnSize-1] = i ^ (i>>1);
    }
    return arr;
}
