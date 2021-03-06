/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-01-19 10:54
Description : Given a singly linked list, group all odd nodes together followed by the even nodes. Please note here we are talking about the node number and not the value in the nodes.
You should try to do it in place. The program should run in O(1) space complexity and O(nodes) time complexity.
Example:
Given 1->2->3->4->5->NULL,
return 1->3->5->2->4->NULL.
Note:
The relative order inside both the even and odd groups should remain as it was in the input. 
The first node is considered odd, the second node even and so on ...
Source      : https://leetcode.com/problems/odd-even-linked-list/
*******************************************/
#include <stdlib.h>
struct ListNode
{
    int val;
    struct ListNode *next;
};
//AC - 4ms;
struct ListNode* oddEvenList( struct ListNode* head )
{
    if(head == NULL || head->next == NULL)
        return head;
    struct ListNode *odd = head;
    struct ListNode *even = head->next;
    struct ListNode *eHead = even;
    while(odd && even && even->next)
    {
        odd->next = even->next;
        odd = odd->next;
        even->next = odd->next;
        even = even->next;
    }
    odd->next = eHead;
    return head;
}
