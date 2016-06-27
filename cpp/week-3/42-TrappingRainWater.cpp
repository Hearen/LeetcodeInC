/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : Mon, 27 Jun 2016 19:29 CST
Description : Given n non-negative integers representing an elevation map where the width of each bar is 1, compute how much water it is able to trap after raining.
For example, 
Given [0,1,0,2,1,0,1,3,2,1,2,1], return 6.
Source      : https://leetcode.com/problems/trapping-rain-water/
*******************************************/
class Solution {
public:
    //direct two traversing method;
	int trap(vector<int>& height) 
    {
        int unit = 0, highest = 0, sum = 0;
        for(int i = 0; i < height.size(); ++i)
        {
            if(highest <= height[i])
            {
                highest = height[i];
                sum += unit;
                unit = 0;
            }
            else
            {
                unit += highest-height[i];
            }
        }
        highest = 0;
        unit = 0;
        for(int i = height.size()-1; i >= 0; --i)
        {
            if(highest < height[i])
            {
                highest = height[i];
                sum += unit;
                unit = 0;
            }
            else
            {
                unit += highest - height[i];
            }
        }
        return sum;
    }

    //just traverse once;
    int trap(vector<int>& height) 
    {
        int l = 0, r = height.size()-1, sum = 0;
        int lMax = 0, rMax = 0;
        while(l <= r)
        {
            if(height[l] <= height[r])
            {
                if(height[l] > lMax) lMax = height[l];
                else sum += lMax-height[l];
                l++;
            }
            else
            {
                if(height[r] > rMax) rMax = height[r];
                else sum += rMax-height[r];
                r--;
            }
        }
        return sum;
    } 

    //just traverse once;
	int trap(vector<int>& height) 
    {
        int l = 0, r = height.size()-1, level = 0, water = 0;
        while (l < r) {
            int lower = height[height[l] < height[r] ? l++ : r--];
            level = max(level, lower);
            water += level - lower;
        }
        return water;
    }
};
