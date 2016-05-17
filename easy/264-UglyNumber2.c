/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-01-22 16:18
Description : Write a program to find the n-th ugly number.
Ugly numbers are positive numbers whose prime factors only include 2, 3, 5. For example, 1, 2, 3, 4, 5, 6, 8, 9, 10, 12 is the sequence of the first 10 ugly numbers.
Note that 1 is typically treated as an ugly number.
Source      : https://leetcode.com/problems/ugly-number-ii/
*******************************************/
#include <limits.h>
//AC - 4ms;
int nthUglyNumber0(int n)
{
    if(n < 1) return 0; //corner cases;
    if(n == 1) return 1;
    int *arr = (int*)malloc(sizeof(int)*n);
    int i2=0, i3=0, i5=0;
    arr[0] = 1;
    for(int i = 1; i < n; i++)
    {
        int t2 = arr[i2]*2;
        int t3 = arr[i3]*3;
        int t5 = arr[i5]*5;
        int min = t2;
        if(min > t3) //select the smallest for the next ugly number;
            min = t3;
        if(min > t5)
            min = t5;
        arr[i] = min;
        if(min == t2) //update the indexes respectively;
            i2++;
        if(min == t3)
            i3++;
        if(min == t5)
            i5++;
    }
    return arr[n-1];
}

int nthUglyNumber(int n)
{
    if(n < 0) return 0;
    if(n == 1) return 1;
    int *arr = (int*)malloc(sizeof(int)*n);
    arr[0] = 1;
    int factors[] = {2, 3, 5};
    int indexes[] = {0, 0, 0};
    int t[] = {0, 0, 0};
    for(int i = 1; i < n; i++)
    {
        int min = INT_MAX;
        for(int j = 0; j < sizeof(factors)/sizeof(int); j++)
            if((t[j]=arr[indexes[j]]*factors[j]) < min)
                min = t[j];
        arr[i] = min;
        for(int j = 0; j < sizeof(factors)/sizeof(int); j++)
            if(t[j] == min)
                indexes[j]++;
    }
    return arr[n-1];
}
