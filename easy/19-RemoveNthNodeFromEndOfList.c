/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-01-22 08:59
Description : Given a linked list, remove the nth node from the end of list and return its head.
For example,
Given linked list: 1->2->3->4->5, and n = 2.

After removing the second node from the end, the linked list becomes 1->2->3->5.
Note:
Given n will always be valid.
Try to do this in one pass.
Source      : https://leetcode.com/problems/remove-nth-node-from-end-of-list/
*******************************************/
#include <stdlib.h>
struct ListNode
{
    int val;
    struct ListNode *next;
};

//AC - 0ms;
struct ListNode* removeNthFromEnd( struct ListNode* head, int n )
{
    struct ListNode *t0 = head, *t1 = head;
    while(n)
        t0 = t0->next, n--;
    if(!t0)
    {
        if(head->next == NULL)
            return NULL;
        else
            return head->next;
    }
    while(t0->next)
    {
        t0 = t0->next;
        t1 = t1->next;
    }
    t1->next = t1->next->next;
    return head;
}
