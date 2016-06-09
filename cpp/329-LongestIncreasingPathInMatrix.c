/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-03-05 09:36
Description : Given an integer matrix, find the length of the longest increasing path.

From each cell, you can either move to four directions: left, right, up or down. You may NOT move diagonally or move outside of the boundary (i.e. wrap-around is not allowed).

Example 1:

nums = [
[9,9,4],
[6,6,8],
[2,1,1]

]
Return 4
The longest increasing path is [1, 2, 6, 9].

Example 2:

nums = [
[3,4,5],
[3,2,6],
[2,2,1]

]
Return 4
The longest increasing path is [3, 4, 5, 6]. Moving diagonally is not allowed.
Source      : https://leetcode.com/problems/longest-increasing-path-in-a-matrix/
*******************************************/
class Solution {
private:
    int rowSize, colSize;
    int traverse(const vector<vector<int>>& matrix, vector<vector<int>>& max_lengths, int r, int c)
    {
        if(max_lengths[r][c]) return max_lengths[r][c];
        int longest = 1;
        if(r-1>-1 && matrix[r][c]>matrix[r-1][c]) longest = max(longest, traverse(matrix, max_lengths, r-1, c)+1);
        if(c-1>-1 && matrix[r][c]>matrix[r][c-1]) longest = max(longest, traverse(matrix, max_lengths, r, c-1)+1);
        if(r+1<rowSize && matrix[r][c]>matrix[r+1][c]) longest = max(longest, traverse(matrix, max_lengths, r+1, c)+1);
        if(c+1<colSize && matrix[r][c]>matrix[r][c+1]) longest = max(longest, traverse(matrix, max_lengths, r, c+1)+1);
        return max_lengths[r][c]=longest;
    }
public:
    //AC - best-submission - Memoization and DFS;
    int longestIncreasingPath(vector<vector<int>>& matrix) 
    {
        rowSize = matrix.size();
        if(!rowSize) return 0; 
        colSize = matrix[0].size();
        int longest = 0;
        vector<vector<int>> max_lengths(rowSize, vector<int>(colSize, 0));
        for(int r = 0; r < rowSize; r++)
            for(int c = 0; c < colSize; c++)
                longest = max(longest, traverse(matrix, max_lengths, r, c));
        return longest;
    }
};
