/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2015-12-20 21:15
Description : Given n non-negative integers representing the histogram's bar height where the width of each bar is 1, find the area of largest rectangle in the histogram.
Above is a histogram where width of each bar is 1, given height = [2,1,5,6,2,3].

The largest rectangle is shown in the shaded area, which has area = 10 unit.

For example,
Given heights = [2,1,5,6,2,3],
return 10.
Source      : https://leetcode.com/problems/largest-rectangle-in-histogram/
*******************************************/
//AC - 8ms
//only calculate the stack - ascending order
//the width will be calculated by the stored indexes;
int largestRectangleArea(int* heights, int heightSize)
{
    heightSize++;
    int* tmp = (int*)malloc(sizeof(int) * heightSize);
    int i = 0;
    for(; i < heightSize - 1; i++)
        tmp[i] = heights[i];
    tmp[heightSize-1] = 0;
    heights = tmp;
    int current = 0, max = 0;
    int* stack = (int)malloc(sizeof(int) * heightSize);
    int top = 0;
    stack[top] = -1;
    for(i = 0; i < heightSize; i++)
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
    return max;
}
