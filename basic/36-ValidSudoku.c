/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-01-20 14:47
Description : Determine if a Sudoku is valid, according to: Sudoku Puzzles - The Rules.
The Sudoku board could be partially filled, where empty cells are filled with the character '.'.
A partially filled sudoku which is valid.

Note:
A valid Sudoku board (partially filled) is not necessarily solvable. Only the filled cells need to be validated.
Source      : https://leetcode.com/problems/valid-sudoku/
*******************************************/
#include <stdbool.h>
//AC - 4ms;
bool isValidSudoku0(char** board, int rSize, int cSize)
{
    int a[10];
    int space = sizeof(int)*10;
    for(int i = 0; i < rSize; i++)
    {
        memset(a, 0, space);
        for(int j = 0; j < cSize; j++)
        {
            if(board[i][j] != '.')
                if(a[board[i][j]-'0']++)
                    return false;
        }
    }
    for(int i = 0; i < cSize; i++)
    {
        memset(a, 0, space);
        for(int j = 0; j < rSize; j++)
        {
            if(board[j][i] != '.')
                if(a[board[j][i]-'0']++)
                    return false;
        }
    }
    for(int row = 0; row < 9; row += 3)
        for(int col = 0; col < 9; col +=3)
        {
            memset(a, 0, space);
            for(int i = 0; i < 3; i++)
                for(int j = 0; j < 3; j++)
                {
                    if(board[row+i][col+j] != '.')
                        if(a[board[row+i][col+j]-'0']++)
                            return false;
                } 
        }
    return true;
}

bool isValidSudoku(char** board, int rSize, int cSize)
{
    bool rTaken[9][9]={0}, cTaken[9][9]={0}, subTaken[9][9]={0};
    for(int r = 0; r < rSize; r++)
        for(int c = 0; c < cSize; c++)
            if(board[r][c] != '.')
            {
                int num=board[r][c]-'0'-1, ith=r/3*3+c/3;
                if(rTaken[r][num] || cTaken[c][num] || subTaken[ith][num])
                    return false;
                rTaken[r][num] = cTaken[c][num] = subTaken[ith][num] = true;
            }
    return true;
}
