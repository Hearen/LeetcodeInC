/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-02-11 21:07
Description : Given an array of integers, every element appears three times except for one. Find that single one.
Note:
Your algorithm should have a linear runtime complexity. Could you implement it without using extra memory?
Source      : https://leetcode.com/problems/single-number-ii/
*******************************************/
//AC - 8ms;
//direct method - calculate each bit and find the single one;
int singleNumber0(int* nums, int size)
{
    int b, ret = 0;
    int len = sizeof(int)*8;
    for(int i = 0; i < len; i++)
    {
        b = 1 << i;
        int count = 0;
        for(int j = 0; j < size; j++)
            if(b & nums[j])
                count++;
        if(count%3)
            ret |= b;
    }
    return ret;
}
//AC - 4ms;
//inspired by logical circuit design and boolean algebra;
//counter - unit of 3;
//current   incoming  next
//a b            c    a b
//0 0            0    0 0
//0 1            0    0 1
//1 0            0    1 0
//0 0            1    0 1
//0 1            1    1 0
//1 0            1    0 0
//a = a&~b&~c + ~a&b&c;
//b = ~a&b&~c + ~a&~b&c;
//return a|b since the single number can appear once or twice;
int singleNumber(int* nums, int size)
{
    int a=0, b=0;
    for(int i = 0; i < size; i++)
    {
        int t = (~a&b&nums[i])|(a&~b&~nums[i]);
        b = (~a&~b&nums[i])|(~a&b&~nums[i]);
        a = t;
    }
    return a|b;
}
