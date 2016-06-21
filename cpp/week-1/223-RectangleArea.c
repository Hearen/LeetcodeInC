/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : Wed, 15 Jun 2016 09:13 CST
Description : Find the total area covered by two rectilinear rectangles in a 2D plane.
Each rectangle is defined by its bottom left corner and top right corner as shown in the figure.
Rectangle Area
Assume that the total area is never beyond the maximum possible value of int.
Source      : https://leetcode.com/problems/rectangle-area/
*******************************************/
class Solution 
{
public:
    int computeArea(int A, int B, int C, int D, int E, int F, int G, int H) 
    {
        int lMax = max(A, E), rMin = min(C, G);
        int bMax = max(B, F), tMin = min(D, H);
        return (C-A)*(D-B)+(G-E)*(H-F)-((rMin>lMax && tMin>bMax)? (rMin-lMax)*(tMin-bMax) : 0);
    }  //no overlapping area should be taken into account;
};
