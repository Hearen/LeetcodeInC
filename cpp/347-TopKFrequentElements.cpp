/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : Sun, 19 Jun 2016 11:13 CST
Description : Given a non-empty array of integers, return the k most frequent elements.
For example,
Given [1,1,1,2,2,3] and k = 2, return [1,2].
Note: 
You may assume k is always valid, 1 ≤ k ≤ number of unique elements.
Your algorithm's time complexity must be better than O(n log n), where n is the array's size.
Source      : https://leetcode.com/problems/top-k-frequent-elements/
*******************************************/
class Solution {
public:
    //AC - 36ms - best submission - using cumulative counting trick;
    vector<int> topKFrequent(vector<int>& nums, int k) 
    {
        int size = nums.size();
        unordered_map<int, int> counters;
        vector<int> cumulativeCounter(size+1, 0);
        for(int i = 0; i < size; ++i) ++cumulativeCounter[++counters[nums[i]]];
        int splittingCount = size;
        while(splittingCount>0 && cumulativeCounter[splittingCount]<k) splittingCount--;
        vector<int> v;
        for(auto& pair: counters)
        if(pair.second>splittingCount && v.size()<k) v.push_back(pair.first);
        for(auto& pair: counters)
        if(pair.second==splittingCount && v.size()<k) v.push_back(pair.first);
        return v;
    }

    //AC - 40ms - bucket collecting method;
    vector<int> topKFrequent(vector<int>& nums, int k) 
    {
        int size = nums.size();
        unordered_map<int, int> counters;
        vector<int> v;
        vector<vector<int>> buckets(size+1);
        for(int i = 0; i < size; ++i) counters[nums[i]]++;
        for(auto& pair: counters) buckets[pair.second].push_back(pair.first);
        for(int i = size; i >= 0; --i)
        {
            for(int j = 0; j < buckets[i].size(); ++j)
            {
                v.push_back(buckets[i][j]);
                if(v.size() == k) return v;
            }
        }
        return v;
    }

    //AC - 40ms - using priority_queue;
    vector<int> topKFrequent(vector<int>& nums, int k) 
    {
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> minHeap;
        vector<int> v;
        unordered_map<int, int> counters;
        for(int i = 0; i < nums.size(); ++i) counters[nums[i]]++;
        for(auto& pair: counters) 
        {
            minHeap.push({pair.second, pair.first});
            if(minHeap.size() > k) minHeap.pop();
        }
        while(!minHeap.empty())
        {
            v.push_back(minHeap.top().second);
            minHeap.pop();
        }
        return v;
    }
};
