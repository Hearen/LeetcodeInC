/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : Wed, 22 Jun 2016 10:05 CST
Description : Given a collection of distinct numbers, return all possible permutations.
For example,
[1,2,3] have the following permutations:
[
[1,2,3],
[1,3,2],
[2,1,3],
[2,3,1],
[3,1,2],
[3,2,1]
]
Follow-up   : what if there are duplicates?
Source      : https://leetcode.com/problems/permutations/
*******************************************/
class Solution {
public:
    //AC - with or without duplicates;
    vector<vector<int>> permute(vector<int>& nums) 
    {
        sort(nums.begin(), nums.end());
        int size = nums.size(), i, j;
        vector<vector<int>> vv;
        while(true)
        {
            vv.push_back(nums);
            int i = size-2, j = size-1;
            while(i>0 && nums[i]>=nums[i+1]) i--;
            while(j>0 && nums[i]>=nums[j]) j--;
            if(j == 0) break;
            swap(nums[i], nums[j]);
            j = size-1, i++;
            while(i<j)  swap(nums[i++], nums[j--]);     
        }
        return vv;
    }
};
