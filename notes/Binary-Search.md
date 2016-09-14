### Wiki
In computer science, binary search, also known as half-interval search or logarithmic search, is a search algorithm that finds the position of a target value within a sorted array. It compares the target value to the middle element of the array; if they are unequal, the half in which the target cannot lie is eliminated and the search continues on the remaining half until it is successful.
Binary search runs in at worst logarithmic time, making O(logn) comparisons, where n is the number of elements in the array and log is the binary logarithm; and using only constant O(1) space. Although specialized data structures designed for fast searching—such as hash tables—can be searched more efficiently, binary search applies to a wider range of search problems.

Although the idea is simple, implementing binary search correctly requires attention to some subtleties about its `exit conditions` and `midpoint calculation`.

### Implementation issues

- If the midpoint of the span is calculated as (L + R) / 2, then the value of L + R may exceed the range of integers of the data type used to store the midpoint, even if L and R are within the range. This can be avoided by calculating the midpoint as L + (R − L) / 2.

- An infinite loop may occur if the exit conditions for the loop—or equivalently, recursive step—are not defined correctly. Once L exceeds R, the search has failed and must convey the failure of the search. In addition, the loop must be exited when the target element is found, or in the case of an implementation where this check is moved to the end, checks for whether the search was successful or failed at the end must be in place.

- If the search space consists only of integers, test your algorithm on a two-element set to be sure it doesn’t lock up

- Verify that the lower and upper bounds are not overly constrained: it’s usually better to relax them as long as it doesn’t break the predicate

- Clarify what exactly you are looking for and then make sure each round your searching space will not lose it

### Median of Two Sorted Arrays
There are two sorted arrays nums1 and nums2 of size m and n respectively. Find the median of the two sorted arrays. The overall run time complexity should be O(log (m+n)).

> Example 1:
nums1 = [1, 3]
nums2 = [2] 
The median is 2.0

> Example 2:
nums1 = [1, 2]
nums2 = [3, 4] 
The median is (2 + 3)/2 = 2.5

