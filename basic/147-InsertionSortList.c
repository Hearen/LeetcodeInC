/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-03-08 21:34
Description : Sort a linked list using insertion sort.
Source      : https://leetcode.com/problems/insertion-sort-list/
*******************************************/
#include <cstdbool.h>
struct ListNode
{
    int val;
    struct ListNode *next;
};

//AC - 12ms;
//if the space is not a constraint, just copying the values to an array and sort them there will be much faster;
struct ListNode* insertionSortList(struct ListNode* head)
{
    if(!head || !head->next) return head; //we have to handle the corner case now, since we adopted last and check head->val the first round;
    struct ListNode* newHead = (struct ListNode*)malloc(sizeof(struct ListNode));
    newHead->next = NULL; //in case of uncertainty;
    newHead->val = head->val-1; //to update the last for the first insertion;
    struct ListNode *p=head, *next, *pre=newHead, *last=newHead;
    while(p)
    {
        next = p->next; //record the next pointer in case of overlapping;
        if(last->val < p->val) //checking the last first to accelerate;
        {
            last->next = p;
            last = p;
        }
        else
        {
            while(pre->next && pre->next->val<p->val)
                pre = pre->next;
            p->next = pre->next; //point to the next node of the current inserting position;
            pre->next = p; 
            pre = newHead; //start over from the very beginning;
        }
        p = next; //move to the next node;
    }
    last->next = NULL;
    return newHead->next;
}
