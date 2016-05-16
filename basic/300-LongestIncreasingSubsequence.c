/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-02-13 12:01
Description : Given an unsorted array of integers, find the length of longest increasing subsequence.
For example,
Given [10, 9, 2, 5, 3, 7, 101, 18],
The longest increasing subsequence is [2, 3, 7, 101], therefore the length is 4. Note that there may be more than one LIS combination, it is only necessary for you to return the length.
Your algorithm should run in O(n2) complexity.

Follow up: Could you improve it to O(n log n) time complexity?
Source      : https://leetcode.com/problems/longest-increasing-subsequence/
*******************************************/
//AC - 28ms - a DP solution;
int lengthOfLIS0(int* nums, int size)
{
    if(size < 2) return size;
    int *lens = (int*)malloc(sizeof(int)*size); //store the LIS length for each index;
    lens[0] = 1;
    int max = 1;
    for(int i = 1; i < size; i++) //start from index 1 to avoid special case in inner loop;
    {
        int t = 0; //used to store the LIS length before index i which must be smaller than nums[i];
        for(int j = i-1; j >= 0; j--) //check all its previous index to update the current;
            if(nums[i] > nums[j] && lens[j] > t)  
                t = lens[j];
        lens[i] = t+1;
        if(lens[i] > max) //update the max;
            max = lens[i];
    }
    return max;
}

int binarySearch(int* nums, int size, int target)
{
    int l=0, r=size-1;
    while(l < r)
    {
        int m = l+(r-l)/2;
        if(nums[m] > target) r = m-1;
        else if(nums[m] < target) l = m+1;
        else break;
    }
    if(nums[l] < target) return l+1; //ensure the index is pointed to the position whose element is equal to or bigger than the target;
    else return l;
}

//AC - 0ms - using stack to collect the LIS;
int lengthOfLIS(int* nums, int size)
{
    int top = -1;
    int *arr = (int*)malloc(sizeof(int)*size);
    for(int i = 0; i < size; i++)
    {
        int pos = binarySearch(arr, top+1, nums[i]);
        if(pos > top) arr[++top] = nums[i]; //a new element should be appended;;
        else arr[pos] = nums[i]; //make the element pos pointing to smaller;
    }
    return top+1;
}
