/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-01-20 09:40
Description : Given an integer n, return the number of trailing zeroes in n!.
Note: Your solution should be in logarithmic time complexity.
Source      : https://leetcode.com/problems/factorial-trailing-zeroes/
*******************************************/
//AC - 0ms - since 2 is ample, we only need to count 5 from 1 to n then - top-down method;
int trailingZeroes0(int n)
{
    int count = 0;
    while(n) count += (n/=5);
    return count;
}

//AC - 0ms - count from the small factor to bigger one to collect all 5s - bottom-up method;
int trailingZeroes(int n)
{
    int count = 0;
    for(long long i=5; n >= i; i *= 5) count += n/i;
    return count;
}
