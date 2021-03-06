/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-01-19 08:06
Description : Given a binary tree, find its maximum depth.
The maximum depth is the number of nodes along the longest path from the root node down to the farthest leaf node.
Source      : https://leetcode.com/problems/maximum-depth-of-binary-tree/
*******************************************/
#include <stdlib.h>
struct TreeNode
{
    int val;
    struct TreeNod *left, *right;
};
//AC - 4ms;
int maxDepth( struct TreeNode * root )
{
    if(root == NULL)
        return 0;
    int lDepth = maxDepth(root->left);
    int rDepth = maxDepth(root->right);
    return 1 + (lDepth > rDepth ? lDepth : rDepth);
}
