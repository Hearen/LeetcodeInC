/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : Fri, 24 Jun 2016 11:30 CST
Description : Given an integer array of size n, find all elements that appear more than ⌊ n/3 ⌋ times. The algorithm should run in linear time and in O(1) space.
Source      : https://leetcode.com/problems/majority-element-ii/
*******************************************/
class Solution {
public:
    //Boyer-Moor Majority Vote Algorithm;
    vector<int> majorityElement(vector<int>& nums) 
    {
        vector<int> v;
        if(nums.size() == 0) return v;
        int a = nums[0]-1, b = nums[0]-1;
        int aCount = 0, bCount = 0;
        for(int i = 0; i < nums.size(); ++i)
        {
            if((aCount==0 || a==nums[i]) && b!=nums[i]) //avoid duplicates in candidates;
            aCount++, a=nums[i];
            else if(bCount==0 || b==nums[i])
            bCount++, b=nums[i];
            else aCount--, bCount--;
        }
        aCount = bCount = 0;
        for(auto n: nums) 
        if(a == n) aCount++;
        else if(b == n) bCount++;
        if(aCount > nums.size()/3) v.push_back(a);
        if(bCount > nums.size()/3) v.push_back(b);
        return v;
    }

    vector<int> majorityElement(vector<int>& nums) 
    {
        int k = K-1, j = 0;
        vector<int> v;
        int size = nums.size();
        if(size == 0) return v;
        int candidates[k]{0}, counters[k]{0};
        //ensure there is no duplicate in candidates;
        candidates[0] = 1;
        for(int i = 0; i < nums.size(); ++i)
        {
            for(j = 0; j < k; ++j)
            {
                if(candidates[j]==nums[i])
                {
                    counters[j]++;
                    break;
                }
            }
            if(j < k) continue;
            for(j = 0; j < k; ++j)
            {
                if(counters[j] == 0)
                {
                    candidates[j] = nums[i];
                    counters[j]++;
                    break;
                }
            }
            if(j < k) continue;
            for(j = 0; j < k; ++j)
                counters[j]--;
        }
        for(int i = 0; i < k; ++i) counters[i] = 0;
        for(int i = 0; i < nums.size(); ++i) 
        {
            for(int j = 0; j < k; ++j)
            {
                if(candidates[j] == nums[i])
                counters[j]++;
            }
        }
        for(int j = 0; j < k; ++j)
        {
            if(counters[j] > nums.size()/K)
                v.push_back(candidates[j]);
        }
        return v;
    }
};
