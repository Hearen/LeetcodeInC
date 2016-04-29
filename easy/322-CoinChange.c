/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-02-13 15:05
Description : You are given coins of different denominations and a total amount of money amount. Write a function to compute the fewest number of coins that you need to make up that amount. If that amount of money cannot be made up by any combination of the coins, return -1.
Example 1:
coins = [1, 2, 5], amount = 11
return 3 (11 = 5 + 5 + 1)
Example 2:
coins = [2], amount = 3
return -1.
Note:
You may assume that you have an infinite number of each kind of coin.
Source      : https://leetcode.com/problems/coin-change/
*******************************************/
//AC - 40ms;
int coinChange(int* coins, int size, int amount)
{
    int *mins = (int*)malloc(sizeof(int)*(amount+1));
    for(int i = 1; i <= amount; i++)
    {
        int min = amount+1;
        for(int j = 0; j < size; j++)
        {
            int t =  i-coins[j];
            if(t >= 0)
            {
                t = mins[t]+1;
                min = t < min? t : min;
            }
        }
        mins[i] = min;
    }
    if(mins[amount] > amount)
        return -1;
    else
        return mins[amount];
}
