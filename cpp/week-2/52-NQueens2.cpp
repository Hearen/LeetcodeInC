/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : Wed, 22 Jun 2016 08:32 CST
Description : Follow up for N-Queens problem.
Now, instead outputting board configurations, return the total number of distinct solutions.
Source      : https://leetcode.com/problems/n-queens-ii/
*******************************************/
class Solution {
private:
    int search(int n, int r, vector<int>& forward, vector<int>& backward, vector<int>& cols)
    {
        if(n == r) return 1;
        int sum = 0;
        for(int c = 0; c < n; ++c)
        {
            if(!forward[r+c] && !backward[n+r-c-1] && !cols[c])
            {
                forward[r+c] = backward[n+r-c-1] = cols[c] = 1;
                sum += search(n, r+1, forward, backward, cols);
                forward[r+c] = backward[n+r-c-1] = cols[c] = 0;
            }
        }
        return sum;
    }

public:
    //AC - best submission;
    int totalNQueens(int n) 
    {
        vector<int> forward(2*n-1), backward(2*n-1), cols(n); //using int is more efficient than bool;
        int count = 0;
        return search(n, 0, forward, backward, cols);
    }
};
