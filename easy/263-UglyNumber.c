/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-01-14 15:38
Description : Write a program to check whether a given number is an ugly number.
Ugly numbers are positive numbers whose prime factors only include 2, 3, 5. For example, 6, 8 are ugly while 14 is not ugly since it includes another prime factor 7.
Note that 1 is typically treated as an ugly number.
Source      : https://leetcode.com/problems/ugly-number/
*******************************************/
#include <stdbool.h>
//AC - 4ms;
bool isUgly0(int n)
{
    if(n == 1)
        return true;
    if(n <= 0)
        return false;
    int next = n;
    while(n > 0)
    {
        if(n % 2 == 0) next = n/2;
        else if(n % 3 == 0) next = n/3;
        else if(n % 5 == 0) next = n/5;
        if(next == 1) return true;
        if(n == next) return false; //if n stays the same which means n can not be divided by 2, 3, 5;
        n = next;
    }
}

bool isUgly(int n)
{
    if(n == 0) return false;
    while(n%2 == 0) n /= 2;
    while(n%3 == 0) n /= 3;
    while(n%5 == 0) n /= 5;
    return n==1;
}

//AC - 4ms - more terse;
bool isUgly1(int n)
{
    for(int i = 2; i<6 && n; i++) //i=4 will be skipped since i=2 will be handled first;
        while(n%i == 0)
            n /= i;
    return n==1;
}

