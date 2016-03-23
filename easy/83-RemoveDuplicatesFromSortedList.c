/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-01-19 11:18
Description : Given a sorted linked list, delete all duplicates such that each element appear only once.
For example,
Given 1->1->2, return 1->2.
Given 1->1->2->3->3, return 1->2->3.
Source      : https://leetcode.com/problems/remove-duplicates-from-sorted-list/
*******************************************/
#include <stdlib.h>
struct ListNode
{
    int val;
    struct ListNode *next;
};

//AC - 4ms;
struct ListNode* deleteDuplicates( struct ListNode* head )
{
    struct ListNode *t = ( struct ListNode* )malloc(sizeof( struct ListNode ));
    struct ListNode *pre = t, *cur = head;
    while(cur)
    {
        if(pre == t || pre->val != cur->val)
        {
            pre->next = cur;
            pre = cur;
            cur = cur->next;
            pre->next = NULL;
        }
        else
            cur = cur->next;
    }
    return t->next;
}
