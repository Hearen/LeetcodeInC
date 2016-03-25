/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-02-11 17:15
Description : Say you have an array for which the ith element is the price of a given stock on day i.
Design an algorithm to find the maximum profit. You may complete at most k transactions.
Note:
You may not engage in multiple transactions at the same time (ie, you must sell the stock before you buy again).
Source      : https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iv/
*******************************************/
//AC - 4ms;
#include <limits.h>
#define MAX(a, b) (a)>(b)? (a):(b)
int maxProfit0(int k, int* prices, int size)
{
    if(size < 2)
        return 0;
   if(k > size/2) //when it's unlimited, it can be easily handled -> corner case;
    {
        int profit = 0;
        for(int i=1; i < size; i++)
            if(prices[i] > prices[i-1])
                profit += prices[i]-prices[i-1];
        return profit;
    }
    int** t = (int**)malloc(sizeof(int*)*(k+1));
    for(int i = 0; i <= k; i++)
    {
        t[i] = (int*)malloc(sizeof(int)*size);
        memset(t[i], 0, sizeof(int)*size);
    }
    int cur = 0;
    for(int i=1; i <= k; i++)
    {
        cur = -prices[0];
        for(int j = 1; j < size; j++)
        {
            t[i][j] = MAX(t[i][j-1], prices[j]+cur); //max profit sell at j;
            cur = MAX(cur, t[i-1][j-1]-prices[j]); //max profit buy at j;
        }
    }
    return t[k][size-1];
}

int maxProfit(int k, int* prices, int size)
{
    if(size < 2)
        return 0;
   if(k > size/2) //when it's unlimited, it can be easily handled -> corner case;
    {
        int profit = 0;
        for(int i=1; i < size; i++)
            if(prices[i] > prices[i-1])
                profit += prices[i]-prices[i-1];
        return profit;
    }
    int *holds = (int*)malloc(sizeof(int)*k);
    int *solds = (int*)malloc(sizeof(int)*k);
    memset(solds, 0, sizeof(int)*k);
    for(int i = 0; i < k; i++)
        holds[i] = INT_MIN;
    for(int i=0; i < size; i++)
    {
        for(int j = 0; j < k; j++)
        {
            holds[j] = MAX(holds[j], (j>0? solds[j-1]:0)-prices[i]);
            solds[j] = MAX(solds[j], holds[j]+prices[i]);
        }
    }
    return solds[k-1];
}
