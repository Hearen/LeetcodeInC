/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-03-04 09:20
Description : Write a program to solve a Sudoku puzzle by filling the empty cells.
Empty cells are indicated by the character '.'.
You may assume that there will be only one unique solution.
Source      : https://leetcode.com/problems/sudoku-solver/?sort=votes
*******************************************/
class Solution {
private:
    bool search(vector<vector<char>>& board, int r, int c, bool rTakens[][9], bool cTakens[][9], bool subTakens[][9])
    {
        if(r == 9) return true; //level checking;
        if(c == 9) return search(board, r+1, 0, rTakens, cTakens, subTakens);
        if(board[r][c] != '.') return search(board, r, c+1, rTakens, cTakens, subTakens);
        for(char a = '1'; a <= '9'; ++a) //try different cases;
        {
            int num = a -'0', k = r/3*3+c/3;
            if(!(rTakens[r][num] || cTakens[c][num] || subTakens[k][num])) //filter out the invalid;
            {
                rTakens[r][num] = cTakens[c][num] = subTakens[k][num] = true;
                board[r][c] = a;
                if(search(board, r, c+1, rTakens, cTakens, subTakens)) return true;
                board[r][c] = '.'; //restore to its original state;
                rTakens[r][num] = cTakens[c][num] = subTakens[k][num] = false;
            }
        }
        return false;
    }
public:
    //AC - 4ms - best submission;
    void solveSudoku(vector<vector<char>>& board) 
    {
        bool rTakens[9][9]{{false}}, cTakens[9][9]{{false}}, subTakens[9][9]{{false}};
        for(int r = 0; r < 9; ++r) //initialize the takens;
            for(int c = 0; c < 9; ++c)
                if(board[r][c] != '.')
                {
                    int num = board[r][c] -'0', k = r/3*3+c/3;
                    rTakens[r][num] = cTakens[c][num] = subTakens[k][num] = true;
                }
        search(board, 0, 0, rTakens, cTakens, subTakens); //time to search and fill up the board;
    }
};
