/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-02-13 10:58
Description : Given a 2D binary matrix filled with 0's and 1's, find the largest square containing all 1's and return its area.
For example, given the following matrix:
1 0 1 0 0
1 0 1 1 1
1 1 1 1 1
1 0 0 1 0
Return 4.
Source      : https://leetcode.com/problems/maximal-square/
*******************************************/
//AC - 4ms;
int maximalSquare(char** matrix, int rSize, int cSize)
{
    int max = 0;
    int *maxes = (int*)malloc(sizeof(int)*cSize);
    memeset(maxes, 0, sizeof(int)*cSize);
    for(int i = 0; i < cSize; i++)
        if(matrix[0][i] == '1') maxes[i] = 1;
    for(int r = 1; r < rSize; r++)
    {
        maxes[0] = matrix[r][0]-'0';
        int pre = matrix[r-1][0]-'0';
        for(int c = 1; c < cSize; c++)
        {
            if(matrix[r][c] == '1')
            {
                int min = pre;
                if(maxes[c-1] < min) min = maxes[c-1];
                if(maxes[c] < min) min = maxes[c];
                pre = maxes[c];
                maxes[c] = min+1;
                if(maxes[c] > max) max = maxes[c];
            }
            else
                maxes[c]=0;
        }
    }
    return max*max;
}
