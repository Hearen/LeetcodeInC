/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-02-19 11:18
Description : Given a binary tree

struct TreeLinkNode {
    TreeLinkNode *left;
    TreeLinkNode *right;
    TreeLinkNode *next;
}
Populate each next pointer to point to its next right node. If there is no next right node, the next pointer should be set to NULL.
Initially, all next pointers are set to NULL.
Note:
You may only use constant extra space.
You may assume that it is a perfect binary tree (ie, all leaves are at the same level, and every parent has two children).
For example,
Given the following perfect binary tree,
1
/  \
2    3
/ \  / \
4  5  6  7
After calling your function, the tree should look like:
1 -> NULL
/  \
2 -> 3 -> NULL
/ \  / \
4->5->6->7 -> NULL
Source      : https://leetcode.com/problems/populating-next-right-pointers-in-each-node/
*******************************************/
struct TreeLinkNode
{
    int val;
    struct TreeLinkNode *left, *right, *next;
};
#include <stdlib.h>
//AC - 4ms;
void connect(struct TreeLinkNode* root)
{
    if(!root || !root->left) return ;
    struct TreeLinkNode *p = root, *nextFirst;
    root->next = NULL;
    while(p && p->left)
    {
        nextFirst = p->left;
        while(p && p->left)
        {
            p->left->next = p->right;
            p->right->next = NULL;
            if(p->next)
                p->right->next = p->next->left;
            p = p->next;
        }
        p = nextFirst;
    }
}