[test](https://discuss.leetcode.com/topic/54889/solution-in-c-well-explained/4)


### Solution
Median is the middle number which partitions the sorted array into two halves with same length, even when it comes to two sorted array, the rule will always apply. 

Overview of the partition:
```
  A[i-1]   |   A[i]
          \|/
          /|\
  B[i-1]   |   B[j]
```

So in this problem, we are to search out the four border numbers A[i-1] and A[i] in array-1 and B[j-1] and B[j] in array-2 to ensure that: 
- First, `max(A[i-1],B[j-1])` is smaller than or equal to `min(A[i],B[j])`.
- Second, `len(A[0]...A[i-1])+len(B[0]...B[j-1])==len(A[i]...A[n-1])+len(B[j]...B[m-1])`, n and m is the size of the array-1 and array-2 respectively. 
- Third,  to ensure the above two conditions, there must be a equation `mid=i+j-1=(m+n-1)/2` and as a result A[i-1] corresponds to B[j] and B[j-1] corresponds to A[i]; so actually we need to search two pairs, which will meet the following requirements: `A[i-1]<=B[j]` and `B[j-1]<=A[i]`.

Now let's dive into details of its implementation.

- First, get the index of the final median index of the two arrays `mid=(m+n-1)/2=i+j-1`, in which case if the whole size of the two array is odd, then the median will be `max(A[i-1],B[j-1])`; if it's even, then the median will be `(max(A[i-1],B[j-1])+min(A[i],B[j]))/2`.
- Second, do the binary searching based on array-1, starting with `l=0`, `r=n-1` and `m1=l+((r-l)>>1)`; and the corresponding index in array-2 will be `m2=mid-m1`.
- Third, if `A[m1] < B[m2]` then we should select the bigger half by `l=m1+1` since `m1` is too small while we need to find the biggest `A[m1]` that is smaller than `B[m2]`, which can then ensure us `A[m1+1]>B[m2-1]`; otherwise select the smaller half by `r=m1-1` since it's too big, which can then ensure us `A[m1-1]<B[m2+1]`.
- Forth, after the searching, `r == l-1` and as a result `l` will point to `A[i]` while `r` pointing to `A[i-1]`, which means `A[i-1], A[i], B[j-1] and B[j]` are `A[r], A[l], B[mid-l] and B[mid-r]` respectively. 
- Fifth, in the end, we can retrieve the median as `First` presents.

```
class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        if(nums1.size() > nums2.size()) nums1.swap(nums2);
        int size = nums1.size()+nums2.size(), mid = (size-1)/2;
        int l = 0, r = nums1.size()-1;
        while(l <= r) {
            int m1 = l+((r-l)>>1), m2 = mid-m1;
            if(nums1[m1] < nums2[m2]) l = m1+1;
            else r = m1-1;
        }
        int a = max(l>0? nums1[r]:INT_MIN, mid-l<nums2.size()? nums2[mid-l]:INT_MIN);
        if(size&1) return a;
        int b = min(l<nums1.size()? nums1[l]:INT_MAX, mid-l+1<nums2.size()? nums2[mid-r]:INT_MAX);
        return (a+b)/2.0;
    }
};
```
### Search for a Range
Given a sorted array of integers, find the starting and ending position of a given target value. Your algorithm's runtime complexity must be in the order of O(log n).  If the target is not found in the array, return [-1, -1].

> For example,
Given [5, 7, 7, 8, 8, 10] and target value 8,
return [3, 4].

[test](https://leetcode.com/problems/search-for-a-range/)

### Solution

#### Built-in method
Directly we can use `lower_bound` and `upper_bound` to search for the range.

> **Note** `nums.end()` will point to the position after the last number.

```
class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        int l = lower_bound(nums.begin(), nums.end(), target)-nums.begin();
        if(nums[l] != target) return vector<int>{-1, -1};
        int r = upper_bound(nums.begin(), nums.end(), target)-nums.begin();
        return vector<int>{l, r-1};
    }
};
```

#### Binary search
Since we can achieve it via built-in methods, similarly we can do it manually by binary searching. But in each selecting the half, we will control the preference for the `target` in the left or right to get the leftmost and rightmost of the `target` in the array.

> **Note** In `l < r` format, as long as the `r = m`, it will never tumble into infinite loop.

```
class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        vector<int> v;
        int l = 0, r = nums.size()-1;
        while(l < r) {
            int m = l+((r-l)>>1);
            nums[m] >= target? r = m : l = m+1;
        }
        nums[l] == target? v.push_back(l) : v.push_back(-1);
        l = 0, r = nums.size()-1;
        while(l < r) {
            int m = l+((r-l)>>1);
            nums[m] > target? r = m : l = m+1;
        }
        if(nums[l] != target) l--;
        nums[l] == target? v.push_back(l) : v.push_back(-1);
        return v;
    }
};
```

### Valid Perfect Square
ven a positive integer num, write a function which returns True if num is a perfect square else False.  
Note: Do not use any built-in library function such as sqrt.  
> Example 1: Input: 16 Returns: True 
Example 2: Input: 14 Returns: False

```
bool isPerfectSquare(int num) {
    long l = 0, r = num, m = 0;
    while(l < r) {
        int m = l+((r-l)>>1), t = m*m;
        if(t == num) return true; //quite essential
        else if(t > num) r = m;
        else if(t < num) l = m+1;
    }
    return l*l == num;
}
```

### Sqrt(x)
Implement int sqrt(int x).  Compute and return the square root of x.

### Solution

#### Binary search
Directly, we will go to binary search but as for integer sqrt there is one thing should be aware of: sqrt(5)=2 which indirectly gives us hint we should keep the smaller in binary searching but if we do, we will encounter TLE in case `1`. 

- As a result, we will not keep the smaller and when we end our searching, we will check it again to return the right value which should be the smallest that's bigger than the result by 1.
- Besides to avoid overflow, we will use long instead of int.

> **Note** to avoid infinite loop, we actually should make sure the `m` will be neither the `l` nor `r` when the next half is about `l=m or r=m`.

```
int mySqrt(int x) {
    int l = 0, h = x;
    while(l <= h) {
        long m = l+((h-l)>>1), t = m*m;
        if(t == x) return m;
        if(t > x) h = m-1;
        else l = m+1;
    }
    return l*l>x? l-1:l;
}
```

#### Newton's method
This is a math solution which is presented as follows; remember to use `long` to avoid overflow.
For more details about [methods](https://en.wikipedia.org/wiki/Methods_of_computing_square_roots) of computing square roots including Newton's method.

```
int mySqrt(int x) {
    long g = x;
    while(g*g > x) g = (g+x/g)/2;
    return g;
}
```

### Longest Increasing Subsequence
Given an unsorted array of integers, find the length of longest increasing subsequence.
For example,
Given [10, 9, 2, 5, 3, 7, 101, 18],
The longest increasing subsequence is [2, 3, 7, 101], therefore the length is 4. Note that there may be more than one LIS combination, it is only necessary for you to return the length.  
Your algorithm should run in O(n2) complexity.  
Follow up: Could you improve it to O(n log n) time complexity?

```
class Solution {
public:
    int lowerBound(vector<int>& nums, int a) {
        if(nums.empty()) return 0;
        int l = 0, r = nums.size()-1;
        while(l < r) {
            int m = l+((r-l)>>1);
            if(nums[m] < a) l = m+1;
            else  r = m;
        }
        return nums[l]<a? l+1 : l;
    }
    int lengthOfLIS(vector<int>& nums) {
        vector<int> v;
        for(int i = 0; i < nums.size(); ++i) {
            int pos = lowerBound(v, nums[i]);
            if(pos == v.size()) v.push_back(nums[i]);
            else v[pos] = nums[i];
        }
        return v.size();
    }
};
```

More C++ way using lower_bound, which means the previous binary search is doing the `lower_bound` thing.

```
int lengthOfLIS(vector<int>& nums) {
    vector<int> collector;
    for(int i = 0; i < nums.size(); ++i) {
        auto iter = std::lower_bound(collector.begin(), collector.end(), nums[i]);
        if(iter == collector.end()) collector.push_back(nums[i]);
        else *iter = nums[i];
    }
    return collector.size();
}
```

### Find the Duplicate Number
Given an array nums containing n + 1 integers where each integer is between 1 and n (inclusive), prove that at least one duplicate number must exist. Assume that there is only one duplicate number, find the duplicate one.
Note:
You must not modify the array (assume the array is read only).
You must use only constant, O(1) extra space.
Your runtime complexity should be less than O(n2).
There is only one duplicate number in the array, but it could be repeated more than once.
```
int findDuplicate(vector<int>& nums) {
    int l = 1, r = nums.size()-1;
    while(l < r) {
        int m = l+(r-l)/2;
        int count = 0;
        for(int i = 0; i < nums.size(); ++i)
            if(l<=nums[i] && m>=nums[i]) count++;
        if(count <= m-l+1) l = m+1;
        else r = m;
    }
    return l;
}
```

Another neat solution using loop searching technique.

```
int findDuplicate(vector<int>& nums) {
    int slow = nums[0], fast = nums[nums[0]];
    while(slow != fast) {
        slow = nums[slow];
        fast = nums[nums[fast]];
    }
    fast = 0;
    while(fast != slow) {
        slow = nums[slow];
        fast = nums[fast];
    }
    return slow;
}
```

### First Bad Version
You are a product manager and currently leading a team to develop a new product. Unfortunately, the latest version of your product fails the quality check. Since each version is developed based on the previous version, all the versions after a bad version are also bad.  Suppose you have n versions [1, 2, ..., n] and you want to find out the first bad one, which causes all the following ones to be bad.  You are given an API bool isBadVersion(version) which will return whether version is bad. Implement a function to find the first bad version. You should minimize the number of calls to the API.

```
int firstBadVersion(int n) {
    int l = 1, r = n, m = 0;
    while(l < r) {
        m = l+((r-l)>>1);
        if(isBadVersion(m)) r = m;
        else l = m+1;
    }
    return l;
}
```
### H-Index 
Given an array of citations (each citation is a non-negative integer) of a researcher, write a function to compute the researcher's h-index.  
According to the definition of h-index on Wikipedia: "A scientist has index h if h of his/her N papers have at least h citations each, and the other N − h papers have no more than h citations each." 
For example, given citations = [3, 0, 6, 1, 5], which means the researcher has 5 papers in total and each of them had received 3, 0, 6, 1, 5 citations respectively. Since the researcher has 3 papers with at least 3 citations each and the remaining two with no more than 3 citations each, his h-index is 3.

> Follow-up: What if the citations array is sorted in ascending order? Could you optimize your algorithm?

[test](https://leetcode.com/problems/h-index-ii/)

### Solution
There is only one possible result and the demonstration logic is as follows:
Suppose, we have two different H-index in n citations and `a<b`.

- First, as for b, there are `b` citations that are bigger or equal to `b`.
- Second, as for a, there are `a` citations that are bigger or equal to `a` and the rest `n-a` citations are equal to or less than `a`;
- But, since `b>a` then there are at least `b` citations that are bigger than `a` (according to the First) and then at most there will be `n-b` that are less than or equal to `a` which is a contradiction against the fact that there will be `n-a` that is equal to or less than `a` (according to the Second). 

So once it's sorted, the index can be used to partition the array and do binary searching.

- First, the splitting element should be `citations[m]` and `citations.size()-m` and once they are equal, we should directly return otherwise continue the binary searching.
- Second, due to the special condition in the First, then we should  use `l=m+1` or `r=m-1` to select the next range and as a result the termination condition should be `l<=r`.

>**Note** Corner cases: [1], [0].

```
class Solution {
public:
    int hIndex(vector<int>& citations) {
        if(citations.empty()) return 0;
        int l = 0, r = citations.size()-1;
        while(l <= r) {
            int m = l+((r-l)>>1);
            if(citations.size()-m == citations[m]) return citations[m];
            else if(citations.size()-m > citations[m]) l = m+1;
            else if(citations.size()-m < citations[m]) r = m-1;
        }
        return citations.size()-l;
    }
};
```

### Search a 2D Matrix II
Write an efficient algorithm that searches for a value in an m x n matrix. This matrix has the following properties: 
Integers in each row are sorted from left to right.
The first integer of each row is greater than the last integer of the previous row.

> For example, 
Consider the following matrix: 
[
  [1,   3,  5,  7],
  [10, 11, 16, 20],
  [23, 30, 34, 50]
]
Given target = 3, return true.

[test](https://leetcode.com/problems/search-a-2d-matrix/)

### Solution
Very intuitive and simple binary searching problem, but I encountered a weird problem which is caused by my preference for `r` and `c` to represent the row index and column index and meantime I also love to use them to represent the leftmost and rightmost of an array. As a direct result, I have the following solution in C++.

```
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int l = 0, r = matrix[0].size()*matrix.size()-1;
        while(l <= r) {
            int m = l+((r-l)>>1);
            int r = m/matrix[0].size(), c = m%matrix[0].size();
            if(matrix[r][c] == target) return true;
            if(matrix[r][c] < target) l = m+1;
            else r = m-1;
        }
        return false;
    }
};
```

Once the searching comes into the loop, the `r` is no longer the rightmost and it will be covered by the inner `r` which is the row index. And then the row index will be updated by selecting the next half instead of the `rightmost` value `r`. And when the loop ends and checking the rightmost value by `r` which now is the outer `r` whose value has not changed and each time it will be the same. As a result, for most of the cases, the above solution will encounter infinite loop, `TLE`. After I update the `l` and `r` to `l` and `h`, everything just works fine. What a coincidence and bad habit.

```
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) 
    {
        int l = 0, h = matrix[0].size()*matrix.size()-1;
        while(l <= h)
        {
            int m = l+((h-l)>>1);
            int r = m/matrix[0].size(), c = m%matrix[0].size();
            if(matrix[r][c] == target) return true;
            if(matrix[r][c] < target) l = m+1;
            else h = m-1;
        }
        return false;
    }
};
```
### Find Peak Element
A peak element is an element that is greater than its neighbors.  Given an input array where num[i] ≠ num[i+1], find a peak element and return its index.  The array may contain multiple peaks, in that case return the index to any one of the peaks is fine.  You may imagine that num[-1] = num[n] = -∞.

> For example, in array [1, 2, 3, 1], 3 is a peak element and your function should return the index number 2.

[test](https://leetcode.com/problems/find-peak-element/)

### Solution
The most direct solution is to search and compare its neighbors until a peak, but actually we can do better - if the next is bigger than the current then the current is a peak (bigger than its previous also) if not then the previous will already be returned.

> **Note** A corner case: the last number should be handled separately, since it will be ignored in the checking process discussed above.

```
int findPeakElement(vector<int>& nums) {
    for(int i = 0; i < nums.size()-1; ++i)
        if(nums[i] > nums[i+1]) return i;
    return nums.size()-1;
}
```
### Find Minimum in Rotated Sorted Array
Suppose a sorted array is rotated at some pivot unknown to you beforehand. And there are no duplicate.
> (i.e., 0 1 2 4 5 6 7 might become 4 5 6 7 0 1 2).  Find the minimum element 0.

> Follow-up: if there are duplicates, how would to solve it?

[test](https://leetcode.com/problems/find-minimum-in-rotated-sorted-array-ii/)

### Solution
In a rotate array, there will be a position where the `sequence changes`, no longer ascending and that number will be the minimum we are searching for. Accordingly, we can adopt binary searching to find it out and the key will be that `sequence change`. Let's suppose `l` and `r` will be the start and the end of the array and `m` is the middle between them.

- First, if `nums[m] > nums[r]` then the `sequence change` number will be between m and r.
- Second, if `nums[m] < nums[r]`, then the `sequence change` number will be between l and m.
- Third, if there exist duplicates and result in `nums[m]==nums[r]` then we will not know that that `sequence change` number but one thing for sure, `nums[r]` will not be the minimum so we can just move the `r` backward to eliminate `nums[r]` by `r--`, which can then be able to terminate the searching properly.

The third part is the essential, which delicately handle the duplicates and terminate the searching elegantly.

```
class Solution {
public:
    int findMin(vector<int>& nums) {
        int l = 0, r = nums.size()-1;
        while(l < r) {
            int m = l+((r-l)>>1);
            else if(nums[m] < nums[r]) r = m;
            else if(nums[m] > nums[l]) l = m+1;
            else r--;
        }
        return nums[l];
    }
};
```
### Search in Rotated Sorted Array
Suppose a sorted array is rotated at some pivot unknown to you beforehand.  
(i.e., 0 1 2 4 5 6 7 might become 4 5 6 7 0 1 2).  You are given a target value to search. If found in the array return its index, otherwise return -1.  
Note: You may assume no duplicate exists in the array.

> Follow-up: what if there are duplicates?

[test](https://leetcode.com/problems/search-in-rotated-sorted-array/)

### Solution
Usually, we will select binary searching for this problem. Suppose `l` and `r` pointing to the leftmost and rightmost of the array and `m` pointing to the middle. Since the array is sorted and rotated, we can take advantage of `nums[m]` and `nums[r]` to check which part is ordered, the left or the right to do our binary searching.

- First, if the `nums[m]==target` then we can just return.
- Second, if `nums[m]>nums[r]` then the left half `[l,m]` should be in ascending order, otherwise the right half `[m,r]` in ascending order;
- Third, if `nums[m]==nums[r]` then we should move `r` backwards since this value cannot be the target and we have to be able to end the searching (if not move it backward, we can encounter infinite loop in binary searching).
- Forth, once we know the ordering part then we can use normal technique to check whether the target is in that ordered range or not and select the next half for further searching.

> **Note** To ensure the whole array will be checked, we should set the termination condition to `l <= r` and as a result the half selection should be `r = m-1 and l = m+1`.
```
class Solution {
public:
    int search(vector<int>& nums, int target) {
        int l = 0, r = nums.size()-1;
        while(l <= r) {
            int m = l+((r-l)>>1);
            if(nums[m] == target) return m;
            if(nums[m] < nums[r]) {
                if(nums[m]<target && target<=nums[r]) l = m+1;
                else r = m-1;
            }
            else if(nums[m] > nums[r]) {
                if(nums[l]<=target && target<nums[m]) r = m-1;
                else l = m+1;
            }
            else r--;
        }
        return -1;
    }
};
```
### Kth Largest Element in an Array
Find the kth largest element in an unsorted array. Note that it is the kth largest element in the sorted order, not the kth distinct element.  
For example,
Given [3,2,1,5,6,4] and k = 2, return 5.
Note: 
You may assume k is always valid, 1 ≤ k ≤ array's length.

[test](https://leetcode.com/problems/kth-largest-element-in-an-array/)

### Solutions

There are five different solutions in this including partition, recursion, max heap, selection sort and just sorting.

#### Partition 

```
int findKthLargest(vector<int>& nums, int k) {
    int size = nums.size();
    int left=0, right=size-1;
    srand((unsigned(time(NULL))));
    for(int i = 0; i < size; ++i)
        swap(nums[i], nums[rand()%size]);
    while(true) {
        int pos=partition(nums, left, right);
        if(pos==k-1)  return nums[pos];
        if(pos>k-1)   right=pos-1;
        else left=pos+1;
    }
}

int partition(vector<int>& nums, int left, int right) {
    int pivot=nums[left];
    int l=left+1, r=right;
    while(l<=r) {
        if(nums[l]<pivot && nums[r]>pivot) swap(nums[l++], nums[r--]);
        if(nums[l]>=pivot) l++;
        if(nums[r]<=pivot) r--;                                               
    }
    swap(nums[left], nums[r]);
    return r;
}
```

#### Recursion

```
int findKthLargest(vector<int>& nums, int k) {
	int small = INT_MAX, big = INT_MIN;
	vector<int> smaller, bigger;
	for(int i = 0; i < nums.size(); ++i)
		small = min(small, nums[i]), big = max(big, nums[i]);
	if(small == big) return big;
	int m = small+((big-small)>>1);
	for(int i = 0; i < nums.size(); ++i)
		nums[i]>m? bigger.push_back(nums[i]):smaller.push_back(nums[i]);
	if(bigger.size() >= k) return findKthLargest(bigger, k);
	else return findKthLargest(smaller, k-bigger.size());
}
```

#### Maxheap

```
int findKthLargest(vector<int>& nums, int k) {
    priority_queue<int, vector<int>, less<int>> maxHeap(nums.begin(), nums.end());
    for(int i = 1; i < k; ++i) maxHeap.pop();
    return maxHeap.top();
}
```

#### Selection

```
int findKthLargest(vector<int>& nums, int k) {
    for(int i = 0; i < k; i++) {
        int localMax = i;
        for(int j = i+1; j < nums.size(); ++j)
            if(nums[j] > nums[localMax]) localMax = j;
        swap(nums[i], nums[localMax]);
    }
    return nums[k-1];
}
```

#### Sorting

```
int findKthLargest(vector<int>& nums, int k) {
    sort(nums.begin(), nums.end(), greater<int>());
    return nums[k-1];
}
```

#### Built-in method

```
int findKthLargest(vector<int>& nums, int k) {
    nth_element(nums.begin(), nums.begin()+nums.size()-k, nums.end());
    return nums[nums.size()-k];
}
```
### Kth Smallest Element in a Sorted Matrix
Given a n x n matrix where each of the rows and columns are sorted in ascending order, find the kth smallest element in the matrix.  

> Example: 
matrix = [
   [ 1,  5,  9 ],
   [10, 11, 13],
   [12, 13, 15]
],
k = 8, 
return 13.

Note: 
You may assume k is always valid, 1 ≤ k ≤ n^2.

[test](https://leetcode.com/problems/kth-smallest-element-in-a-sorted-matrix/)

### Solution

A similar problem [Search a 2D Matrix II](https://leetcode.com/problems/search-a-2d-matrix-ii/) which is searching for the target instead of the kth.

#### Analysis
Since the matrix is sorted in two directions, using binary search to find the kth smallest is an intuitive method. Since we are searching for the number, so the searching space should be the space ranging from the smallest to the biggest number in the matrix. 

> Note that the index here cannot be used to form the searching space since it's not linear to the numbers in the matrix, and as a result the index cannot partition the matrix properly.

> Take [[1,4],[3,5]] 2 as an example. If we use the index range as the searching space, `l=0, r=3, m=(0+3)/2=1` in the first round and then the numbers smaller than or equal to its number, `matrix[m/size][m%size]=matrix[1/2][1%2]=matrix[0][1]=4,` are 3 (1, 4 and 3 respectively) and then we will set r=m=1. Just now we have eliminated the potential answer number 3, whose index should be 2 matrix[2/2][2%2]=matrix[1][0]. All of these are because the index sequence is not linear to the matrix numbers whose order lies in two directions.

> **Note 2** we cannot use lower_bound too, it will be incorrect to remove the other half by `l=m+1:r=m` since m can be included while counting via lower_bound.

#### Details
- Start with half of the smallest and biggest of the matrix, and then count how many numbers are smaller than or equal to it row by row;
- K directly becomes the comparison determining which direction we will go in the next round, left part or the right part;
- Keep the answer number within the range [l, r] in each round.

The time complexity will be O(nlognlogm) while n is the number of rows in the matrix and m is the gap between the smallest and the biggest number in the matrix.

```
class Solution {
public:
    int kthSmallest(vector<vector<int>>& matrix, int k) {
        int size = matrix.size(), l = matrix[0][0], r = matrix[size-1][size-1];
        while(l < r) {
            int smaller = 0, m = l+((r-l)>>1);
            for(int i = 0; i < size; ++i) 
                smaller += upper_bound(matrix[i].begin(), matrix[i].end(), m)-matrix[i].begin();
            smaller<k? l=m+1 : r=m;
        }
        return r;
    }
};
```
### Conclusion
- termination `l < r` - `r = m` and `l = m+1` and after searching `l == r` 
- termination `l <= r` - `r = m-1` and `l = m+1` and after searching `l > r`
- always clearly know what you are searching for and keep that valid in the searching space
