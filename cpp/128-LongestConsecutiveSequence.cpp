/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-02-27 11:03
Description : 
Source      : https://leetcode.com/problems/longest-consecutive-sequence/
*******************************************/
class Solution
{
    public:
        //AC - 24ms - bottom-up method;
        int longestConsecutive(vector<int>& nums) 
        {
            int maxCount = 0, lCount = 0, rCount = 0;
            unordered_map<int, int> count_map;
            for(int i = 0; i < nums.size(); ++i)
            {
                if(!count_map[nums[i]])
                {
                    int lCount = count_map[nums[i]-1];
                    int rCount = count_map[nums[i]+1];
                    int sum = lCount+rCount+1;
                    count_map[nums[i]] = count_map[nums[i]-lCount] = count_map[nums[i]+rCount] = sum;
                    maxCount = max(maxCount, sum);
                }
            }
            return maxCount;
        }

        //AC - 20ms - blood spreading into two directions;
        int longestConsecutive(vector<int>& nums)
        {
            unordered_set<int> set(nums.begin(), nums.end());
            int ret = 1;
            for(auto &n: nums)
            {
                if(!set.count(n)) continue;
                set.erase(n);
                int pre=n-1, next=n+1;
                while(set.count(pre)) set.erase(pre--);
                while(set.count(next)) set.erase(next++);
                ret = max(ret, next-pre-1);
            }
            return ret;
        }
};
