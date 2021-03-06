/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2015-12-26 21:06
Description : Given an array of citations (each citation is a non-negative integer) of a researcher, write a function to compute the researcher's h-index.
According to the definition of h-index on Wikipedia: "A scientist has index h if h of his/her N papers have at least h citations each, and the other N − h papers have no more than h citations each."
For example, given citations = [3, 0, 6, 1, 5], which means the researcher has 5 papers in total and each of them had received 3, 0, 6, 1, 5 citations respectively. Since the researcher has 3 papers with at least 3 citations each and the remaining two with no more than 3 citations each, his h-index is 3.

Note: If there are several possible values for h, the maximum one is taken as the h-index.
Follow up for H-Index: What if the citations array is sorted in ascending order? Could you optimize your algorithm?

Hint:
Expected runtime complexity is in O(log n) and the input is sorted.
Source      : https://leetcode.com/problems/h-index-ii/
*******************************************/
//AC - 4ms;
int hIndex1(int* nums, int size)
{
    int l=0, r=size-1;
    while(l <= r)
    {
        int m = l+(r-l)/2;
        if(size-m < nums[m]) r = m-1;
        else if(size-m > nums[m]) l = m+1;
        else r--; //ensure the loop will terminate properly;
    }
    return size-l;
}

//AC - 4ms;
int hIndex(int* nums, int size)
{
    int l=0, r=size-1;
    while(l <= r)
    {
        int m = l+(r-l)/2;
        if(size-m == nums[m]) return nums[m]; //exactly fit in, just return;
        if(size-m < nums[m]) r = m-1;
        else l = m+1;
    }
    return size-l;
}

