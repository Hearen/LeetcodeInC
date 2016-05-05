/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-02-12 10:43
Description : Given a 2D matrix matrix, find the sum of the elements inside the rectangle defined by its upper left corner (row1, col1) and lower right corner (row2, col2).
Range Sum Query 2D
The above rectangle (with the red border) is defined by (row1, col1) = (2, 1) and (row2, col2) = (4, 3), which contains sum = 8.
Example:
Given matrix = [
[3, 0, 1, 4, 2],
[5, 6, 3, 2, 1],
[1, 2, 0, 1, 5],
[4, 1, 0, 1, 7],
[1, 0, 3, 0, 5]
]
sumRegion(2, 1, 4, 3) -> 8
sumRegion(1, 1, 2, 2) -> 11
sumRegion(1, 2, 2, 4) -> 12
Note:
You may assume that the matrix does not change.
There are many calls to sumRegion function.
You may assume that row1 ≤ row2 and col1 ≤ col2.
Source      : https://leetcode.com/problems/range-sum-query-2d-immutable/
*******************************************/
struct NumMatrix
{
    int** sumMatrix; //sumMatrix[i][j] is the sum from (0, 0) to (i, j);
};

struct NumMatrix* NumMatrixCreate(int** matrix, int rSize, int cSize)
{
    struct NumMatrix *t = (struct NumMatrix*)malloc(sizeof(struct NumMatrix));
    t->sumMatrix = (int**)malloc(sizeof(int*)*rSize);
    int *sums = (int*)malloc(sizeof(int)*(cSize+1));
    for(int r = 0; r < rSize; r++) //from top to bottom, summing them up;
    {
        (t->sumMatrix)[r] = (int*)malloc(sizeof(int)*cSize);
        sums[0] = matrix[r][0]; //using another assistant array to store the pre-sum of the row;
        for(int i = 0; i < cSize; i++) //from left to right, add them all;
        {
            if(i > 0)
                sums[i] = sums[i-1]+matrix[r][i];
            (t->sumMatrix)[r][i] = sums[i]; //set the pre-sum of the row;
            if(r > 0) 
                (t->sumMatrix)[r][i] += (t->sumMatrix)[r-1][i];
        }
    }
    return t;
}

//AC - 8ms - summing all the sub-matrices first;
int sumRegion(struct NumMatrix* numMatrix, int row1, int col1, int row2, int col2)
{
    int** sumMatrix = numMatrix->sumMatrix;
    int ret = sumMatrix[row2][col2];
    if(row1 > 0) //only the valid sub-matrix should be checked and subtracted;
        ret -= sumMatrix[row1-1][col2];
    if(col1 > 0)
        ret -= sumMatrix[row2][col1-1];
    if(row1 > 0 && col1 > 0)
        ret += sumMatrix[row1-1][col1-1];
    return ret;
}

void NumMatrixFree(struct NumMatrix* numMatrix)
{
    free(numMatrix->sumMatrix);
    free(numMatrix);
}
