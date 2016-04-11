/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-03-04 14:00
Description : Given a range [m, n] where 0 <= m <= n <= 2147483647, return the bitwise AND of all numbers in this range, inclusive.
For example, given the range [5, 7], you should return 4.
Source      : https://leetcode.com/problems/bitwise-and-of-numbers-range/
*******************************************/
#include <limits.h>
int rangeBitwiseAnd0(int m, int n)
{
    int count = 0;
    while(m != n) //until the left identical bits, all the right will be cancelled by increments from m to n;;
    {
        m >>= 1;
        n >>= 1;
        count++;
    }
    return m << count;
}

//AC - get the left common part;
int rangeBitwiseAnd1(int m, int n)
{
    int r = INT_MAX;
    while((m&r) != (n&r)) r <<= 1;
    return n&r;
}

int rangeBitwiseAnd(int m, int n)
{
    while(m < n) n &= n-1; //remove the right bit-1 until equal to or less than m;
    return n;
}
