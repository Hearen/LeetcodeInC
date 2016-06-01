/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-02-19 16:17
Description : Given a binary tree, return the preorder traversal of its nodes' values.
For example:
Given binary tree {1,#,2,3},
   1
    \
    2
    /
    3
return [1,2,3].
Note: Recursive solution is trivial, could you do it iteratively?
Source      : https://leetcode.com/problems/binary-tree-preorder-traversal/
*******************************************/
#include <stdlib.h>
struct TreeNode
{
    int val;
    struct TreeNode *left, *right;
};

void traverse(struct TreeNode* root, int** arr, int* returnSize)
{
    *returnSize += 1;
    *arr = (int*)realloc(*arr, sizeof(int)*(*returnSize));
    (*arr)[*returnSize-1] = root->val;
    if(root->left)
        traverse(root->left, arr, returnSize);
    if(root->right)
        traverse(root->right, arr, returnSize);
}
//AC - 0ms;
int* preorderTraversal0(struct TreeNode* root, int* returnSize)
{
    if(!root) return NULL;
    int* arr = (int*)malloc(sizeof(int));
    *returnSize = 0;
    traverse(root, &arr, returnSize);
    return arr;
}


//AC - 0ms;
#define LEN 10000
int* preorderTraversal1(struct TreeNode* root, int* returnSize)
{
    *returnSize = 0;
    if(!root) return NULL;
    int* arr = (int*)malloc(sizeof(int)*LEN);
    struct TreeNode** stack = (struct TreeNode**)malloc(sizeof(struct TreeNode*)*LEN);
    int top = -1;
    stack[++top] = root;
    while(top > -1)
    {
        struct TreeNode* t = stack[top--];
        arr[(*returnSize)++] = t->val;
        if(t->right) stack[++top] = t->right;
        if(t->left) stack[++top] = t->left;
    }
    return arr;
}


//AC - 0ms;
//Using Morris Traversal to traverse in preorder;
int* preorderTraversal(struct TreeNode* root, int* returnSize)
{
    if(!root) return NULL;
    int* arr = (int*)malloc(sizeof(int));
    *returnSize = 0;
    while(root)
    {
        if(!root->left)
        {
            *returnSize += 1;
            arr = (int*)realloc(arr, sizeof(int)*(*returnSize));
            arr[*returnSize-1] = root->val;
            root = root->right;
        }
        else
        {
            struct TreeNode* pre = root->left;
            while(pre->right && pre->right!=root)
                pre = pre->right;
            if(!pre->right) //before moving to the left, collect it now;
            {
                *returnSize += 1;
                arr = (int*)realloc(arr, sizeof(int)*(*returnSize));
                arr[*returnSize-1] = root->val;
                pre->right = root;
                root = root->left;
            }
            else
            {
                pre->right = NULL; //restore the modified nodes;
                root = root->right;
            }
        }
    }
    return arr;
}
