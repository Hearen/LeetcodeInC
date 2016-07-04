/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : Wed, 29 Jun 2016 11:27 CST
Description : Given an unsorted array of integers, find the length of longest increasing subsequence.
For example,
Given [10, 9, 2, 5, 3, 7, 101, 18],
The longest increasing subsequence is [2, 3, 7, 101], therefore the length is 4. Note that there may be more than one LIS combination, it is only necessary for you to return the length.
Your algorithm should run in O(n2) complexity.
Follow up: Could you improve it to O(n log n) time complexity?
Source      : https://leetcode.com/problems/longest-increasing-subsequence/
*******************************************/
class Solution {
private:
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
        return nums[l]<target? l+1 : l;//ensure the index is pointed to the position whose element is equal to or bigger than the target;
    }
    
    
public:
    //AC - 4ms - using stack to collect the LIS;
    int lengthOfLIS(vector<int>& nums)
    {
        int size = nums.size();
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

    //AC - 4ms - C++ way;
	int lengthOfLIS(vector<int>& nums) 
    {
        vector<int> collector;
        for(int i = 0; i < nums.size(); ++i)
        {
            auto iter = std::lower_bound(collector.begin(), collector.end(), nums[i]);
            if(iter == collector.end()) collector.push_back(nums[i]);
            else *iter = nums[i];
        }
        return collector.size();
    }

    //AC - 120ms - DP solution;
	int lengthOfLIS(vector<int>& nums) 
    {
        int size = nums.size();
        if(!size) return 0;
        int subLens[size];
        subLens[0] = 1;
        int maxLen = 1;
        for(int i = 1; i < size; ++i)
        {
            subLens[i] = 1;
            for(int j = i-1; j >= 0; --j)
            {
                if(nums[i] > nums[j]) subLens[i] = max(subLens[i], subLens[j]+1);
                maxLen = max(maxLen, subLens[i]);
            }
        }
        return maxLen;
    }
};
