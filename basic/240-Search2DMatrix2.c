/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2015-12-25 15:17
Description : Write an efficient algorithm that searches for a value in an m x n matrix. This matrix has the following properties:
Integers in each row are sorted in ascending from left to right.
Integers in each column are sorted in ascending from top to bottom.
For example,
Consider the following matrix:
[
[1,   4,  7, 11, 15],
[2,   5,  8, 12, 19],
[3,   6,  9, 16, 22],
[10, 13, 14, 17, 24],
[18, 21, 23, 26, 30]
]
Given target = 5, return true.
Given target = 20, return false.
Source      : https://leetcode.com/problems/search-a-2d-matrix-ii/
*******************************************/
#include <stdbool.h>
bool search(int* a, int size, int target)
{
    if(target<a[0] || target>a[size-1]) return false;
    int l=0, h=size-1;
    while(l < h)
    {
        int m = (l+h)/2;
        if(a[m] < target) l = m+1;
        else if(a[m] > target) h = m-1;
        else return true;
    }
    return a[l]==target;
}

//AC - 120ms - basic binary search;
bool searchMatrix0(int** matrix, int rSize, int cSize, int target)
{
    for(int i = 0; i < rSize; i++)
    {
        if(search(matrix[i], cSize, target))
            return true;
    }
    return false;
}

//AC - 52ms - getting closer and closer to the target
bool searchMatrix(int** matrix, int rSize, int cSize, int target)
{
    int r=rSize-1, c=0;
    while(r>-1 && c < cSize)
    {
        if(matrix[r][c] < target) c++;
        else if(matrix[r][c] > target) r--;
        else return true;
    }
    return false;
}
