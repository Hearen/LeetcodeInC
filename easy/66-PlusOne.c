/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-01-20 09:30
Description : Given a non-negative number represented as an array of digits, plus one to the number.
The digits are stored such that the most significant digit is at the head of the list.
Source      : https://leetcode.com/problems/plus-one/
*******************************************/
//AC - 0ms;
int* plusOne(int* digits, int size, int* returnSize)
{
    int unit = 10;
    digits[size-1] += 1;
    int c = 0;
    for(int i = size-1; i > 0; i--)
    {
        if(digits[i] >= unit)
        {
            digits[i-1]++;
            digits[i] = 0;
        }
    }
    if(digits[0] >= unit)
    {
        digits[0] = 0;
        *returnSize = size+1;
        int *a = (int*)malloc(sizeof(int)*(*returnSize));
        a[0] = 1;
        for(int i = 0; i < size; i++)
            a[i+1] = digits[i];
        return a;
    }
    else
        *returnSize = size;
    return digits;
}
