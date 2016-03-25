/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-02-11 15:52
Description : Say you have an array for which the ith element is the price of a given stock on day i.
Design an algorithm to find the maximum profit. You may complete as many transactions as you like (ie, buy one and sell one share of the stock multiple times). However, you may not engage in multiple transactions at the same time (ie, you must sell the stock before you buy again).
Source      : https://leetcode.com/problems/best-time-to-buy-and-sell-stock-ii/
*******************************************/
//AC - 4ms;
int maxProfit1(int* prices, int size)
{
    if(size <= 1)
        return 0;
    int profit = 0;
    for(int i = 1; i < size; i++)
    {
        if(prices[i] > prices[i-1])
            profit += prices[i]-prices[i-1];
    }
    return profit;
}

