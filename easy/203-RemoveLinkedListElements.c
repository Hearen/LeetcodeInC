/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-01-22 09:12
Description : Remove all elements from a linked list of integers that have value val.
Example
Given: 1 --> 2 --> 6 --> 3 --> 4 --> 5 --> 6, val = 6
Return: 1 --> 2 --> 3 --> 4 --> 5
Source      : https://leetcode.com/problems/remove-linked-list-elements/
*******************************************/
#include <stdlib.h>
struct ListNode
{
    int val;
    struct ListNode *next;
};
//AC - 12ms;
struct ListNode* removeElements( struct ListNode* head, int val )
{
    struct ListNode *t = ( struct ListNode* )malloc(sizeof( struct ListNode ));
    struct ListNode *pre = t, *cur = head;
    t->next = NULL;
    while(cur)
    {
        if(cur->val != val)
        {
            pre->next = cur;
            pre = pre->next;
        }
        cur = cur->next;
    }
    pre->next = NULL;
    return t->next;
}
