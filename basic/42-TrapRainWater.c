/*******************************************
Author: LHearen
E-mail: LHearen@126.com
Time  :	2015-12-02 21:28
Description: 
Source: https://leetcode.com/problems/trapping-rain-water/
*******************************************/
#include<stdio.h>
//regular tests: [0,5,6,4,6,1,0,0,2,7]
//[2,0,2], [0,2,0], [4,2,1,4,3,2,4]
//60ms - traverse to the end - from the left and right
//at the same time until tops meet in the middle;

//4ms - travesing from left to right and then
//reverse the direcition to collect the water;
//simple and direct but efficient;
int trap(int *hArray, int size)
{
    int unitSum = 0;
    int sum = 0;
    int top = 0;
    for(int i = 0; i < size; i++)
    {
        //in case of re-calculating in the next section;
        if(top < hArray[i]) //collect only the higher bar;
        {
            sum += unitSum;
            unitSum = 0;
            top = hArray[i];
        }
        else
            unitSum += top - hArray[i];
    }
    top=0, unitSum=0; //reset;
    for(int j = size - 1; j > -1; j--)
    {
        if(top <= hArray[j]) //collect both the equal and higher bar;
        {
            sum += unitSum;
            unitSum = 0;
            top = hArray[j];
        }
        else
            unitSum += top - hArray[j];
    }
    return sum;
}
