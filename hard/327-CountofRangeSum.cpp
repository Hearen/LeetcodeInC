/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-01-14 20:42
Description : 
Source      : https://leetcode.com/problems/count-of-range-sum/
*******************************************/
#include <limits.h>
#include <stdlib.h>
void swap(long*p, long*q)
{
    long t = *p;
    *p = *q;
    *q = t;
}

void swiftSort(long* arr, int low, int high)
{
    int l = low, r = high;
    long v = arr[l+(r-l)/2];
    while(l <= r)
    {
        while(arr[l] < v) l++;
        while(arr[r] > v) r--;
        if(l <= r)
        {
            swap(arr+l, arr+r);
            l++, r--;
        }
    }
    if(r > low)
        swiftSort(arr, low, r);
    if(l < high)
        swiftSort(arr, l, high);
}

int indexOf(long* arr, int size, double a)
{
    int l = 0, r = size-1, m;
    while(l <= r)
    {
        m = l + (r-l)/2;
        arr[m] <= a? (l=m+1) : (r=m-1);
    }
    return l;
}

int counter(long* nums, int l, int h, int low, int high)
{
    if(h == l)
        return (nums[l] >= low && nums[l] <= high)? 1:0;
    int m = l + (h-l)/2;
    int count = 0;
    int tmpSize = h-m;
    long *arr = (long*)malloc(sizeof(long)*tmpSize);
    long sum = 0;
    for(int i = m+1; i <= h; i++)
    {
        sum += nums[i];
        arr[i-m-1] = sum;
    }
    swiftSort(arr, 0, tmpSize-1);
    sum = 0;
    for(int i = m; i >= l; i--)
    {
        sum += nums[i];
        count += indexOf(arr, tmpSize, high-sum+0.5) - indexOf(arr, tmpSize, low-sum-0.5);
    }
    return counter(nums, l, m, low, high) + counter(nums, m+1, h, low, high) + count;
}

//AC - 72ms - Divide and Conquer;
int countRangeSum(int* nums, int size, int low, int high)
{
    if(size == 0)
        return 0;
    long *a = (long*)malloc(sizeof(long)*size);
    for(int i = 0; i < size; i++)
        nums[i] == INT_MIN? (a[i] = -1*INT_MIN) : (a[i] = nums[i]);
    return counter(a, 0, size-1, low, high);
}

#include <vector.h>

class Solution 
{  
public:
    // return last index <= hint.
    int BinarySearch(const vector<long long> &ranges, const long long hint) 
    {
        int begin = 0;
        int end = ranges.size();
        while (begin < end) 
        {
            int mid = begin + (end - begin) / 2;
            if (hint < ranges[mid]) end = mid;
            else begin = mid + 1;
        }
        return end - 1;
    }

    long long SumBIT(const vector<long long> &bit, int idx) 
    {
        long long sum = 0;
        while (idx > 0) 
        {
            sum += bit[idx];
            idx -= (idx & -idx);
        }
        return sum;
    }

    //updating process;
    void AddBIT(vector<long long> &bit, int idx, int value) 
    {
        const int n = bit.size();
        while (idx < n) 
        {
            bit[idx] += value;
            idx += (idx & -idx);
        }
    }

    vector<long long> BuildPrefixSum(const vector<int> &nums) 
    {
        vector<long long> prefix_sums(nums.size() + 1, 0);
        for (int i = 1; i <= nums.size(); ++i) prefix_sums[i] = prefix_sums[i - 1] + nums[i - 1];
        return prefix_sums;
    }

    vector<long long> BuildSortedRanges(const vector<long long> &prefix_sums) 
    {
        // remove duplicates.
        set<long long> help(prefix_sums.cbegin(), prefix_sums.cend());
        // make sure BinarySearch not return zero. This is *important*!
        help.insert(LLONG_MIN);
        // return sorted array.
        return vector<long long>(help.begin(), help.end());
    }

