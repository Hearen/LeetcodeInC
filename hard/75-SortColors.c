/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-01-04 08:01
Description : Given an array with n objects colored red, white or blue, sort them so that objects of the same color are adjacent, with the colors in the order red, white and blue.
Here, we will use the integers 0, 1, and 2 to represent the color red, white, and blue respectively.

Note:
You are not suppose to use the library's sort function for this problem.
Follow up:
A rather straight forward solution is a two-pass algorithm using counting sort.
First, iterate the array counting number of 0's, 1's, and 2's, then overwrite array with total number of 0's, then 1's and followed by 2's.

Could you come up with an one-pass algorithm using only constant space?
Source      : https://leetcode.com/problems/sort-colors/
*******************************************/
void swap(int* p, int* q)
{
    int t=*p; *p=*q; *q=t;
}

//AC - 0ms - one pass;
void sortColors0(int* nums, int size)
{
    if(size < 2) return;
    int index0=0, index2=size-1;
    int i = 0;
    while(i <= index2)
    {
        if(nums[i] == 0)
            swap(nums+index0++, nums+i++);
        else if(nums[i] == 2)
            swap(nums+index2--, nums+i);
        else i++;
    }
}

//AC - 0ms - two passes;
void sortColors1(int* nums, int size)
{
    if(size < 2) return ;
    int index0=0, index1=size-1;
    while(index0 != index1) //sort color ZERO;
    {
        while(nums[index0]==0 && index0<index1) index0++;
        while(nums[index1]!=0 && index0<index1) index1--;
        if(index0 != index1) swap(nums+index0, nums+index1);
    }
    index1 = size-1;
    while(index0 != index1) //sort color ONE;
    {
        while(nums[index0]==1 && index0<index1) index0++;
        while(nums[index1]!=1 && index0<index1) index1--;
        if(index0 != index1) swap(nums+index0, nums+index1);
    }
}

//AC - 0ms - one pass;
void sortColors2(int* nums, int size)
{
    int index0=0, index1=0, index2=0;
    for(int i = 0; i < size; i++)
        switch(nums[i])
        {
            case 0: nums[index2++]=2; nums[index1++]=1; nums[index0++]=0; break;
            case 1: nums[index2++]=2; nums[index1++]=1;  break;
            case 2: nums[index2++] = 2; break;
            default: break;
        }
}

void sortColors(int* nums, int size)
{
    int index0=0, index1=size-1;
    for(int i = 0; i < index1; i++)
    {
        if(nums[i] == 0) swap(nums+i, nums+index0++);
        if(nums[i] == 2) swap(nums+i--, nums+index1--);
    }
}

void sortKColors(int* nums, int size, int k)
{
    if(size < 2) return ;
    int color0=1, color1=k;
    int index0=0, index1=size-1;
    while(color0 < color1)
    {
        int i = index0;
        while(i <= index1)
        {
            if(nums[i] == color0)
                swap(nums+index0++, nums+i++);
            else if(nums[i] == color1)
                swap(nums+index1--, nums+i);
            else i++;
        }
        color0++, color1--;
    }
}
