/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : Wed, 22 Jun 2016 15:41 CST
Description : Given a collection of candidate numbers (C) and a target number (T), find all unique combinations in C where the candidate numbers sums to T.
Each number in C may only be used once in the combination.
Note:
All numbers (including target) will be positive integers.
The solution set must not contain duplicate combinations.
For example, given candidate set [10, 1, 2, 7, 6, 1, 5] and target 8, 
A solution set is: 
[
[1, 7],
[1, 2, 5],
[2, 6],
[1, 1, 6]
]
Source      : https://leetcode.com/problems/combination-sum-ii/
*******************************************/
class Solution {
private:
    int size; //from 20ms to 18ms;
    vector<vector<int>> vv; //from 18ms to 16ms;
    void search(vector<int>& candidates, int pos, int target, vector<int>& v)
    {
        if(target < 0) return;
        if(target == 0)
        {
            vv.push_back(v);
            return ;
        }
        for(int i = pos; i < size; ++i)
        {
            if(i==pos || candidates[i]!=candidates[i-1]) //avoid duplicates;
            {
                v.push_back(candidates[i]);
                search(candidates, i+1, target-candidates[i], v);
                v.pop_back();
            }
        }
    }
public:
    //AC - 16ms;
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) 
    {
        sort(candidates.begin(), candidates.end()); //avoid duplicates;
        size = candidates.size();  
        vector<int> v;
        search(candidates, 0, target, v);
        return vv;
    }
};