    //AC - using Fenwick Tree (Binary Indexed Tree);
    //reference: http://www.geeksforgeeks.org/binary-indexed-tree-or-fenwick-tree-2/
    int countRangeSum(vector<int>& nums, int lower, int upper) 
    {
        if (nums.empty()) return 0;
        const int n = nums.size();
        auto prefix_sums = BuildPrefixSum(nums);
        auto ranges = BuildSortedRanges(prefix_sums);
        vector<long long> bit(ranges.size(), 0);
        for (int i = 0; i <= n; ++i) // mark prefix sums.
            AddBIT(bit, BinarySearch(ranges, prefix_sums[i]), 1);
        int count = 0;
        for (int i = 0; i < n; ++i) 
        {
            // make prefix_sums[i] invisible.
            AddBIT(bit, BinarySearch(ranges, prefix_sums[i]), -1);
            // count the number of valid ranges.
            count += SumBIT(bit, BinarySearch(ranges, upper + prefix_sums[i]));
            count -= SumBIT(bit, BinarySearch(ranges, lower + prefix_sums[i] - 1));
        }
        return count;
    }

    //AC - 100ms - using multiset sorting feature;
    int countRangeSum(vector<int>& nums, int lower, int upper) 
    {
        if (nums.empty()) return 0;
        const int n = nums.size();
        auto prefix_sums = BuildPrefixSum(nums);
        int count = 0;
        multiset<long long> ordered_sums;
        for (int i = n; i >= 1; --i) 
        {
            ordered_sums.insert(prefix_sums[i]);
            auto lb_iter = ordered_sums.lower_bound(lower + prefix_sums[i - 1]);
            auto ub_iter = ordered_sums.upper_bound(upper + prefix_sums[i - 1]);
            count += distance(lb_iter, ub_iter);
        }
        return count;
    }
};


class Solution {
    struct SegmentTree 
    {
        SegmentTree* left;
        SegmentTree* right;
        int count;
        long min;
        long max;
        // constructing the SegmentTree - nums have been sorted
        SegmentTree(vector<long>& nums, int l, int r):left(NULL),right(NULL) 
        {
            if (l>r) return;
            min = nums[l];
            max = nums[r];
            count=0;
            if (l==r) return;
            int m = (l+r)/2;
            if (l<=m) left = new SegmentTree(nums, l,m);
            else left=NULL;
            if (m+1<=r) right = new SegmentTree(nums, m+1, r);
            else right = NULL;
        }

        //update process;
        void add(long value) 
        {
            if (value<min || value>max) return;
            count++;
            if (left && value<=left->max) left->add(value);
            else if (right && value>=right->min) right->add(value);
        }

        //getSum process;
        int getCount(long minValue, long maxValue) 
        {
            if (minValue<=min && max<=maxValue) return count;
            if (maxValue<min || minValue>max) return 0;
            int leftCount = left ? left->getCount(minValue, maxValue) : 0;
            int rightCount = right ? right->getCount(minValue, maxValue) : 0;
            return leftCount+rightCount;
        }
    };


public:
    //AC - 48ms - SegmentTree using the prefixSum to indicate the range of the node and 
    //an extra variable count to record the count of the prefixSum that is within the range;
    //reference: https://codelucid.wordpress.com/2015/05/27/segment-trees/
    int countRangeSum(vector<int>& nums, int lower, int upper) 
    {
        if (nums.size()==0) return 0;
        unordered_set<long> values;
        long sum = 0;
        for(int i=0;i<nums.size();++i) 
        {
            sum+=nums[i];
            values.insert(sum);
        }
        vector<long> sums;
        for(auto& v : values) sums.push_back(v);
        sort(sums.begin(), sums.end());
        SegmentTree* tree = new SegmentTree(sums, 0, sums.size()-1);
        int count = 0;
        for(int i=nums.size()-1;i>=0;i--) 
        {
            tree->add(sum);
            sum-=nums[i];
            count += tree->getCount(lower+sum, upper+sum);
        }
        return count;
    }
};
