/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-03-01 19:06
Description : Write a program to find the nth super ugly number.
Super ugly numbers are positive numbers whose all prime factors are in the given prime list primes of size k. For example, [1, 2, 4, 7, 8, 13, 14, 16, 19, 26, 28, 32] is the sequence of the first 12 super ugly numbers given primes = [2, 7, 13, 19] of size 4.

Note:
(1) 1 is a super ugly number for any given primes.
(2) The given numbers in primes are in ascending order.
(3) 0 < k ≤ 100, 0 < n ≤ 106, 0 < primes[i] < 1000.
Source      : https://leetcode.com/problems/super-ugly-number/
*******************************************/
#include <limits.h>
//AC - 40ms;
int nthSuperUglyNumber0(int n, int* primes, int size)
{
    int *uglies = (int*)malloc(sizeof(int)*n);
    uglies[0] = 1; //the first SuperUgly;
    int *indexes = (int*)malloc(sizeof(int)*size); //each prime will be related to the biggest SuperUgly number in uglies - using this array can eliminate redundant checking;
    memset(indexes, 0, sizeof(int)*size); //all pointing to the first SuperUgly first;
    for(int i = 1; i < n; i++)
    {
        uglies[i] = INT_MAX;
        for(int j = 0; j < size; j++) //search for the smallest that can be retrieved from primes and former SuperUgly numbers;
        {
            int t = uglies[indexes[j]]*primes[j];
            if(uglies[i] > t)
                uglies[i] = t;
        }
        for(int j = 0; j < size; j++) //make sure there will be no duplicate, so that we can find the next smallest as before;
            indexes[j] += (uglies[i]==uglies[indexes[j]]*primes[j]);
    }
    return uglies[n-1];
}

int getMin(int* factors, int len)
{
    int min = factors[0];
    for(int i = 1; i < len; i++)
        if(factors[i] < min) min = factors[i];
    return min;
}
//AC - 36ms - optimized based on the previous solution
//eliminate lots of multiplications;
int nthSuperUglyNumber(int n, int* primes, int size)
{
    int *indexes = (int*)malloc(sizeof(int)*size);
    int *factors = (int*)malloc(sizeof(int)*size);
    int *uglies = (int*)malloc(sizeof(int)*n);
    uglies[0] = 1;
    int min;
    memset(indexes, 0, sizeof(int)*size);
    memcpy(factors, primes, sizeof(int)*size);
    for(int i = 1; i < n; i++)
    {
        min = getMin(factors, size);
        uglies[i] = min;
        for(int j = 0; j < size; j++)
            if(min == factors[j]) 
                factors[j] = primes[j]*uglies[++indexes[j]];
    }
    return uglies[n-1];
}
