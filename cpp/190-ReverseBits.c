/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-01-21 08:37
Description : Reverse bits of a given 32 bits unsigned integer.
For example, given input 43261596 (represented in binary as 00000010100101000001111010011100), return 964176192 (represented in binary as 00111001011110000010100101000000).
Source      : https://leetcode.com/problems/reverse-bits/
*******************************************/
#include <stdint.h>
//AC - 4ms;
uint32_t reverseBits(uint32_t n)
{
    uint32_t mask=1<<31, a=0;
    for(int i = 0; i < 32; i++)
    {
        if(n & 1) a |= mask;
        n >>= 1;
        mask >>= 1;
    }
    return a;
}
