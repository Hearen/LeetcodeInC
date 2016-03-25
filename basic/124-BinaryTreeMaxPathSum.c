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
#include <limits.h>
#define MAX(a, b) ((a) > (b)? (a) : (b))
struct TreeNode
{
    int val;
    struct TreeNode *left, *right;
};

int max(int a, int b)
{
    return a > b? a : b;
}

//return the max sum ended with root and refresh the global max path sum accordingly;
int helper(struct TreeNode* root, int* maxSum)
{
    if(!root) return 0;
    int lMax = max(0, helper(root->left, maxSum)); //if the result of helper in left is negative, select nothing is better;
    int rMax = max(0, helper(root->right, maxSum));
    *maxSum = max(*maxSum, lMax+rMax+root->val);
    return max(lMax, rMax)+root->val;
}
//AC - 16ms;
int maxPathSum(struct TreeNode* root)
{
    if(!root) return 0;
    int maxSum = INT_MIN;
    helper(root, &maxSum);
    return maxSum;
}
