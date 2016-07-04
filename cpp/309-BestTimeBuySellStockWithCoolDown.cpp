/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : Thu, 30 Jun 2016 08:44 CST
Description : Say you have an array for which the ith element is the price of a given stock on day i.
Design an algorithm to find the maximum profit. You may complete as many transactions as you like (ie, buy one and sell one share of the stock multiple times) with the following restrictions:

- You may not engage in multiple transactions at the same time (ie, you must sell the stock before you buy again).
- After you sell your stock, you cannot buy stock on next day. (ie, cooldown 1 day)

Example:
prices = [1, 2, 3, 0, 2]
maxProfit = 3
transactions = [buy, sell, cooldown, buy, sell]
Source      : https://leetcode.com/problems/best-time-to-buy-and-sell-stock-with-cooldown/
*******************************************/
class Solution {
public:
    int maxProfit(vector<int>& prices) 
    {
        int preBuy = INT_MIN, curBuy = INT_MIN;
        int preSell = 0, curSell = 0;
        for(int i = 0; i < prices.size(); ++i)
        {
            preBuy = curBuy;
            curBuy = max(curBuy, preSell-prices[i]);//cannot buy on the next day;
            preSell = curSell;
            curSell = max(curSell, preBuy+prices[i]);//cannot engage in multiple at the same time;
        }
        return curSell;
    }
};
