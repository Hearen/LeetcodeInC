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
Reference   : https://leetcode.com/discuss/75756/share-my-greedy-solution
*******************************************/
#include <vector.h>
class Solution {
public:
    #define MIN(a,b) (a<b?a:b)
    #define MAX(a,b) (a>b?a:b)
    // create max number of length t from single non-empty vector
    void getMax(int* num, int& len, int* result, int& t, int& sortedLen)
    {
        int n, top = 0;
        result[0] = num[0];
        const int need2drop = len - t;
        for (int i = 1; i < len; ++i){
            n = num[i];
            while (top >= 0 && result[top] < n && (i - top) <= need2drop) --top; // i - top means already dropped i - top numbers
            if (i - top > need2drop){
                sortedLen = MAX(1,top);
                while (++top < t) result[top] = num[i++];
                return;
            }
            if (++top < t) result[top] = n;
            else top = t - 1;
        }
    }
    // create max number of different length from single vector
    void dp(int *num, int len, int&sortedLen, int& minL, int& maxL, int *res, int &k){
        int  j, *head, *prevhead = res;
        const int soi = sizeof(int);
        getMax(num, len, res, maxL,sortedLen);
        for (int l = maxL; l > MAX(minL,1); --l){
            head = prevhead + k;
            memcpy(head, prevhead, l*soi);
            for (j = sortedLen; j < l; ++j){
                if (head[j] > head[j - 1]){
                    sortedLen = MAX(1, j - 1);
                    memcpy(head + j - 1, prevhead + j, soi*(l - j));
                    break;
                }
            }
            if (j == l) sortedLen = l;
            prevhead = head;
        }
    }
    // merge max number created from single vector
    void merge(int* num1,int len1,int* num2,int len2,int* result,int& resSize){
        int i = 0, j = 0, k = 0;
        while (i < resSize){
            if (j < len1 && k < len2){
                if (num1[j] > num2[k])
                    result[i++] = num1[j++];
                else if (num1[j] < num2[k])
                    result[i++] = num2[k++];
                else{
                    int remaining1 = len1 - j, remaining2 = len2 - k, tmp = num1[j];
                    int flag = memcmp(num1 + j, num2 + k, sizeof(int) * MIN(remaining1, remaining2));
                    flag = (flag == 0 ? (remaining1>remaining2 ? 1 : -1) : flag);
                    int * num = flag > 0 ? num1 : num2;
                    int & cnt = flag > 0 ? j : k;
                    int len = flag > 0 ? len1 : len2;
                    while (num[cnt]==tmp && cnt < len && i<resSize) result[i++] = num[cnt++];
                }
            }
            else if (j < len1) result[i++] = num1[j++];
            else result[i++] = num2[k++];
        }
    }

    //AC - 16ms - the most efficient solution;
    vector<int> maxNumber(vector<int>& nums1, vector<int>& nums2, int k){
        int soi = sizeof(int), len1 = nums1.size(), len2 = nums2.size(), step = k*soi;
        int minL1 = MAX(0, k - len2), maxL1 = MIN(k, len1), minL2 = k - maxL1, maxL2 = k - minL1, range = maxL1 - minL1 + 1;
        int * res = new int[range * k * 2 + 2 * k], *dp1 = res + k, *dp2 = res + range*k+k, *tmp=res+range*2*k+k;
        memset(res, 0, step);
        int sortedLen1 = 1, sortedLen2 = 1;
        if (len1 == 0 && len2 > 0) getMax(&nums2[0], len2, res, k, sortedLen2);
        else if (len1 > 0 && len2 == 0) getMax(&nums1[0], len1, res, k, sortedLen2);
        else if (len1 > 0 && len2 > 0){
            dp(&nums1[0], len1, sortedLen1, minL1, maxL1, dp1,k);
            dp(&nums2[0], len2, sortedLen2, minL2, maxL2, dp2,k);
            if (sortedLen1 + sortedLen2 > k){
                merge(dp1 + k*(maxL1 - sortedLen1), sortedLen1, dp2 + k*(maxL2 - sortedLen2), sortedLen2, tmp, k);
                vector<int> resv(tmp, tmp + k);
                delete[] res;
                return resv;
            }
            for (int i = minL1; i <= maxL1; ++i){
                merge(dp1+k*(maxL1-i), i, dp2+k*(maxL2-k+i), (k-i), tmp,k);
                if (memcmp(res, tmp, step) < 0) memcpy(res, tmp, step);
            }
        }
        vector<int> resv(res, res + k);
        delete[] res;
        return resv;
    }
};

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
        if (j == nums2.size()) return true;
        if (i<nums1.size() && nums1[i]>nums2[j]) return true;
        return false;
    }

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
        vector<int> res(k, 0);
        for (int i = max(0, k-len2); i <= min(k, len1); ++i) 
        {
            auto v1 = maxVector(nums1, i);
            auto v2 = maxVector(nums2, k - i);
            auto tmp = merge(v1, v2, k);
            if (compare(tmp, 0, res, 0)) res = tmp;
        }
        return res;
    }
};
