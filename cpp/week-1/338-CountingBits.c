/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-03-21 16:53
Description : Given a non negative integer number num. For every numbers i in the range 0 ≤ i ≤ num calculate the number of 1's in their binary representation and return them as an array.
Example:
For num = 5 you should return [0,1,1,2,1,2].

Follow up:
It is very easy to come up with a solution with run time O(n*sizeof(integer)). But can you do it in linear time O(n) /possibly in a single pass?
Space complexity should be O(n).
Can you do it like a boss? Do it without using any builtin function like __builtin_popcount in c++ or in any other language.
Source      : https://leetcode.com/problems/counting-bits/
*******************************************/
//AC - 128ms;
int* countBits(int num, int *returnSize)
{
    num++;
    *returnSize = num;
    int* arr = (int*)malloc(sizeof(int)*num);
    memset(arr, 0, sizeof(int)*num);
    for(int i = 1; i < num; i++)
        arr[i] = (i&1)? arr[i>>1]+1 : arr[i>>1]; //just check its half;
    return arr;
}
