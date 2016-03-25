/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-02-12 10:12
Description : Given a triangle, find the minimum path sum from top to bottom. Each step you may move to adjacent numbers on the row below.
For example, given the following triangle
[
[2],
[3,4],
[6,5,7],
[4,1,8,3]
]
The minimum path sum from top to bottom is 11 (i.e., 2 + 3 + 5 + 1 = 11).
Note:
Bonus point if you are able to do this using only O(n) extra space, where n is the total number of rows in the triangle.
Source      : https://leetcode.com/problems/triangle/
*******************************************/
//AC - 8ms - O(n^2);
int minimumTotal0(int** triangle, int rSize, int *cSize)
{
    int len = sizeof(int)*cSize[rSize-1];
    int *mins0 = (int*)malloc(len);
    int *mins1 = (int*)malloc(len);
    mins0[0] = triangle[0][0];
    for(int r = 1; r < rSize; r++)
    {
        for(int c = 0; c < cSize[r]; c++)
        {
            if(c == 0)
            {
                mins1[c] = mins0[c]+triangle[r][c];
                continue;
            }
            if(c == cSize[r]-1)
            {
                mins1[c] = mins0[c-1]+triangle[r][c];
                continue;
            }
            int t = triangle[r][c] + mins0[c];
            if(mins0[c] > mins0[c-1])
                t = triangle[r][c] + mins0[c-1];
            mins1[c] = t;
        }
        int *t = mins0;
        mins0 = mins1;
        mins1 = t;
    }
    int t = mins0[0];
    for(int i = 0; i < cSize[rSize-1]; i++)
        if(t > mins0[i])
            t = mins0[i];
    return t;
}

//AC - 8ms - O(2n);
int minimumTotal1(int** triangle, int rSize, int *cSize)
{
    int len = sizeof(int)*cSize[rSize-1];
    int *mins0 = (int*)malloc(len);
    int *mins1 = (int*)malloc(len);
    mins0[0] = triangle[0][0];
    for(int r = 1; r < rSize; r++)
    {
        for(int c = 0; c < cSize[r]; c++)
        {
            if(c == cSize[r]-1)
                mins0[c] = mins0[c-1];
            int t = triangle[r][c] + mins0[c];
            if(c > 0 && mins0[c] > mins0[c-1])
                t = triangle[r][c] + mins0[c-1];
            mins1[c] = t;
        }
        int *t = mins0;
        mins0 = mins1;
        mins1 = t;
    }
    int t = mins0[0];
    for(int i = 0; i < cSize[rSize-1]; i++)
        if(t > mins0[i])
            t = mins0[i];
    return t;
}

//AC - 8ms - O(n);
int minimumTotal2(int** triangle, int rSize, int *cSize)
{
    int len = sizeof(int)*cSize[rSize-1];
    int *mins = (int*)malloc(sizeof(int)*len);
    mins[0] = triangle[0][0];
    for(int r = 1; r < rSize; r++)
    {
        for(int c = cSize[r]-1; c > -1; c--)
        {
            if(c == 0) mins[c] += triangle[r][c];
            else
            {
                if(c == cSize[r]-1) mins[c] = triangle[r][c]+mins[c-1];
                else mins[c] = triangle[r][c]+(mins[c]>mins[c-1]? mins[c-1]:mins[c]);
            }
        }
    }
    int t = mins[0];
    for(int i = 0; i < cSize[rSize-1]; i++)
        if(t > mins[i])
            t = mins[i];
    return t;
}

//AC - 8ms - O(1);
int minimumTotal(int** triangle, int rSize, int *cSize)
{
    for(int r = rSize-1; r > -1; r--)
        for(int c = 0; c < cSize[r]-1; c++)
            triangle[r-1][c] += triangle[r][c]>triangle[r][c+1]? triangle[r][c+1]:triangle[r][c];
    return triangle[0][0];
}
