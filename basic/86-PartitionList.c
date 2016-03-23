/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-02-24 16:23
Description : Given a linked list and a value x, partition it such that all nodes less than x come before nodes greater than or equal to x.
You should preserve the original relative order of the nodes in each of the two partitions.
For example,
Given 1->4->3->2->5->2 and x = 3,
return 1->2->2->4->3->5.

Source      : https://leetcode.com/problems/partition-list/
*******************************************/
struct ListNode
{
    int val;
    struct ListNode *next;
};
#include <stdlib.h>
struct ListNode* partition(struct ListNode* head, int x)
{
    if(!head) return NULL;
    struct ListNode *less = (struct ListNode*)malloc(sizeof(struct ListNode)); //used as head;
    struct ListNode *greater = (struct ListNode*)malloc(sizeof(struct ListNode));
    struct ListNode *l=less, *g=greater; //used to track the chain for connecting;
    while(head)
    {
        if(head->val < x)
        {
            l->next = head;
            l = l->next;
        }
        else
        {
            g->next = head;
            g = g->next;
        }
        head = head->next;
    }
    g->next = NULL;
    l->next = greater->next;
    return less->next;
}
