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
    // create max number of length t from single non-empty vector
    // @nums is the array of length @len 
    // @result will be used to store the max number of length @t 
    // @sortedLen indicates the prefix length which is in descending order;
    void getMax(int* nums, int& len, int* result, int& t, int& sortedLen)
    {
        int n, top = 0;
        result[0] = nums[0];
        const int need2drop = len - t;
        for (int i = 1; i < len; ++i){
            n = nums[i];
            while (top >= 0 && result[top] < n && (i - top) <= need2drop) --top; // i - top means already dropped i - top numsbers
            if (i - top > need2drop){
                sortedLen = max(1,top);
                while (++top < t) result[top] = nums[i++];
                return;
            }
            if (++top < t) result[top] = n;
            else top = t - 1;
        }
    }
    // create max number of different length from single vector
    // @nums is the original array of length @len
    // @sortedLen is the longest length of the descending prefix of the max number;
    // @minL and @maxL is the min and max length of the result max number
    // @res is a pointer which will record the max numbers of length ranging from minL to maxL
    // @k is the length of the final max number;
    void dp(int *nums, int len, int&sortedLen, int& minL, int& maxL, int *res, int &k)
    {
        int  j, *head, *preHead = res;
        const int soi = sizeof(int);
        getMax(nums, len, res, maxL, sortedLen);
        for(int l = maxL; l > max(minL,1); --l) //according to the max number of length maxL to generate all the max numbers ranging from minL to maxL (exclusive) and append them;
        {
            head = preHead + k; //jump to the next max-number pointer;
            memcpy(head, preHead, l*soi); 
            for(j = sortedLen; j < l; ++j)
            {
                if(head[j] > head[j - 1]) //remove the previous element encountering the first ascending pair;
                {
                    sortedLen = max(1, j - 1); //update the sortedLen;
                    memcpy(head + j - 1, preHead + j, soi*(l - j));
                    break;
                }
            }
            if(j == l) sortedLen = l; //it's already descending, remove the last element updating sortedLen to l;
            preHead = head; //update preHead;
        }
    }
    // merge max number created from single vector
    // @nums1 is the first array of length @len1
    // @nums2 is the second array of length @len2
    // @result is the array of length @resSize which will contain the max number generated
    // by the both two arrays without changing the order in each array;
    void merge(int* nums1,int len1,int* nums2,int len2,int* result,int& resSize)
    {
        int i = 0, j = 0, k = 0; //i -> result, j -> nums1, k -> nums2;
        while (i < resSize)
        {
            if (j < len1 && k < len2) //normal case;
            {
                if (nums1[j] > nums2[k]) //collect the bigger element first;
                    result[i++] = nums1[j++];
                else if (nums1[j] < nums2[k])
                    result[i++] = nums2[k++];
                else //when they are equal, collect the one with bigger lexical order;
                {
                    int remaining1 = len1-j, remaining2 = len2-k, tmp = nums1[j];
                    int flag = memcmp(nums1+j, nums2+k, sizeof(int)*min(remaining1, remaining2));
                    flag = (flag==0 ? (remaining1>remaining2 ? 1 : -1) : flag); //determine which is bigger in lexical order -> when the lexical order are the same the longer one will be bigger in order;
                    int * nums = flag > 0 ? nums1 : nums2;
                    int & cnt = flag > 0 ? j : k; //using reference to modify j or k;
                    int len = flag > 0 ? len1 : len2;
                    while (nums[cnt]==tmp && cnt < len && i<resSize) result[i++] = nums[cnt++];
                }
            }
            else if (j < len1) result[i++] = nums1[j++];
            else result[i++] = nums2[k++];
        }
    }

    //AC - 16ms - the most efficient solution;
    // Reference: https://leetcode.com/discuss/85603/c-16ms-fastest-beats-97%25
    vector<int> maxNumber(vector<int>& nums1, vector<int>& nums2, int k){
        int soi = sizeof(int), len1 = nums1.size(), len2 = nums2.size();
        int step = k*soi; //the space the final max number might take in memory;
        int minL1 = max(0, k-len2), maxL1 = min(k, len1), minL2 = k-maxL1, maxL2 = k-minL1, range = maxL1-minL1+1;
        int * res = new int[range*k*2 + 2*k], *dp1 = res+k, *dp2 = res+range*k+k, *tmp=res+range*2*k+k; //using one-dimension array to handle different arrays -> only using the necessary space without any waste;
        memset(res, 0, step);
        int sortedLen1=1, sortedLen2=1;
        if (len1 == 0 && len2 > 0) getMax(nums2, len2, res, k, sortedLen2); //handle corner cases;
        else if (len1 > 0 && len2 == 0) getMax(nums1, len1, res, k, sortedLen1);
        else if (len1 > 0 && len2 > 0) //the normal case;
        {
            dp(&nums1[0], len1, sortedLen1, minL1, maxL1, dp1,k);
            dp(&nums2[0], len2, sortedLen2, minL2, maxL2, dp2,k);
            if (sortedLen1+sortedLen2 > k) //special cases - needless to check each combination accelerating the process from 20ms to 16ms;
                merge(dp1 + k*(maxL1 - sortedLen1), sortedLen1, dp2 + k*(maxL2 - sortedLen2), sortedLen2, res, k);
            else for(int i = minL1; i <= maxL1; ++i)
            {
                merge(dp1+k*(maxL1-i), i, dp2+k*(maxL2-k+i), (k-i), tmp,k);
                if(memcmp(res, tmp, step) < 0) memcpy(res, tmp, step);
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
