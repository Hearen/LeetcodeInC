/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-02-12 16:49
Description : Given a positive integer n, find the least number of perfect square numbers (for example, 1, 4, 9, 16, ...) which sum to n.
For example, given n = 12, return 3 because 12 = 4 + 4 + 4; given n = 13, return 2 because 13 = 4 + 9.
Source      : https://leetcode.com/problems/perfect-squares/
*******************************************/
#include <limits.h>
//AC - 144ms - DP method;
int numSquares0(int n)
{
    int *mins = (int*)malloc(sizeof(int)*(n+1)); //store the minimal number of the PerfectSquare;
    mins[0] = 0;
    for(int i = 1; i <= n; i++)
    {
        int min = INT_MAX;
        int square = 1;
        for(int r=1; square <= i; r++) //traverse the previous result to get the min;
        {
            int t = mins[i-square]+1;
            min = t < min? t : min;
            square = r*r;
        }
        mins[i] = min;
    }
    return mins[n];
}

int helper(int n)
{
    static int mins[1000000]; //using static feature to avoid redundant searching;
    mins[0] = 0;
    for(int i = 1; i <= n; i++)
    {
        int min = INT_MAX;
        int square = 1;
        for(int r=1; square <= i; r++)
        {
            int t = mins[i-square]+1;
            min = t < min? t : min;
            square = r*r;
        }
        mins[i] = min;
    }
    return mins[n];
}

//AC - 124ms;
int numSquares1(int n)
{
    return helper(n);
}

//AC - 4ms - mathematical method;
int numSquares(int n)
{
    //Based on Lagrange's Four Square theorem, there 
    //are only 4 possible results: 1, 2, 3, 4.
    //The result is 4 if and only if n can be written in the form of 4^k*(8*m + 7).
    while(n%4 == 0) //(n & 3) == 0
        n >>= 2;
    if(n%8 == 7)
        return 4;
    for(int a=0; a*a <= n; ++a) //consider 1 and 2;
    {
        int b = sqrt(n-a*a);
        if(a*a + b*b == n)
            return 1+!!a; //if a==0, then return 1 otherwise return 2;
    }
    return 3;
}
