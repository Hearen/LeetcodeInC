/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-02-18 21:19
Description : Given a binary tree, determine if it is height-balanced.
For this problem, a height-balanced binary tree is defined as a binary tree in which the depth of the two subtrees of every node never differ by more than 1.
Source      : https://leetcode.com/problems/balanced-binary-tree/
*******************************************/
#include <stdbool.h>
struct TreeNode
{
    int val;
    struct TreeNod *left, *right;
};
int height(struct TreeNode* root)
{
    if(!root) return 0;
    if(!root->left && !root->right) return 1;
    int lHeight=0, rHeight=0;
    if(root->left)
        lHeight = height(root->left)+1;
    if(root->right)
        rHeight = height(root->right)+1;
    return lHeight > rHeight? lHeight : rHeight; 
}

//AC - 8ms;
bool isBalanced(struct TreeNode* root)
{
    if(!root) return true;
    int lHeight = height(root->left);
    int rHeight = height(root->right);
    int min = lHeight > rHeight? rHeight : lHeight;
    int max = lHeight > rHeight? lHeight : rHeight;
    if(max-min > 1)
        return false;
    return isBalanced(root->left) && isBalanced(root->right);
}
