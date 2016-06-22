/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-01-02 20:29
Description : Given a collection of integers that might contain duplicates, nums, return all possible subsets.
Note:
Elements in a subset must be in non-descending order.
The solution set must not contain duplicate subsets.
For example,
If nums = [1,2,2], a solution is:

[
[2],
[1],
[1,2,2],
[2,2],
[1,2],
[]
]
Source      : https://leetcode.com/problems/subsets-ii/
*******************************************/
class Solution {
private:
    int size;
    void search(vector<int>& nums, int pos, vector<int>& v, vector<vector<int>>& vv)
    {
        vv.push_back(v);
        for(int i = pos; i < size; ++i)
        {
            if(i==pos || nums[i]!=nums[i-1])
            {
                v.push_back(nums[i]);
                search(nums, i+1, v, vv);
                v.pop_back();
            }
        }
    }
public:
    //AC - recursive method;
    vector<vector<int>> subsetsWithDup(vector<int>& nums) 
    {
        size = nums.size();
        sort(nums.begin(), nums.end());
        vector<vector<int>> vv;
        vector<int> v;
        search(nums, 0, v, vv);
        return vv;
    }

    //AC - iterative method;
    vector<vector<int>> subsetsWithDup(vector<int>& nums) 
    {
        sort(nums.begin(), nums.end());
        vector<vector<int>> vv;
        vector<vector<int>> vv0;
        vv.push_back(vector<int>());
        for(int i = 0; i < nums.size(); ++i)
        {
            //duplicates here have many choices, not appear, appear once, twice ...;
            if(i==0 || nums[i]!=nums[i - 1]) vv0 = vv; 
            for(auto& set : vv0) set.push_back(nums[i]);
            vv.insert(vv.end(), vv0.begin(), vv0.end());
        }
        return vv;
    }
};
