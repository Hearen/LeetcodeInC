/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-02-26 08:42
Description : Given a matrix of m x n elements (m rows, n columns), return all elements of the matrix in spiral order.
For example,
Given the following matrix:

[
[ 1, 2, 3  ],
[ 4, 5, 6  ],
[ 7, 8, 9  ]
]
You should return [1,2,3,6,9,8,7,4,5].
Source      : https://leetcode.com/problems/spiral-matrix/
*******************************************/
#include <stdlib.h>
//AC - 0ms;
int* spiralOrder0(int** matrix, int rSize, int cSize)
{
    int count = 0;
    int size = rSize*cSize;
    int *arr = (int*)malloc(sizeof(int)*size);
    int rmin=0, rmax=rSize-1;
    int cmin=0, cmax=cSize-1;
    while(count < size)
    {
        for(int c = cmin; c <= cmax; c++) //from left to right including the last;
            arr[count++] = matrix[rmin][c];
        if(count == size) break; //only one row;
        for(int r = rmin+1; r <= rmax; r++) //from top to bottom including the last;
            arr[count++] = matrix[r][cmax];
        if(count == size) break; //only one column;
        for(int c = cmax-1; c >= cmin; c--) //from right to left including the last;
            arr[count++] = matrix[rmax][c];
        for(int r = rmax-1; r > rmin; r--) //from bottom to top excluding the last;
            arr[count++] = matrix[r][cmin];
        rmin++; rmax--; cmin++; cmax--;
    }
    return arr;
}

int* spiralOrder(int** matrix, int rSize, int cSize)
{
    if(!rSize || !cSize) return NULL;
    int dirs[][2] = {{0,1}, {1,0}, {0,-1}, {-1,0}};
    int *arr = (int*)malloc(sizeof(int)*rSize*cSize);
    int index = 0;
    int steps[] = {cSize, rSize-1};
    int d = 0; //index of directions;
    int r=0, c=-1; //start position;
    while(steps[d%2])
    {
        for(int i = 0; i < steps[d%2]; i++)
        {
            r+=dirs[d][0], c+=dirs[d][1];
            arr[index++] = matrix[r][c];
        }
        steps[d%2]--;
        d = (d+1)%4;
    }
    return arr;
}
