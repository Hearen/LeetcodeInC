/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2015-12-22 20:53
Description : Implement int sqrt(int x).

Compute and return the square root of x.
Source      : https://leetcode.com/problems/sqrtx/
*******************************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
//Newton method - 8ms;
int intSqrt(int x)
{
    long g = x;
    while(g*g > x)
        g = (g + x/g) / 2;
    return g; 
}

//bit manipulation - 4ms or 8ms due to format;
int bitSqrt(int x)
{
    if(x == 0 || x == 1)
        return x;
    int h = 0;
    while((long)(1 << h) * (long)(1 << h) <= x)
        h++;
    h--;
    int d = h - 1;
    int res = (1 << h);
    while(d >= 0)
    {
        if((long)(res | 1 << d)*(long)(res | 1 << d) <= x)
            res |= (1 << d);
        d--;
    }
    return res;
}

