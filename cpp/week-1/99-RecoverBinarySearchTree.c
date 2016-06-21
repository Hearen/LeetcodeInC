/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-02-20 19:19
Description : Two elements of a binary search tree (BST) are swapped by mistake.
Recover the tree without changing its structure.
Note:
A solution using O(n) space is pretty straight forward. Could you devise a constant space solution?
Source      : https://leetcode.com/problems/recover-binary-search-tree/
*******************************************/
struct TreeNode
{
    int val;
    struct TreeNode *left, *right;
};
#include <stdlib.h>
void traverse(struct TreeNode* root, struct TreeNode** pre, struct TreeNode** first, struct TreeNode** second)
{
    if(!root) return ;
    traverse(root->left, pre, first, second);
    if((*pre) && (*pre)->val>root->val) //check whether the previous node is abnormal in in-order traversal;
    {
        if(!(*first)) //if *first is never used then it should be used to store the bigger; 
            *first=*pre; 
        *second = root; //the two swapped nodes can be adjacent and distant;
    }
    *pre = root; //store the previous node in in-order traversal;
    traverse(root->right, pre, first, second);
}
//AC - 20ms;
void recoverTree0(struct TreeNode* root)
{
    struct TreeNode *first=NULL, *second=NULL, *pre=NULL;
    traverse(root, &pre, &first, &second);
    if(first&&second)
    {
        int t = first->val;
        first->val = second->val;
        second->val = t;
    }
}

void recoverTree(struct TreeNode* root)
{
    struct TreeNode *pre=NULL, *first=NULL, *second=NULL;
    struct TreeNode *t = NULL;
    while(root)
    {
        if(root->left)
        {
            t = root->left;
            while(t->right && t->right!=root) t = t->right;
            if(t->right)
            {
                if(pre && pre->val > root->val)
                {
                    if(!first)
                    {
                        first = pre;
                        second = root;
                    }
                    else second = root;
                }
                pre = root;
                t->right = NULL;
                root = root->right;
            }
            else
            {
                t->right = root;
                root = root->left;
            }
        }
        else
        {
            if(pre && pre->val > root->val)
            {
                if(!first) first=pre, second=root;
                else second = root;
            }
            pre = root;
            root = root->right;
        }
    }
    if(first && second)
    {
        first->val += second->val;
        second->val = first->val-second->val;
        first->val -= second->val;
    }
}
