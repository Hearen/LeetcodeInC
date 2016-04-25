/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-02-20 14:22
Description : Given a binary search tree, write a function kthSmallest to find the kth smallest element in it.
Note: 
You may assume k is always valid, 1 ≤ k ≤ BST's total elements.
Follow up:
What if the BST is modified (insert/delete operations) often and you need to find the kth smallest frequently? How would you optimize the kthSmallest routine?
Source      : https://leetcode.com/problems/kth-smallest-element-in-a-bst/
*******************************************/
struct TreeNode
{
    int val;
    struct TreeNode *left, *right;
};
#include <stdlib.h>

int helper(struct TreeNode* root, int* k)
{
    if(root)
    {
        int ret = helper(root->left, k);
        if(!(*k)) return ret;
        if(!(*k-=1)) return root->val;
        return helper(root->right, k);
    }
}
//AC - 12ms - a recursive in-order solution;
int kthSmallest0(struct TreeNode* root, int k)
{
    return helper(root, &k);
}

//AC - 12ms - a stack-in-order solution;
#define LEN 100
int kthSmallest1(struct TreeNode* root, int k)
{
    struct TreeNode** stack = (struct TreeNode**)malloc(sizeof(struct TreeNode*)*LEN);
    int top = -1;
    while(root)
    {
        stack[++top] = root;
        root = root->left;
    }
    while(k)
    {
        struct TreeNode *t = stack[top--];
        k--;
        if(!k) return t->val;
        struct TreeNode *p = t->right;
        while(p)
        {
            stack[++top] = p;
            p = p->left;
        }
    }
    return 0;
}

#define LEN 100
int kthSmallest2(struct TreeNode* p, int k)
{
    struct TreeNode** stack = (struct TreeNode**)malloc(sizeof(struct TreeNode*)*LEN);
    int top = -1;
    while(p || top>-1)
    {
        while(p)
        {
            stack[++top] = p;
            p = p->left;
        }
        p = stack[top--];
        k--;
        if(!k) return p->val;
        p = p->right;
    }
    return 0;
}

int countNodes(struct TreeNode* root)
{
    if(!root) return 0;
    return 1+countNodes(root->left)+countNodes(root->right);
}

//AC - 12ms;
int kthSmallest(struct TreeNode* root, int k)
{
    int lCount = countNodes(root->left);
    if(k == lCount+1) return root->val;
    else if(k <= lCount) return kthSmallest(root->left, k);
    else return kthSmallest(root->right, k-lCount-1);
}

