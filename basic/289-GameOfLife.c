/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-02-25 21:20
Description : According to the Wikipedia's article: "The Game of Life, also known simply as Life, is a cellular automaton devised by the British mathematician John Horton Conway in 1970."
Given a board with m by n cells, each cell has an initial state live (1) or dead (0). Each cell interacts with its eight neighbors (horizontal, vertical, diagonal) using the following four rules (taken from the above Wikipedia article):

Any live cell with fewer than two live neighbors dies, as if caused by under-population.
Any live cell with two or three live neighbors lives on to the next generation.
Any live cell with more than three live neighbors dies, as if by over-population..
Any dead cell with exactly three live neighbors becomes a live cell, as if by reproduction.
Write a function to compute the next state (after one update) of the board given its current state.

Follow up: 
Could you solve it in-place? Remember that the board needs to be updated at the same time: You cannot update some cells first and then use their updated values to update other cells.
In this question, we represent the board using a 2D array. In principle, the board is infinite, which would cause problems when the active area encroaches the border of the array. How would you address these problems?
Source      : https://leetcode.com/problems/game-of-life/
*******************************************/
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))
//in-place solution using bit manipulation;
void gameOfLife(int** board, int rSize, int cSize)
{
    for(int i = 0; i < rSize; i++)
        for(int j = 0; j < cSize; j++)
        {
            int count = 0;
            for(int rr = MAX(i-1, 0); rr < MIN(i+2, rSize); rr++)
                for(int cc = MAX(j-1, 0); cc < MIN(j+2, cSize); cc++)
                    count += board[rr][cc]&1; //in-place;
            count -= board[i][j];
            if(count==3 || (board[i][j]&&count==2))
                board[i][j] |= 2;
        }
    for(int i = 0; i < rSize; i++)
        for(int j = 0; j < cSize; j++)
            board[i][j] >>= 1;
}
