/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-02-11 21:39
Description : Say you have an array for which the ith element is the price of a given stock on day i.
Design an algorithm to find the maximum profit. You may complete as many transactions as you like (ie, buy one and sell one share of the stock multiple times) with the following restrictions:
You may not engage in multiple transactions at the same time (ie, you must sell the stock before you buy again).
After you sell your stock, you cannot buy stock on next day. (ie, cooldown 1 day)
Example:

prices = [1, 2, 3, 0, 2]
maxProfit = 3
transactions = [buy, sell, cooldown, buy, sell]
Source      : https://leetcode.com/problems/best-time-to-buy-and-sell-stock-with-cooldown/
*******************************************/
#include <limits.h>
//AC - 4ms;
//https://leetcode.com/discuss/71354/share-my-thinking-process
#define MAX(a, b) (a)>(b)? (a):(b)
int maxProfit(int* prices, int size)
{
    int preBuy = INT_MIN, curBuy = INT_MIN;
    int preSell = 0, curSell = 0;
    for(int i = 0; i < size; i++)
    {
        preBuy = curBuy;
        curBuy = MAX(curBuy, preSell-prices[i]); //preSell -> sell[i-2], curBuy -> buy[i-1];
        preSell = curSell;
        curSell = MAX(curSell, preBuy+prices[i]); //curSell -> sell[i-1], preBuy -> buy[i-1];
    }
    return curSell;
}
