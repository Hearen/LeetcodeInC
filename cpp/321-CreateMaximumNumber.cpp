/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-04-29 09:23
Description : Given two arrays of length m and n with digits 0-9 representing two numbers. Create the maximum number of length k <= m + n from digits of the two. The relative order of the digits from the same array must be preserved. Return an array of the k digits. You should try to optimize your time and space complexity.
Example 1:
nums1 = [3, 4, 6, 5]
nums2 = [9, 1, 2, 5, 8, 3]
k = 5
return [9, 8, 6, 5, 3]
Example 2:
nums1 = [6, 7]
nums2 = [6, 0, 4]
k = 5
return [6, 7, 6, 0, 4]
Example 3:
nums1 = [3, 9]
nums2 = [8, 9]
k = 3
return [9, 8, 9]
Source      : https://leetcode.com/problems/create-maximum-number/
*******************************************/
class Solution 
{
public:
    //select the maximal number in certain length within one vector;
    vector<int> maxVector(vector<int> nums, int k) 
    {
        while (nums.size() > k) 
        {
            int i = 0, n = nums.size();
            for (; i < n - 1; ++i)  //at least erase one element each time;
            {
                if (nums[i] < nums[i + 1]) 
                {
                    nums.erase(nums.begin() + i);
                    break;
                }
            }
            if (i == n - 1) nums.erase(nums.begin() + i);
        }
        return nums;
    }

    //compare two vectors from certain index adopting lexical order;
    //if the first vector is bigger return true otherwise return false;
    bool compare(vector<int> &nums1, int i, vector<int> &nums2, int j) 
    {
        while (i<nums1.size() && j<nums2.size() && nums1[i]==nums2[j]) ++i, ++j;
        if (i<nums1.size() && j<nums2.size()) return nums1[i]>nums2[j];
        else if(j == nums2.size()) return true;
        else return false;
    }

    //get the first k numbers which form the largest lexical sequence;
    vector<int> merge(vector<int> &nums1, vector<int> &nums2, int k) 
    {
        vector<int> res(k, 0);
        for (int i=0, j=0, r=0; r < k; ++r) 
            res[r] = compare(nums1, i, nums2, j) ? nums1[i++] : nums2[j++];
        return res;
    }

    //AC - 386ms - the most intuitive solution;
    vector<int> maxNumber(vector<int>& nums1, vector<int>& nums2, int k) 
    {
        int len1=nums1.size(), len2=nums2.size();
        vector<int> v(k, 0);
        for (int l1 = max(0, k-len2); l1 <= min(k, len1); ++l1) 
        {
            auto v1 = maxVector(nums1, l1);
            auto v2 = maxVector(nums2, k-l1);
            auto tmp = merge(v1, v2, k);
            if (compare(tmp, 0, v, 0)) v = tmp;
        }
        return v;
    }
};
