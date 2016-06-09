/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-02-20 20:05
Description : Given a binary tree, find the maximum path sum.
For this problem, a path is defined as any sequence of nodes from some starting node to any node in the tree along the parent-child connections. The path does not need to go through the root.
For example:
Given the below binary tree,
1
/ \
2   3
Return 6.
Source      : https://leetcode.com/problems/binary-tree-maximum-path-sum/
*******************************************/
class Solution {
private:
    int traverse(TreeNode* root, int& maxSum)
    {
        if(!root) return 0;
        int lMax = max(0, traverse(root->left, maxSum));
        int rMax = max(0, traverse(root->right, maxSum));
        maxSum = max(maxSum, lMax+rMax+root->val);
        return max(lMax, rMax)+root->val;
    }
public:
    //AC - bets-submission - global variable and return value;
    int maxPathSum(TreeNode* root) 
    {
        int maxSum = INT_MIN;
        traverse(root, maxSum);
        return maxSum;
    }

};
