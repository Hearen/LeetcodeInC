/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-02-27 11:03
Description : 
Source      : https://leetcode.com/problems/longest-consecutive-sequence/
*******************************************/
#include <unordered_map.h>
void sort(int* nums, int begin, int end)
{
    int l=begin, r=end;
    int v = nums[l+(r-l)/2];
    while(l <= r)
    {
        while(nums[l] < v) l++;
        while(nums[r] > v) r--;
        if(l <= r)
        {
            int t = nums[l];
            nums[l] = nums[r];
            nums[r] = t;
            l++; r--;
        }
    }
    if(begin < r)
         sort(nums, begin, r);
    if(l < end)
        sort(nums, l, end);
}

//AC - 4ms;
int longestConsecutive0(int* nums, int size)
{
    sort(nums, 0, size-1);
    int max = 1;
    int count = 1;
    for(int i = 1; i < size; i++)
    {
        if(nums[i] == nums[i-1]) continue; //just ignore the equivalent elements;
        if(nums[i] == nums[i-1]+1) count++;
        else  //there is a gap - nonconsecutive;
        {
            max = max > count? max : count;
            count = 1; //reset counter;
        }
    }
    max = max > count? max : count; //collect the last section;
    return max;
}

class Solution
{
    public:
        //AC - 28ms;
        int longestConsecutive0(vector<int>& nums)
        {
            unordered_map<int, int> map;
            int ret = 0;
            for(auto &i: nums)
            {
                if(map[i]) continue;
                if(!map.count(i-1) && !map.count(i+1))
                {
                    ret = max(ret, map[i]=1);
                    continue;
                }
                if(!map.count(i-1)) //only map[i+1];
                {
                    ret = max(ret, map[i]=map[i+map[i+1]]=map[i+1]+1); //set left and right boundary;
                    continue;
                }
                if(!map.count(i+1)) //only map[i-1];
                {
                    ret = max(ret, map[i]=map[i-map[i-1]]=map[i-1]+1);
                    continue;
                }
                ret = max(ret, map[i]=1, map[i-map[i-1]]=map[i+map[i+1]]=1+map[i-1]+map[i+1]);
            }
            return ret;
        }

        //AC - 24ms;
        int longestConsecutive1(vector<int>& nums)
        {
            int ret = 0;
            unordered_map<int, int> map;
            for(int &n: nums)
            {
                if(!map.count(n))
                {
                    int left = map.count(n-1)? map.at(n-1) : 0;
                    int right = map.count(n+1)? map.at(n+1) : 0;
                    int sum = left+right+1;
                    map[n] = sum;
                    if(sum > ret) ret = sum;
                    map[n-left] = map[n+right] = sum;
                }
            }
            return ret;
        }

        //AC - 20ms - quite different solution;
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
