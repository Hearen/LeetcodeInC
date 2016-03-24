/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-01-06 08:16
Description : Given a singly linked list where elements are sorted in ascending order, convert it to a height balanced BST.
Source      : https://leetcode.com/problems/convert-sorted-list-to-binary-search-tree/
*******************************************/
#include <stdlib.h>
#define FOO
struct ListNode{
    int val;
    struct ListNode* next;
};

struct TreeNode
{
    int val;
    struct TreeNode* left;
    struct TreeNode* right;
};

//AC - 8ms;
struct TreeNode* sortedListToBST(struct ListNode* head)
{
    if(head == NULL)
        return NULL;
    if(head->next == NULL)
    {
        struct TreeNode *t = (struct TreeNode*)malloc(sizeof(struct TreeNode));
        t->right = t->left = NULL;
        t->val = head->val;
        return t;
    }
    struct ListNode* slow = head;
    struct ListNode* fast = head->next->next;
    while(fast && fast->next)
    {
        slow = slow->next;
        fast = fast->next->next;
    }
    struct TreeNode* root = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    root->val = slow->next->val;
    root->right = sortedListToBST(slow->next->next);
    slow->next = NULL;
    root->left = sortedListToBST(head);
    return root;
}
