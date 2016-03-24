/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-02-19 21:15
Description : Given inorder and postorder traversal of a tree, construct the binary tree.
Note:
You may assume that duplicates do not exist in the tree.
Source      : https://leetcode.com/problems/construct-binary-tree-from-inorder-and-postorder-traversal/
*******************************************/
struct TreeNode
{
    int val;
    struct TreeNode *left, *right;
};
#include <stdlib.h>
//AC - 20ms;
struct TreeNode* buildTree(int* inorder, int inSize, int* postorder, int postSize)
{
    if(inSize==0) return NULL;
    int cur = 0;
    for(; cur < inSize; cur++)
        if(postorder[postSize-1] == inorder[cur]) 
            break;
    struct TreeNode *root = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    root->val = inorder[cur];
    root->left = buildTree(inorder, cur, postorder, cur);
    root->right = buildTree(inorder+cur+1, inSize-cur-1, postorder+cur, inSize-cur-1);
    return root;
}
