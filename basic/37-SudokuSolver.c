/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-03-04 09:20
Description : Write a program to solve a Sudoku puzzle by filling the empty cells.
Empty cells are indicated by the character '.'.
You may assume that there will be only one unique solution.
Source      : https://leetcode.com/problems/sudoku-solver/?sort=votes
*******************************************/
#include <bool.h>
bool check(char** board, int r, int c, char a) //check it in row, column and the sub three-dimension cube;
{
    for(int i = 0; i < 9; i++) if(board[r][i]==a || board[i][c]==a) return false;
    int r0=r-r%3, c0=c-c%3; //get the start row and column of the sub cube;
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            if(board[r0+i][c0+j] == a) return false;
    return true;
}
bool solver0(char** board, int r, int c) //check and try it from left to right and then downwards;
{
    if(r == 9) return true; //now till the end and nothing wrong so far, so return true;
    if(c == 9) return solver(board, r+1, 0); //till the end of the current row and then downwards;
    if(board[r][c] != '.') return solver(board, r, c+1); //already taken just move to the next;
    for(char a = '1'; a <= '9'; a++) //try each possible candidate;
    {
        if(check(board, r, c, a)) //check its validity;
        {
            board[r][c] = a; //set it then and just move to the next;
            if(solver(board, r, c+1)) return true; //if it's solvable then just return true;
            board[r][c] = '.'; //restore it for easier checking in the next round;
        }
    }
    return false; //nothing works around then return false;
}
//AC - 12ms;
void solveSudoku0(char** board, int rSize, int cSize)
{
    solver(board, 0, 0); //start from the top-left position to the bottom right end;
}

bool solver(char** board, int r, int c, bool rTaken[][9], bool cTaken[][9], bool subTaken[][9]) //check and try it from left to right and then downwards;
{
    if(r == 9) return true; //now till the end and nothing wrong so far, so return true;
    if(c == 9) return solver(board, r+1, 0, rTaken, cTaken, subTaken); //till the end of the current row and then downwards;
    if(board[r][c] != '.') return solver(board, r, c+1, rTaken, cTaken, subTaken); //already taken just move to the next;
    for(char a = '1'; a <= '9'; a++) //try each possible candidate;
    {
        int num=a-'1', k=r/3*3+c/3;
        if(!(rTaken[r][num] || cTaken[c][num] || subTaken[k][num])) //check its validity;
        {
            rTaken[r][num] = cTaken[c][num] = subTaken[k][num] = true;
            board[r][c] = a; //set it then and just move to the next;
            if(solver(board, r, c+1, rTaken, cTaken, subTaken)) return true; //if it's solvable then just return true;
            board[r][c] = '.'; //restore it for easier checking in the next round;
            rTaken[r][num] = cTaken[c][num] = subTaken[k][num] = false;
        }
    }
    return false; //nothing works around then return false;
}

//AC - 4ms;
void solveSudoku(char** board, int rSize, int cSize)
{
    bool rTaken[9][9]={0}, cTaken[9][9]={0}, subTaken[9][9]={0};
    for(int r = 0; r < rSize; r++)
    {
        for(int c = 0; c < cSize; c++)
            if(board[r][c] != '.')
            {
                int num=board[r][c]-'1', k=r/3*3+c/3;
                rTaken[r][num] = true;
                cTaken[c][num] = true;
                subTaken[k][num] = true;
            }
    }
    solver(board, 0, 0, rTaken, cTaken, subTaken); //start from the top-left position to the bottom right end;
}
