/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-01-12 20:07
Description : Given a 2D board containing 'X' and 'O', capture all regions surrounded by 'X'.
A region is captured by flipping all 'O's into 'X's in that surrounded region.
For example,
X X X X
X O O X
X X O X
X O X X
After running your function, the board should be:
X X X X
X X X X
X X X X
X O X X
Source      : https://leetcode.com/problems/surrounded-regions/
*******************************************/
class Solution {
private:
    const char mask = 'a';
    const char big_O = 'O';
    const char big_X = 'X';
    int rowSize, colSize;
    //be careful of the edges here;
    void fillup(vector<vector<char>>& board, int r, int c)
    {
        if(board[r][c] != big_O) return ;  //in case of re-checking backwards;
        board[r][c] = mask;
        if(r-1>0 && board[r-1][c]==big_O) fillup(board, r-1, c);
        if(c-1>0 && board[r][c-1]==big_O) fillup(board, r, c-1);
        if(r+2<rowSize && board[r+1][c]==big_O) fillup(board, r+1, c);
        if(c+2<colSize && board[r][c+1]==big_O) fillup(board, r, c+1);
    }

public:
    void solve(vector<vector<char>>& board) 
    {
        rowSize = board.size();
        if(!rowSize) return ;
        colSize = board[0].size();
        for(int r = 0; r < rowSize; r++)
        for(int c = 0; c < colSize; c++)
            if((c==0 || c==colSize-1 || r==0 || r==rowSize-1) && board[r][c]==big_O) 
                fillup(board, r, c);
        for(int r = 0; r < rowSize; r++)
            for(int c = 0; c < colSize; c++)
            {
                if(board[r][c] == mask) board[r][c] = big_O;
                else board[r][c] = big_X;
            }
    }
    void solve(vector<vector<char>>& board) 
    {
        int rowSize = board.size();
        if(!rowSize) return ; 
        int colSize = board[0].size();
        stack<int> rows, cols;
        for(int r = 0; r < rowSize; r++)
        for(int c = 0; c < colSize; c++)
        if((r==0 || r==rowSize-1 || c==0 || c==colSize-1) && board[r][c] == 'O') rows.push(r), cols.push(c);
        while(!rows.empty())
        {
            int r=rows.top(), c=cols.top();
            board[r][c] = mask;
            rows.pop(), cols.pop();
            if(r-1>-1 && board[r-1][c]=='O') rows.push(r-1), cols.push(c);
            if(r+1<rowSize && board[r+1][c]=='O') rows.push(r+1), cols.push(c);
            if(c-1>-1 && board[r][c-1]=='O') rows.push(r), cols.push(c-1);
            if(c+1<colSize && board[r][c+1]=='O') rows.push(r), cols.push(c+1);
        }
        for(int r = 0; r < rowSize; r++)
            for(int c = 0; c < colSize; c++)
                if(board[r][c] == mask) board[r][c] = 'O';
                else board[r][c] = 'X';
    }
};
