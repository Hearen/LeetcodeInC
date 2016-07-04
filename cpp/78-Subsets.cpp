/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-01-05 21:02
Description : Given a set of distinct integers, nums, return all possible subsets.
Note: The solution set must not contain duplicate subsets.
For example,
If nums = [1,2,3], a solution is:
[
[3],
[1],
[2],
[1,2,3],
[1,3],
[2,3],
[1,2],
[]
]
Source      : https://leetcode.com/problems/subsets/
*******************************************/
#include <vector>
using namespace std;
class Solution {
public:
    //AC - 8ms - bit manipulation - translated into another problem;
    vector<vector<int>> subsets(vector<int>& nums) 
    {
        int size = nums.size();
        int set_size = 1 << size;
        vector<vector<int>> sets(set_size, vector<int>());
        for(int i = 0; i < size; i++)
            for(int j = 0; j < set_size; j++)
                if((j>>i) & 1)
                    sets[j].push_back(nums[i]);
        return sets;
    }

    //AC - 8ms - iterative solution;
    vector<vector<int>> subsets(vector<int>& nums)
    {
        int size = nums.size();
        vector<vector<int>> sets(1, vector<int>());
        for(int i = 0; i < size; i++)
        {
            int n = sets.size();
            for(int j = 0; j < n; j++)
            {
                sets.push_back(sets[j]); //automaticaly copy the vector object;
                sets.back().push_back(nums[i]);
            }
        }
        return sets;
    }

    //AC - 8ms - recursive way;
    vector<vector<int>> subset(vector<int>& nums)
    {
        int size = nums.size();
        vector<vector<int>> sets(1, vector<int>());
        if(!size) return sets;
        int n = nums.back();
        nums.pop_back();
        sets = subsets(nums);
        vector<vector<int>> sets0(sets.begin(), sets.end());
        for(auto& set: sets)
        {
            set.push_back(n);
            sets0.push_back(set);
        }
        return sets0;
    }

    //AC - 4ms - eliminating lots of redundant checking;
    vector<vector<int>> subsets(vector<int>& nums)
    {
        vector<vector<int>> sets;
        vector<int> set;
        genSubsets(nums, 0, sets, set);
        return sets;
    }

    void genSubsets(const vector<int>& nums, int pos, vector<vector<int>>& sets, vector<int>& set)
    {
        sets.push_back(set);
        for(int i = pos; i < nums.size(); i++)
        {
            set.push_back(nums[i]);
            genSubsets(nums, i+1, sets, set);
            set.pop_back();
        }
    }
};
