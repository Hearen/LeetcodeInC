/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : Wed, 15 Jun 2016 21:43 CST
Description : Given a positive integer n, break it into the sum of at least two positive integers and maximize the product of those integers. Return the maximum product you can get.
For example, given n = 2, return 1 (2 = 1 + 1); given n = 10, return 36 (10 = 3 + 3 + 4).
Note: you may assume that n is not less than 2.
Source      : https://leetcode.com/problems/integer-break/
*******************************************/
class Solution 
{
public:
    //AC - 0ms - (n/2)^2 >= n/2 * 2 - mathematical problem;
    //2, 3 should be the unit since 3 is better (6 = 3+3 = 2+2+2)
    //so we should get as many 3 as possible;
    int integerBreak(int n) 
    {
        if(n == 2) return 1;
        if(n == 3) return 2;
        switch(n%3)
        {
            case 0: return pow(3, n/3);
            case 1: return pow(3, n/3 - 1)*4;
            case 2: return pow(3, n/3)*2;
        }
        return 0;
    }
};
