/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2015-12-03 09:02
Description : Given a sorted integer array without duplicates, return the summary of its ranges.
For example, given [0,1,2,4,5,7], return ["0->2","4->5","7"].
Source      : https://leetcode.com/problems/summary-ranges/
*******************************************/
#include <stdlib.h>
#include<string.h>
#include <stdio.h>
char** summaryRanges(int * nums, int size, int* returnSize)
{
    char **sArray = (char**)malloc(sizeof(char*));
    int l=0, h=0; //point to the lowest and highest index of the consecutive range;
    int index = 0; //index the sArray;
    char s[100]; //temporary collector used to store string range;
    for(int i = 1; i < size+1; i++)
    {
        if((i<size && nums[i]-nums[h]!=1) || i==size) //not consecutive, update both l and h;
        {
            if(h == l) sprintf(s, "%d", nums[h]);   
            else sprintf(s, "%d->%d", nums[l], nums[h]);
            l = h = i;
            index++;
            sArray = (char**)realloc(sArray, sizeof(char*)*index);
            sArray[index-1] = (char*)malloc((strlen(s) + 1)* sizeof(char));
            strcpy(sArray[index-1], s); 
        }
        else //move to the next since it's consecutive;
            h = i;
    }
    *returnSize = index;
    return sArray;
}
