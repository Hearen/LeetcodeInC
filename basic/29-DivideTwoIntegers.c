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
//AC - 8ms;
int divide0(int dividend, int divisor)
{
    if(divisor == 0 || (dividend == INT_MIN && divisor == -1))
        return INT_MAX;
    int sign = (dividend < 0 ^ divisor < 0)? -1 : 1;
    long dd = fabs(dividend), dv = fabs(divisor);
    long tmp, factor;
    int res = 0;
    while(dd >= dv)
    {
        tmp = dv, factor = 1;
        while(dd >= tmp)
            factor<<=1, tmp<<=1;
        tmp >>= 1, factor >>= 1;
        dd -= tmp;
        res += factor;
    }
    return sign*res;
}

int divide1(int dividend, int divisor)
{
    //a/b = e^(lna)/e^lnb = e^(lna-lnb);
    if(dividend == 0) return 0;
    if(divisor == 0) return INT_MAX;
    long ret = exp(log(fabs(dividend))-log(fabs(divisor)));
    if(dividend<0 ^ divisor<0) ret *= -1;
    if(ret > INT_MAX) return INT_MAX;
    return ret;
}

//AC - 4ms;
int divide(int dd, int dv)
{
    if(!dv) return INT_MAX;
    if(dv == 1) return dd;
    if(dv == -1)
    {
        if(dd == INT_MIN) return INT_MAX;
        return -dd;
    }
    bool sd=dd<0, sv=dv<0;
    unsigned int nom=sd?-dd:dd, den=sv?-dv:dv;
    unsigned int r=0, ret=0;
    for(int i = 31; i > -1; i--)
    {
        r <<= 1;
        r |= (nom>>i) & 1;
        if(r >= den)
        {
            r -= den;
            ret |= 1<<i;
        }
    }
    return sd^sv? -ret : ret;
}
