/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-01-20 10:33
Description : Given numRows, generate the first numRows of Pascal's triangle.
For example, given numRows = 5,
Return
[
[1],
[1,1],
[1,2,1],
[1,3,3,1],
[1,4,6,4,1]
]
Source      : https://leetcode.com/problems/pascals-triangle/
*******************************************/
#include <stdlib.h>
//AC - 0ms;
int** generate(int rSize, int** colSizes)
{
    if(rSize == 0)
        return NULL;
    *colSizes = (int*)malloc(sizeof(int)*rSize);
    int** arrs = (int**)malloc(sizeof(int*)*rSize);
    for(int i = 0; i < rSize; i++)
    {
        (*colSizes)[i] = i+1;
        arrs[i] = (int*)malloc(sizeof(int)*(i+1));
        for(int j = 0; j < i+1; j++)
            arrs[i][j] = 1;
    }
    for(int i = 2; i < rSize; i++)
        for(int j = 1; j < (*colSizes)[i]; j++)
            if(j < (*colSizes)[i-1])
                arrs[i][j] = arrs[i-1][j-1]+arrs[i-1][j];
    return arrs;
}
