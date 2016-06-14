/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-03-01 16:20
Description : Given an integer n, count the total number of digit 1 appearing in all non-negative integers less than or equal to n.
For example:
Given n = 13,
Return 6, because digit 1 occurred in the following numbers: 1, 10, 11, 12, 13.
Source      : https://leetcode.com/problems/number-of-digit-one/
*******************************************/
class Solution 
{
public:
    int countDigitOne(int num) 
    {
        int sum = 0;
        for(long i = 1; i <= num; i *= 10)
        {
            int a = num/i;
            int b = num%i;
            sum += (a+8)/10*i+(a%10==1)*(b+1);
        }
        return sum;
    }
};
