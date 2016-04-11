/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-02-28 10:56
Description : Description:

Count the number of prime numbers less than a non-negative number, n
Source      : https://leetcode.com/problems/count-primes/
*******************************************/
#include <bool.h>
//AC - 44ms;
int countPrimes0(int n)
{
    bool *notPrimes = (bool*)malloc(sizeof(bool)*n);
    memset(notPrimes, 0, sizeof(bool)*n);
    int count = 0;
    for(int i = 2; i < n; i++)
    {
        if(!notPrimes[i])
        {
            count++;
            if(i > sqrt(n)) continue;
            for(int j = i*i; j < n; j += i)
                notPrimes[j] = true;
        }
    }
    return count;
}

//AC - 44ms;
int countPrimes1(int n)
{
    bool* primes = (bool*)malloc(sizeof(bool)*n);
    memset(primes, 1, sizeof(bool)*n);
    primes[0] = primes[1] = false;
    for(int i = 0; i < sqrt(n); ++i)
    {
        if(primes[i])
            for(int j = i*i; j < n; j += i)
                primes[j] = false;
    }
    int count = 0;
    for(int i = 0; i < n; i++)
        if(primes[i]) count++;
    return count;
}

