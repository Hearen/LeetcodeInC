/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-02-19 12:21
Description : Follow up for problem "Populating Next Right Pointers in Each Node".

What if the given tree could be any binary tree? Would your previous solution still work?

Note:

You may only use constant extra space.
For example,
Given the following binary tree,
         1
        /  \
        2    3
        / \    \
        4   5    7
After calling your function, the tree should look like:
1 -> NULL
/  \
2 -> 3 -> NULL
/ \    \
4-> 5 -> 7 -> NULL
Source      : https://leetcode.com/problems/populating-next-right-pointers-in-each-node-ii/
*******************************************/
struct TreeLinkNode
{
    int val;
    struct TreeLinkNode *left, *right, *next;
};
#include <stdlib.h>
//AC - 8ms;
void connect0(struct TreeLinkNode* root)
{
    if(!root) return ;
    struct TreeLinkNode *p = root, *nextFirst;
    while(p)
    {
        nextFirst = NULL; //defaulted to NULL to jump out the loop;
        while(p) //search for the first valid node of the next level;
        {
            if(p->left)
            {
                nextFirst = p->left;
                break;
            }
            if(p->right)
            {
                nextFirst = p->right;
                break;
            }
            p = p->next;
        }
        struct TreeLinkNode *cur=nextFirst, *next;
        while(p) //connect the next level;
        {
            next = p->left;
            if(next && cur!=next) //only valid nodes can be connected and the next cannot be the same with current node;
            {
                cur->next = next;
                cur = next;
            }
            next = p->right;
            if(next && cur!=next)
            {
                cur->next = next;
                cur = next;
            }
            p = p->next;
        }
        p = nextFirst; //move to the next level;
    }
}

void connect1(struct TreeLinkNode* root)
{
    struct TreeLinkNode *head=NULL, *pre=NULL, *cur=root;
    while(cur)
    {
        while(cur) //connect the next level;
        {
            if(cur->left)
            {
                if(pre) pre->next = cur->left;
                else head = cur->left;
                pre = cur->left;
            }
            if(cur->right)
            {
                if(pre) pre->next = cur->right;
                else head = cur->right;
                pre = cur->right;
            }
            cur = cur->next;
        }
        cur = head;
        head = pre = NULL;
    }
}

void connect2(struct TreeLinkNode* root)
{
    struct TreeLinkNode *t = (struct TreeLinkNode*)malloc(sizeof(struct TreeLinkNode));
    struct TreeLinkNode *cur = t;
    while(root)
    {
        t->next = NULL; //reset for the next level;;
        cur = t;
        while(root) //collect the next level;
        {
            if(root->left)
            {
                cur->next = root->left;
                cur = cur->next;
            }
            if(root->right)
            {
                cur->next = root->right;
                cur = cur->next;
            }
            root = root->next;
        }
        root = t->next;
    }
}

void connect(struct TreeLinkNode* root)
{
    if(!root) return ;
    struct TreeLinkNode *t = (struct TreeLinkNode*)malloc(sizeof(struct TreeLinkNode));
    t->next = NULL;
    for(struct TreeLinkNode *cur=root, *pre=t; cur; cur = cur->next)
    {
        if(cur->left)
        {
            pre->next = cur->left;
            pre = pre->next;
        }
        if(cur->right)
        {
            pre->next = cur->right;
            pre = pre->next;
        }
    }
    connect(t->next);
}
