/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2015-12-26 19:52
Description : Given an array of citations (each citation is a non-negative integer) of a researcher, write a function to compute the researcher's h-index.
According to the definition of h-index on Wikipedia: "A scientist has index h if h of his/her N papers have at least h citations each, and the other N − h papers have no more than h citations each."

For example, given citations = [3, 0, 6, 1, 5], which means the researcher has 5 papers in total and each of them had received 3, 0, 6, 1, 5 citations respectively. Since the researcher has 3 papers with at least 3 citations each and the remaining two with no more than 3 citations each, his h-index is 3.

Note: If there are several possible values for h, the maximum one is taken as the h-index.
Source      : https://leetcode.com/problems/h-index/
*******************************************/
//AC - 88ms - direct method;
int hIndex0(int* s, int size)
{
    int i = size;
    for(; i > 0; i--)
    {
        int count = 0;
        int extra = 0;
        for(int j = 0; j < size; j++)
        {
            if(s[j] > i)
                count++;
            if(s[j] == i)
                extra++;
        }
        if(count <= i && count+extra >= i)
            break;
    }
    return i;
}

//AC - 0ms - after understanding the specific details of H-index;;
int hIndex(int* nums, int size)
{
    int* counters = (int*)malloc(sizeof(int)*(size+1));
    memset(counters, 0, sizeof(int)*(size+1));
    for(int i = 0; i < size; i++)
    {
        if(nums[i] > size) counters[size]++;
        else counters[nums[i]]++;
    }
    int i, t = 0;
    for(i = size; i > -1; --i)
    {
        t += counters[i];
        if(t >= i) break;
    }
    return i;
}
