/*******************************************
Author: LHearen
E-mail: LHearen@126.com
Time  :	2015-12-03 08:02
Description: A robot is located at the top-left corner of a m x n grid (marked 'Start' in the diagram below).
The robot can only move either down or right at any point in time. The robot is trying to reach the bottom-right corner of the grid (marked 'Finish' in the diagram below).
How many possible unique paths are there?

Above is a 3 x 7 grid. How many possible unique paths are there?

Note: m and n will be at most 100.
Source: https://leetcode.com/problems/unique-paths/
*******************************************/
//member must be long long to handle big integer;
//AC - 0ms;
int uniquePaths0(int m, int n)
{
    if(m > n) return uniquePaths(n, m);
    m--, n--;
    long long denominator = 1;
    long long member = 1;
    while(m > 0)
    {
        member *= m + n;
        denominator *= m;
        m--;
    }
    return member / denominator;
}

//AC - 0ms;
int uniquePaths(int m, int n)
{
    if(m > n) return uniquePaths(n, m);
    int *arr = (int*)malloc(sizeof(int)*m);
    for(int i = 0; i < m; i++)
        arr[i] = 1;
    for(int i = 1; i < n; i++)
        for(int j = 1; j < m; j++)
            arr[j] += arr[j-1];
    return arr[m-1];
}
