/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-01-19 15:33
Description : You are climbing a stair case. It takes n steps to reach to the top.

Each time you can either climb 1 or 2 steps. In how many distinct ways can you climb to the top?
Source      : https://leetcode.com/problems/climbing-stairs/
*******************************************/
//AC - 0ms;
int climbStairs(int n)
{
    int *arr = (int*)malloc(sizeof(int)*(n+1));
    arr[0] = arr[1] = 1;
    for(int i = 2; i <= n; i++)
        arr[i] = arr[i-1] + arr[i-2];
    return arr[n];
}
