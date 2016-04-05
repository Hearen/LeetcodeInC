/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2015-12-24 20:00
Description : Sort a linked list in O(n log n) time using constant space complexity.
Source      : https://leetcode.com/problems/sort-list/
*******************************************/
#include<stdio.h>
struct ListNode
{
    int val;
    struct ListNode *next;
};
//AC - 20ms;
struct ListNode* merge(struct ListNode* l, struct ListNode* r)
{
    struct ListNode head;
    struct ListNode* p = &head;
    while(l && r)
    {
        if(l->val <= r->val) //collect left first when left and right are equal;
        {
            p->next = l;
            l = l->next;
        }
        else
        {
            p->next = r;
            r = r->next;
        }
        p = p->next;
    }
    p->next = (l == NULL ? r : l);
    return head.next; //return without the fake head;
}
struct ListNode* sortList(struct ListNode* head)
{
    if(head == NULL || head->next == NULL)
        return head;
    struct ListNode *s1 = head, *s2 = head->next;
    while(s2 && s2->next) //split the list into two halves;
    {
        s1 = s1->next;
        s2 = s2->next->next;
    }
    s2 = s1->next;
    s1->next = NULL;
    return merge(sortList(head), sortList(s2)); //merge two parts by invoking recursive method;
}


struct ListNode* partition(struct ListNode* head, struct ListNode* tail)
{
    if(head == tail || head->next == tail)
        return head;
    int pivot = head->val;
    struct ListNode left, mid, right; //the head of each position;
    struct ListNode *l=&left, *m=&mid, *r=&right; //used to move forward;
    while(head != tail)
    {
        if(head->val < pivot)
        {
            l->next = head;
            l = l->next;
        }
        else if(head->val > pivot)
        {
            r->next = head;
            r = r->next;
        }
        else
        {
            m->next = head;
            m = m->next;
        }
        head = head->next;
    }
    r->next = tail; //connect the right end to the next part;
    m->next = partition(right.next, tail);  //connect the middle part to the right;
    l->next = mid.next; //connect the left to the middle;
    return partition(left.next, l->next); //handle the left part and return the head of the left;
}


//http://www.geeksforgeeks.org/quicksort-on-singly-linked-list/
//AC - 16ms;
struct ListNode* swiftSort(struct ListNode* head)
{
    return partition(head, NULL);
}
