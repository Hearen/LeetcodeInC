/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-02-12 16:49
Description : Given a positive integer n, find the least number of perfect square numbers (for example, 1, 4, 9, 16, ...) which sum to n.
For example, given n = 12, return 3 because 12 = 4 + 4 + 4; given n = 13, return 2 because 13 = 4 + 9.
Source      : https://leetcode.com/problems/perfect-squares/
*******************************************/
class Solution {
public:
    //AC - 8ms - mathematical method;
    int numSquares(int n) 
    {
        int t = n;
        //Based on Lagrange's Four Square theorem, there 
        //are only 4 possible results: 1, 2, 3, 4.
        //The result is 4 if and only if n can be written in the form of 4^k*(8*m + 7).
        while((t&3) == 0) t >>= 2;
        if(t%8 == 7) return 4;
        for(int a = sqrt(n); a > -1; a--)
        {
            int b = sqrt(n-a*a);
            if(n == b*b+a*a) return b==0? 1 : 2;
        }
        return 3;
    }

    //AC - 12ms - DP;
    int numSquares(int n) 
    {
        static vector<int> v({0, 1}); //using static accelerate from 324ms to 12ms;
        while(v.size() <= n)
        {
            int a = v.size();
            int t = a;
            for(int j = sqrt(a); j > 0; j--)
            {
                int b = a-j*j;
                if(!b) t = 1;
                else t = min(t, 1+v[b]);
            }
            v.push_back(t);
        }
        return v[n];
    }
};
