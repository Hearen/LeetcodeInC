/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-01-02 10:06
Description : The n-queens puzzle is the problem of placing n queens on an n×n chessboard such that no two queens attack each other. Given an integer n, return all distinct solutions to the n-queens puzzle. Each solution contains a distinct board configuration of the n-queens' placement, where 'Q' and '.' both indicate a queen and an empty space respectively.'
Source      : https://leetcode.com/problems/n-queens/
*******************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
void traverse(int row, int n, int* stack, bool* cols, bool* fslash, bool* bslash, char**** boards, int* returnSize)
{
    if(row == n)
    {
        (*returnSize)++;
        *boards = (char***)realloc(*boards, sizeof(char**)*(*returnSize));
        (*boards)[*returnSize-1] = (char**)malloc(sizeof(char*)*n);
        for(int i = 0; i < n; i++)
        {
            (*boards)[*returnSize-1][i] = (char*)malloc(sizeof(char)*(n+1));
            for(int j = 0; j < n; j++)
                (*boards)[*returnSize-1][i][j] = '.';
            (*boards)[*returnSize-1][i][n] = '\0';
        }
        for(int i = 0; i < n; i++) //according to the recorded selected columns, set Queen;
            (*boards)[*returnSize-1][i][stack[i]] = 'Q';
        return;
    }
    for(int i = 0; i < n; i++)
    {
        int f=row+i, b=row+n-1-i;
        if(cols[i] && fslash[f] && bslash[b])
        {
            cols[i] = fslash[f] = bslash[b] = false; //set it unavailable;
            stack[row] = i; //record the selected column for the current row;
            traverse(row+1, n, stack, cols, fslash, bslash, boards, returnSize); //check the next row;
            cols[i] = fslash[f] = bslash[b] = true; //reset;
        }
    }
}

//AC - 4ms;
char*** solveNQueens(int n, int* returnSize)
{
    char*** boards = (char***)malloc(sizeof(char**));
    bool* cols = (bool*)malloc(sizeof(bool)*n);
    for(int i = 0; i < n; i++)
        cols[i] = true;
    bool* fslash = (bool*)malloc(sizeof(bool)*(2*n));
    bool* bslash = (bool*)malloc(sizeof(bool)*(2*n));
    for(int i = 0; i < 2*n; i++)
    {
        fslash[i] = true;
        bslash[i] = true;
    }
    int* stack = (int*)malloc(sizeof(int)*n); //used to record the selected column for each row;
    traverse(0, n, stack, cols, fslash, bslash, &boards, returnSize);
    return boards;
}

