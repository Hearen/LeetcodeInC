/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2015-12-02 21:28
Description : Given a 2D board and a word, find if the word exists in the grid.
The word can be constructed from letters of sequentially adjacent cell, where "adjacent" cells are those horizontally or vertically neighboring. The same letter cell may not be used more than once.

For example,
Given board =

[
['A','B','C','E'],
['S','F','C','S'],
['A','D','E','E']
]
word = "ABCCED", -> returns true,
word = "SEE", -> returns true,
word = "ABCB", -> returns false.
Source      : https://leetcode.com/problems/word-search/
*******************************************/
#include"utils.h"
//using recursive function to achieve backtracking;
//the termination conditions should be carefully handled;
bool isFound(char** board, int row, int col, char*word, int rIndex, int cIndex)
{
    if(rIndex >= row || cIndex >= col || rIndex < 0 || cIndex < 0 || *word != board[rIndex][cIndex])
        return false;
    if(*(word+1) == '\0')
        return true;
    char t = board[rIndex][cIndex];
    //avoid re-visiting;
    board[rIndex][cIndex] = '\0';
    if(isFound(board, row, col, word + 1, rIndex + 1, cIndex) || isFound(board, row, col, word + 1, rIndex - 1, cIndex) ||
            isFound(board, row, col, word + 1, rIndex, cIndex + 1) || isFound(board, row, col, word + 1, rIndex, cIndex - 1))
        return true;
    board[rIndex][cIndex] = t;
    return false;
}

bool exist(char** board, char row, int col, char* word)
{
    //start the searching from every point;
    for(int i = 0; i < row; i++)
        for(int j = 0; j < col; j++)
        {
            if(isFound(board, row, col, word, i, j))
                return true;
        }
    return false;
}
