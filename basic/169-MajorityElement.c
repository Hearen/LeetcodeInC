/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-01-15 08:24
Description : Given an array of size n, find the majority element. The majority element is the element that appears more than ⌊ n/2 ⌋ times.
You may assume that the array is non-empty and the majority element always exist in the array.
Source      : https://leetcode.com/problems/majority-element/ 
*******************************************/
void swap(int* p, int* q)
{
    int t = *p;
    *p = *q;
    *q = t;
}

void swiftSort(int* nums, int low, int high)
{
    int l = low, h = high;
    int v = nums[l+(h-l)/2];
    while(l <= h)
    {
        while(nums[l] < v) l++;
        while(nums[h] > v) h--;
        if(l <= h)
        {
            swap(nums+l, nums+h);
            l++, h--;
        }
    }
    if(h > low)
        swiftSort(nums, low, h);
    if(l < high)
        swiftSort(nums, l, high);
}
//AC - 16ms;
int majorityElement0(int* nums, int size)
{
    swiftSort(nums, 0, size-1);
    return nums[size/2];
}

//AC - 16ms - bit manipulation;
int majorityElement1(int* nums, int size)
{
    int majority=0;
    for(int i = 0, mask=1; i < 32; i++, mask<<=1)
    {
        int bitCount = 0;
        for(int j = 0; j < size; j++)
            if(nums[j] & mask) bitCount++;
        if(bitCount > size/2)
            majority |= mask;
    }
    return majority;
}

//AC - 8ms;
//Boyer-Moore majority vote algorithm;
int majorityElement(int* nums, int size)
{
    int majority = nums[0], count = 1;
    for(int i = 1; i < size; i++)
    {
        if(count == 0) majority = nums[i];
        if(majority == nums[i]) count++;
        else count--;
    }
    return majority;
}

