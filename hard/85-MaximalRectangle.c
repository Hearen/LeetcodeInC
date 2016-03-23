/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2015-12-19 11:19
Description : Given a 2D binary matrix filled with 0's and 1's, find the largest rectangle containing all ones and return its area.
Source      : https://leetcode.com/problems/maximal-rectangle/
*******************************************/
//AC - 4ms
int fixedMaximalRectangle(int* heights, int* stack, int size)
{
    int current = 0, max = 0; 
    int i = 0, j = 0;
    int top = 0;
    stack[top] = -1;
    for(; i < size; i++)
    {
        while(top > 0 && heights[stack[top]] > heights[i])
        {
            current = (i - stack[top - 1] - 1) * heights[stack[top]];
            top--;
            if(current > max)
                max = current;
        }
        stack[++top] = i;
    }
    return current > max? current : max;
}
int maximalRectangle(char** matrix, int rowSize, int colSize)
{
    colSize++;
    int* heights = (int*)malloc(sizeof(int) * colSize);
    int* stack = (int*)malloc(sizeof(int) * colSize);
    int i = 0, j = 0;
    int max = 0, current = 0; 
    for(j = 0; j < colSize; j++) 
    {
        heights[j] = 0;
        stack[j] = 0;
    }
    for(i = 0; i < rowSize; i++)
    {
        for(j = 0; j < colSize - 1; j++)
        {
            matrix[i][j] == '0' ? heights[j] = 0 : heights[j]++;
        }
        current = fixedMaximalRectangle(heights, stack, colSize);
        if(current > max)
           max = current; 
    }
    return max;
}
