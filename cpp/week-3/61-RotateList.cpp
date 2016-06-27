/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : Mon, 27 Jun 2016 21:04 CST
Description : Given a list, rotate the list to the right by k places, where k is non-negative.
For example:
Given 1->2->3->4->5->NULL and k = 2,
return 4->5->1->2->3->NULL.
Source      : https://leetcode.com/problems/rotate-list/
*******************************************/
class Solution {
public:
    ListNode* rotateRight(ListNode* head, int k) 
    {
        if(!head) return head;
        int len = 1;
        ListNode *p = head;
        while(p->next)
        {
            p = p->next;
            len++;
        }
        p->next = head; //connecting to form a circle;
        if(k %= len)
            for(int i = 0; i < len-k; ++i) p = p->next;
        ListNode *newHead = p->next;
        p->next = NULL;
        return newHead;
    }
};
