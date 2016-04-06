/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-01-20 14:14
Description : Write a program to find the node at which the intersection of two singly linked lists begins.
For example, the following two linked lists:
A:          a1 → a2
                   ↘
                    c1 → c2 → c3
                   ↗            
B:     b1 → b2 → b3
begin to intersect at node c1.
Notes:
If the two linked lists have no intersection at all, return null.
The linked lists must retain their original structure after the function returns.
You may assume there are no cycles anywhere in the entire linked structure.
Your code should preferably run in O(n) time and use only O(1) memory.
Source      : https://leetcode.com/problems/intersection-of-two-linked-lists/
*******************************************/
#include <stdlib.h>
struct ListNode
{
    int val;
    struct ListNode *next;
};

//AC - 32ms - using length difference;
struct ListNode* getIntersectionNode0(struct ListNode* headA, struct ListNode* headB)
{
    int lenA = 0;
    int lenB = 0;
    struct ListNode *t0 = headA;
    struct ListNode *t1 = headB;
    while(t0)
        lenA++, t0 = t0->next;
    while(t1)
        lenB++, t1 = t1->next;
    int difference = 0;
    if(lenA > lenB)
    {
        difference = lenA - lenB;
        t0 = headA;
        t1 = headB;
    }
    else
    {
        difference = lenB - lenA;
        t0 = headB;
        t1 = headA;
    }
    while(difference)
        t0 = t0->next, difference--;
    while(t0)
    {
        if(t0 == t1)
            return t0;
        t0 = t0->next;
        t1 = t1->next;
    }
    return NULL;
}

struct ListNode* getIntersectionNode(struct ListNode* headA, struct ListNode* headB)
{
    if(!headA || !headB) return NULL;
    struct ListNode *p1=headA, *p2=headB;
    while(p1 != p2)
    {
        p1 = p1? p1->next : headB;
        p2 = p2? p2->next : headA;
        if(p1 == p2) return p1;
    }
    return p1;
}
