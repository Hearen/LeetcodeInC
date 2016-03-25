/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-02-19 19:20
Description : Given a binary tree, flatten it to a linked list in-place.

For example,
Given

         1
        / \
        2   5
        / \   \
        3   4   6
The flattened tree should look like:
1
\
    2
        \
            3
                \
                    4
                        \
                            5
                                \
                                    6
Source      : https://leetcode.com/problems/flatten-binary-tree-to-linked-list/
*******************************************/
struct TreeNode
{
    int val;
    struct TreeNode *left, *right;
};

#include <stdlib.h>
struct TreeNode* traverseLeft(struct TreeNode* root)
{
    if(!root->left &&!root->right) return root;
    struct TreeNode* t = root->right;
    root->right = root->left;
    struct TreeNode *leftmost = root; //in case of NULL left;
    if(root->left)
        leftmost = traverseLeft(root->left);
    root->left = NULL; //make sure all the left pointer is NULL;
    leftmost->right = t; //using the leftmost pointer to connect the right children;
    if(t)
        traverseLeft(t); 
}

//AC - 4ms;
void flatten(struct TreeNode* root)
{
    if(!root) return ;
    traverseLeft(root);
}
