/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2015-12-27 20:33
Description : Divide two integers without using multiplication, division and mod operator.
If it is overflow, return MAX_INT.
Source      : https://leetcode.com/problems/divide-two-integers/
*******************************************/
#include <limits.h>
#include <cstdbool.h>


class Solution {
public:
    //AC - 12ms - bit manipulation;
    int divide(int dividend, int divisor) 
    {
        if(dividend==0 || divisor==0) return 0;
        int sign = (dividend<0 ^ divisor<0)? -1 : 1;
        long dvd = abs((long)dividend), dvr = abs((long)divisor);
        cout<<dvd<<dvr<<endl;
        long ret = 0, d = 0, t = 0;
        while(dvd > 0)
        {
            if(dvr > dvd) break;
            t = dvr, d = 0;
            while(t <= dvd) t <<= 1, d++;
            t>>=1, d--;
            ret |= (long)1<<d;
            dvd -= t;
        }
        ret *= sign;
        return ret>INT_MAX? INT_MAX : ret;
    }

    //AC - 8ms - reusing the previous temporary value to reduce redundant calculation;
    int divide(int dividend, int divisor) 
    {
        if((dividend==INT_MIN && divisor==-1) || divisor==0) return INT_MAX;
        int sign = (dividend<0 ^ divisor<0)? -1 : 1;
        long dd = abs((long)dividend), dv = abs((long)divisor);
        if(dd < dv) return 0;
        int h = 0;
        long t = dv;
        while(t <= dd) t <<= 1, h++;
        long ret = 1 << (h? --h : h);
        dd -= (t>>=1);
        while(dd >= dv)
        {
            while(t > dd)
                t >>= 1, h--;
            ret |= 1<<h;
            dd -= t;
        }
        return ret*sign;
    }
    
    //AC - 12ms - math;
    int divide(int dividend, int divisor)
    {
        if(dividend==0 || divisor==0) return 0;
        long ret = exp(log(fabs(dividend))-log(fabs(divisor)));
        if(dividend<0 ^ divisor<0) ret *= -1;
        return ret>INT_MAX? INT_MAX : ret;
    }

    //AC - 12ms - using div;
    int divide(int dividend, int divisor)
    {
        if(dividend==INT_MIN && divisor==-1) return INT_MAX;
        div_t divresult = div(dividend, divisor);
        return divresult.quot;
    }
};
