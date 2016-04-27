/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-01-12 08:21
Description : Given an integer, write a function to determine if it is a power of three.
Follow up:
Could you do it without using any loop / recursion?
Source      : https://leetcode.com/problems/power-of-three/
*******************************************/
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
//AC - direct and intuitive method;
bool isPowerOfThree0(int n)
{
    long a = 1;
    while(a <= n)
    {
        if(a==n)
            return true;
        a *= 3;
    }
    return false;
}

//AC - the following four methods are using mod;
//This process can be faster using hashmap or binary search;
bool isPowerOfThree1(int n)
{
    return (n == 1 || n == 3 || n == 9 || n == 27 || n == 81 || n == 243 || n == 729 || n == 2187 || n == 6561 || n == 19683 || n == 59049 || n == 177147 || n == 531441 || n == 1594323 || n == 4782969 || n == 14348907 || n == 43046721 || n == 129140163 || n == 387420489 || n == 1162261467);
}

bool isPowerOfThree2(int n)
{
    int maxPowerOfThree = (int)pow(3, (int)(log(INT_MAX)/log(3)));
    return n>0 && maxPowerOfThree%n==0;
}

bool isPowerOfThree3(int n)
{
    return n>0 && (int)pow(3, 19)%n==0;
}

bool isPowerOfThree4(int n)
{
    return n>0 && 1162261467%n==0;
}

//AC - the following two methods are using log;
bool isPowerOfThree5(int n)
{
    return fmod(log10(n)/log10(3), 1) == 0;
}

bool isPowerOfThree6(int n)
{
    double ret = log10(n)/log10(3);
    return ret==(int)ret;
}

