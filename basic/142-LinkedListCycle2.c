/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2015-12-27 15:35
Description : Given a linked list, return the node where the cycle begins. If there is no cycle, return null.
Note: Do not modify the linked list.
Follow up:
Can you solve it without using extra space?
Source      : https://leetcode.com/problems/linked-list-cycle-ii/
*******************************************/
#include <stdio.h>
struct ListNode
{
    int val;
    struct ListNode* next;
};

//AC - 4ms;
struct ListNode* detectCycle(struct ListNode* head)
{
    if(head == NULL || head->next == NULL || head->next->next == NULL)
        return NULL;
    struct ListNode* slow = head->next;
    struct ListNode* fast = head->next->next;
    while(slow != fast)
    {
        slow = slow->next;
        if(fast == NULL || fast->next == NULL)
            break;
        fast = fast->next->next;
    }
    if(fast == NULL || fast->next == NULL)
        return NULL;
    fast = head; 
    while(slow != fast)
    {
        slow = slow->next;
        fast = fast->next;
    }
    return slow;
}
