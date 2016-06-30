/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : Thu, 30 Jun 2016 10:32 CST
Description : Given a non-empty 2D matrix matrix and an integer k, find the max sum of a rectangle in the matrix such that its sum is no larger than k.

Example:
Given matrix = [
[1,  0, 1],
[0, -2, 3]
]
k = 2
The answer is 2. Because the sum of rectangle [[0, 1], [-2, 3]] is 2 and 2 is the max number no larger than k (k = 2).

Note:
The rectangle inside the matrix must have an area > 0.
What if the number of rows is much larger than the number of columns?
Source      : https://leetcode.com/problems/max-sum-of-sub-matrix-no-larger-than-k/
*******************************************/
class Solution {
public:
    int maxSumSubmatrix(vector<vector<int>>& matrix, int k) 
    {
        if(matrix.empty()) return 0;
        int rowSize = matrix.size(), colSize = matrix[0].size();
        int ret = INT_MIN;
        for(int l = 0; l < colSize; ++l) //starting column;
        {
            vector sums = vector<int>(rowSize, 0); //store the row pre-sums;
            for(int c = l; c < colSize; ++c) //try different ending columns;
            {
                for(int r = 0; r < rowSize; ++r) 
                    sums[r] += matrix[r][c];
                set<int> sums_set;
                sums_set.insert(0); //sentinel;
                int maxSum = INT_MIN, sum = 0;
                for(int i = 0; i < rowSize; ++i)
                {
                    sum += sums[i]; //the sum from the starting top-left to current position;
                    auto iter = sums_set.lower_bound(sum-k);
                    if(iter != sums_set.end()) maxSum = max(maxSum, sum-*iter);
                    sums_set.insert(sum);
                }
                ret = max(ret, maxSum);
            }
        }
        return ret;
    }
};
