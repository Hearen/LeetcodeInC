/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-03-07 08:24
Description : Find the kth largest element in an unsorted array. Note that it is the kth largest element in the sorted order, not the kth distinct element.
For example,
Given [3,2,1,5,6,4] and k = 2, return 5.
Note: 
You may assume k is always valid, 1 ≤ k ≤ array's length.
Source      : https://leetcode.com/problems/kth-largest-element-in-an-array/
*******************************************/
#include <stdbool.h>
#include <stdio.h>
void swap(int* p, int* q)
{
    int t=*p; *p=*q; *q=t;
}

int partition(int* nums, int begin, int end)
{
    int l=begin, r=end;
    int m = (l+r)/2;
    int mid = nums[m];
    swap(nums+m, nums+l);
    l++;
    while(l <= r)
    {
        while(nums[r] > mid) r--;
        while(l<=r && nums[l]<mid) l++;
        if(l <= r)
        {
            swap(nums+l, nums+r);
            l++; r--;
        }
    }
    swap(nums+begin, nums+r);
    return r;
}

//AC - 4ms;
int findKthLargest0(int* nums, int size, int k)
{
    k = size-k;
    int begin = 0; 
    int end = size-1;
    while(true)
    {
        int position = partition(nums, begin, end);
        if(position == k) return nums[k];
        if(position > k) end = position-1;
        else begin = position+1;
    }
}

void sort(int* nums, int begin, int end)
{
    int l=begin, r=end;
    int v=nums[(l+r)/2];
    while(l <= r)
    {
        while(nums[l] < v) l++;
        while(nums[r] > v) r--;
        if(l <= r)
        {
            swap(nums+l, nums+r);
            l++; r--;
        }
    }
    if(begin < r)
        sort(nums, begin, r);
    if(l < end)
        sort(nums, l, end);
}

//AC - 8ms;
int findKthLargest1(int* nums, int size, int k)
{
    sort(nums, 0, size-1);
    return nums[size-k];
}

//AC - 120ms;
int findKthLargest2(int* nums, int size, int k)
{
    for(int i = 0; i < k; i++)
    {
        int max = i;
        for(int j = i+1; j < size; j++)
            if(nums[j] > nums[max]) max = j;
        swap(nums+i, nums+max);
    }
    return nums[k-1];
}

void fixDown(int* a, int size, int k)
{
    int j;
    while(2*k < size)
    {
        j = 2*k;
        if(j < size-1 && a[j] < a[j+1]) j++;//select the bigger one;
        if(a[k] >= a[j]) break;
        swap(a+k, a+j), k = j;
    }
}
void heapSort(int *a, int l, int r)
{
    int size = r-l+1;
    for(int k=size/2; k >= 0; k--)
    fixDown(a+l, size, k);
    while(size > 1)
    {
        swap(a+l, a+l+size-1);
        fixDown(a+l, --size, 0);
    }
}

//AC - 12ms;
int findKthLargest(int *nums, int size, int k)
{
    heapSort(nums, 0, size-1);
    return nums[size-k];
}
