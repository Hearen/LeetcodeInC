/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : Wed, 29 Jun 2016 21:31 CST
Description : Say you have an array for which the ith element is the price of a given stock on day i.
Design an algorithm to find the maximum profit. You may complete at most two transactions.
Note:
You may not engage in multiple transactions at the same time (ie, you must sell the stock before you buy again).
Source      : https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iii/
*******************************************/
class Solution {
public:
	//collecting from left to right and then right to left;
    int maxProfit(vector<int>& prices) 
    {
        int size = prices.size();
        if(!size) return 0;
        int lProfits[size]{0}, rProfits[size]{0};
        int preMin = prices[0], postMax = prices[size-1];
        for(int i = 1; i < size; ++i)
        {
            lProfits[i] = max(lProfits[i-1], prices[i]-preMin);
            preMin = min(preMin, prices[i]);
        }
        for(int i = size-2; i >= 0; --i)
        {
            rProfits[i] = max(rProfits[i+1], postMax-prices[i]);
            postMax = max(postMax, prices[i]);
        }
        int maxProfit = 0;
        for(int i = 0; i < size; ++i)
            maxProfit = max(maxProfit, lProfits[i]+rProfits[i]);
        return maxProfit;
    }

	//greedy solution;
	int maxProfit(vector<int>& prices) 
    {
        int k = 2, size = prices.size();
        if(k > size/2) //too big, need acceleration;
        {
            int profit = 0;
            for(int i = 1; i < size; ++i)
                if(prices[i] > prices[i-1])
                    profit += prices[i]-prices[i-1];
            return profit;
        }
        int hold[k]{0}, sold[k]{0};
        for(int i = 0; i < k; ++i) hold[i] = INT_MIN;
        for(int i = 0; i < size; ++i)
        {
            for(int j = 0; j < k; ++j)
            {
                hold[j] = max(hold[j], (j>0? sold[j-1]:0)-prices[i]);
                sold[j] = max(sold[j], hold[j]+prices[i]);
            }
        }
        return sold[k-1];
    }
};
