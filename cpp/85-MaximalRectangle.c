/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2015-12-19 11:19
Description : Given a 2D binary matrix filled with 0's and 1's, find the largest rectangle containing all ones and return its area.
Source      : https://leetcode.com/problems/maximal-rectangle/
*******************************************/
class Solution {
private:
    int getLargest(int* heights, int* stack, int size)
    {
        int current = 0, max = 0, top = 0; 
        stack[top] = -1; //ensure the width of the area is okay, hitting the bottom of stack;
        for(int i = 0; i < size; ++i)
        {
            while(top>0 && heights[stack[top]]>heights[i]) //keep the stack in ascending order;
            {
                current = (i-stack[top-1]-1) * heights[stack[top]]; //get the area started with the height indexes by stack[top];
                top--;
                if(current > max) max = current;
            }
            stack[++top] = i;
        }
        return max;
    }
public:
    int maximalRectangle(vector<vector<char>>& matrix) 
    {
        int rowSize = matrix.size();
        if(rowSize == 0) return 0;
        int colSize = matrix[0].size();
        int heights[colSize+1] = {0}; //spare another column for sentinel so when we finish checking heights, it can automatically collect the leftover in stack;
        int stack[colSize+1] = {0}; //stay ascending order to avoid redundant calculation;
        int largest = 0;
        for(int r = 0; r < rowSize; ++r)
        {
            for(int c = 0; c < colSize; ++c) matrix[r][c]=='1'? heights[c]++ : heights[c]=0;
            largest = max(largest, getLargest(heights, stack, colSize+1));
        }
        return largest;
    }
};
