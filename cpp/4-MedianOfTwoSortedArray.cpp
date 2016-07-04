/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2015-12-25 16:09
Description :There are two sorted arrays nums1 and nums2 of size m and n respectively. Find the median of the two sorted arrays. The overall run time complexity should be O(log (m+n)).
Source      : https://leetcode.com/problems/median-of-two-sorted-arrays/
*******************************************/
class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) 
    {
        if(nums1.size() > nums2.size()) nums1.swap(nums2);
        int size1 = nums1.size(), size2 = nums2.size();
        int mid = (size1+size2-1)/2;
        int l = 0, r = mid>size1? size1 : mid;
        while(l < r)
        {
            int m1 = (l+r)/2;
            int m2 = mid - m1;
            if(nums1[m1] < nums2[m2]) l = m1+1;
            else r = m1;
        }
        int a = max(l>0? nums1[l-1]:INT_MIN, mid-l<size2? nums2[mid-l] : INT_MIN);
        if((size1+size2)&1) return a;
        int b = min(l<size1? nums1[l]:INT_MAX, mid-l+1<size2? nums2[mid-l+1]:INT_MAX);
        return (double)(a+b)/2;
    }
};

