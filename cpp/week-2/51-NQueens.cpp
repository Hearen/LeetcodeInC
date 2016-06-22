/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : Wed, 22 Jun 2016 08:39 CST
Description : The n-queens puzzle is the problem of placing n queens on an n×n chessboard such that no two queens attack each other.
Given an integer n, return all distinct solutions to the n-queens puzzle.
Each solution contains a distinct board configuration of the n-queens' placement, where 'Q' and '.' both indicate a queen and an empty space respectively.
For example,
There exist two distinct solutions to the 4-queens puzzle:
[
[".Q..",  // Solution 1
"...Q",
"Q...",
"..Q."],
["..Q.",  // Solution 2
"Q...",
"...Q",
".Q.."]
]
Source      : https://leetcode.com/problems/n-queens/
*******************************************/
class Solution {
private:
    void search(int n, int r, vector<string>& v, vector<vector<string>>& vv, vector<int>& forward, vector<int>& backward, 
    vector<int>& columns)
    {
        if(r == n) vv.push_back(v);
        for(int c = 0; c < n; c++)
        {
            if(!forward[c+r] && !backward[r+n-c-1] && !columns[c])
            {
                v[r][c] = 'Q';
                forward[c+r] = backward[r+n-c-1] = columns[c] = 1;
                search(n, r+1, v, vv, forward, backward, columns);
                forward[c+r] = backward[r+n-c-1] = columns[c] = 0;
                v[r][c] = '.';
            }
        }
    }
public:
    //AC - 4ms - best submission;
    vector<vector<string>> solveNQueens(int n) 
    {
        vector<int> forward(2*n-1), backward(2*n-1), columns(n); //using int instead of bool accelerate from 16ms to 8ms;
        vector<vector<string>> vv;
        vector<string> v(n, string(n, '.')); //using predefined board instead of creating a new string each time, accelerating from 8ms to 4ms;
        search(n, 0, v, vv, forward, backward, columns);
        return vv;
    }
};
