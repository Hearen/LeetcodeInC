/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-01-19 11:14
Description : 
Source      : https://leetcode.com/problems/number-of-1-bits/
*******************************************/
#include <types.h>
//AC - 4ms;
int hammingWeight0(uint32_t n)
{
    int count = 0;
    while(n)
    {
        if(n & 1)
            count++;
        n >>= 1;
    }
    return count;
}

//AC - 4ms - only counting the 1s;
int hammingWeight(uint32_t n)
{
    int count = 0;
    for(; n; c++) n &= n-1; //count the right-most bit-1;
    return count;
}
