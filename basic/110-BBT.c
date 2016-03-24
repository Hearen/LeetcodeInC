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
    int lHeight=height(root->left), rHeight=height(root->right);
    return 1+(lHeight > rHeight? lHeight : rHeight); 
}

//AC - 8ms - traverse twice;
bool isBalanced0(struct TreeNode* root)
{
    if(!root) return true;
    int lHeight = height(root->left), rHeight = height(root->right);
    if(abs(lHeight-rHeight) > 1) return false;
    return isBalanced0(root->left) && isBalanced0(root->right);
}

int helper(struct TreeNode* root)
{
    if(!root) return 0;
    int lHeight=helper(root->left), rHeight=helper(root->right);
    if(lHeight==-1 || rHeight==-1) return -1;
    if(abs(lHeight-rHeight) > 1) return -1;
    return 1+(lHeight>rHeight? lHeight:rHeight);
}

//AC - 8ms - just traverse once;
bool isBalanced(struct TreeNode* root)
{
    return helper(root) != -1;
}


