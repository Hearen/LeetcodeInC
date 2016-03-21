/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-02-25 08:42
Description : Given n non-negative integers a1, a2, ..., an, where each represents a point at coordinate (i, ai). n vertical lines are drawn such that the two endpoints of line i is at (i, ai) and (i, 0). Find two lines, which together with x-axis forms a container, such that the container contains the most water.
Note: You may not slant the container.
Source      : https://leetcode.com/problems/container-with-most-water/
*******************************************/
//AC - 12ms;
int maxArea1(int* heights, int size)
{
    int l = 0;
    int r = size-1;
    int max = 0;
    while(l < r)
    {
        int len = r-l;
        int area = 0;
        if(heights[l] < heights[r])
        {
            area = len*heights[l];
            max = max > area? max : area;
            l++;
        }
        else
        {
            area = len*heights[r];
            max = max > area? max : area;
            r--;
        }
    }
    return max;
}

//AC - 8ms;
int maxArea(int* heights, int size)
{
    int l=0, r=size-1;
    int max = 0;
    while(l < r)
    {
        int area = (r-l)*(heights[l] < heights[r]? heights[l++] : heights[r--]);
        max = max > area? max : area;
    }
    return max;
}
