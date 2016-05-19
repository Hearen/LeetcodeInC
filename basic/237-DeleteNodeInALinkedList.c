/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-01-14 16:29
Description : Write a function to delete a node (except the tail) in a singly linked list, given only access to that node.
Supposed the linked list is 1 -> 2 -> 3 -> 4 and you are given the third node with value 3, the linked list should become 1 -> 2 -> 4 after calling your function.
Source      : https://leetcode.com/problems/delete-node-in-a-linked-list/
*******************************************/
#include <stdlib.h>
struct ListNode
{
    int val;
    struct ListNode *next;
};

//AC - 4ms - since there is no constraint that we cannot modify the struct;
void deleteNode0( struct ListNode* node )
{
    if(!node) node = NULL; //handle corner case;
    node->val = node->next->val;
    node->next = node->next->next;
}

//AC - 4ms - take advantage of pointer;
void deleteNode( struct ListNode* node )
{
    *node = *(node->next);  //modify the content node points to directly;
}
