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

class Solution {
public:
    //AC - 8ms - binary search;
    int mySqrt(int x) 
    {
        if(x == 0) return 0;
        if(x == 1) return 1;
        int l = 0, r = x;
        while(true)
        {
            int m = l+(r-l)/2;
            if(m > x/m) r = m-1;
            else
            {
                if(m+1 > x/(m+1)) return m;
                l = m+1;
            }
        }
    }

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
        if(x == 0 || x == 1) return x;
        int h = 0;
        while((long)(1 << h) * (long)(1 << h) <= x) h++;
        h--;
        int d = h - 1;
        int res = (1 << h);
        while(d >= 0)
        {
            if((res | 1 << d)*(res | 1 << d) <= x)
                res |= (1 << d);
            d--;
        }
        return res;
    }
};
