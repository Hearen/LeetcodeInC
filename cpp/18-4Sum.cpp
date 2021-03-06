/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : Mon, 20 Jun 2016 17:09 CST
Description : Given an array S of n integers, are there elements a, b, c, and d in S such that a + b + c + d = target? Find all unique quadruplets in the array which gives the sum of target.
Note: The solution set must not contain duplicate quadruplets.
For example, given array S = [1, 0, -1, 0, -2, 2], and target = 0.
A solution set is:
[
[-1,  0, 0, 1],
[-2, -1, 1, 2],
[-2,  0, 0, 2]
]
Source      : https://leetcode.com/problems/4sum/
*******************************************/
class Solution {
private:
    const int K = 4;
    int size = 0;
    void search(vector<int>& nums, int pos, int k, int target, vector<int>& v, vector<vector<int>>& vv)
    {
        if(k == 2)
        {
            int l = pos, r = size-1;
            while(l < r)
            {
                int t = nums[l]+nums[r];
                if(t > target) r--;
                else if(t < target) l++;
                else 
                {
                    v[K-2] = nums[l++];
                    v[K-1] = nums[r--];
                    vv.push_back(v);
                    while(l<r && nums[l]==nums[l-1]) l++; //avoid duplicates;
                    while(l<r && nums[r]==nums[r+1]) r--; //avoid duplicates;
                }
            }
        }
        else
        {
            for(int top = size-k; pos <= top; ++pos)
            {
                int sum = 0;
                for(int i = 0; i < k; i++) sum += nums[pos+i]; 
                if(sum > target) break; //avoid futile searching;
                sum = nums[pos];
                for(int i = 0; i < k-1; ++i) sum += nums[size-1-i];
                if(sum < target) continue; //avoid futile searching;
                v[K-k] = nums[pos];
                search(nums, pos+1, k-1, target-nums[pos], v, vv);
                while(pos<=top && nums[pos+1]==nums[pos]) pos++; //avoid duplicates;
            }
        }
    }
public:
    //AC - 16ms - handle kSum;
    vector<vector<int>> fourSum(vector<int>& nums, int target) 
    {
        sort(nums.begin(), nums.end());
        size = nums.size();
        vector<vector<int>> vv;
        vector<int> v(K, 0);
        search(nums, 0, K, target, v, vv);
        return vv;
    }

    //AC - 16ms - best submission;
    vector<vector<int>> fourSum(vector<int>& nums, int target) 
    {
        sort(nums.begin(), nums.end());
        vector<vector<int>> vv;
        int size = nums.size();
        for(int i = 0; i < size-3; ++i)
        {
            if(i && nums[i]==nums[i-1]) continue;
            if(nums[i]+nums[i+1]+nums[i+2]+nums[i+3] > target) break;
            if(nums[i]+nums[size-3]+nums[size-2]+nums[size-1] < target) continue;
            for(int j = i+1; j < size-2; ++j)
            {
                if(j>i+1 && nums[j]==nums[j-1]) continue;
                if(nums[i]+nums[j]+nums[j+1]+nums[j+2] > target) break;
                if(nums[i]+nums[j]+nums[size-2]+nums[size-1] < target) continue;
                int l = j+1, r = size-1;
                while(l < r)
                {
                    int t = nums[i]+nums[j]+nums[l]+nums[r];
                    if(t < target) l++;
                    else if(t > target) r--;
                    else
                    {
                        vv.push_back(vector<int>{nums[i], nums[j], nums[l++], nums[r--]});
                        while(l<r && nums[l]==nums[l-1]) l++;
                        while(l<r && nums[r]==nums[r+1]) r--;
                    }
                }
            }
        }
        return vv;
    }
};
