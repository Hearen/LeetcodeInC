/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : Mon, 04 Jul 2016 10:51 CST
Description : A linked list is given such that each node contains an additional random pointer which could point to any node in the list or null.
Return a deep copy of the list.
Source      : https://leetcode.com/problems/copy-list-with-random-pointer/
*******************************************/
class Solution {
public:
    RandomListNode *copyRandomList(RandomListNode *head) {
        if(!head) return NULL;
        unordered_map<RandomListNode*, RandomListNode*> node_map;
        RandomListNode *p = head, *pre = NULL, t(0);
        pre = &t;
        while(p)
        {
            pre->next = node_map[p] = new RandomListNode(p->label);
            p = p->next;
            pre = pre->next;
        }
        p = head;
        pre = t.next;
        while(p)
        {
            pre->random = node_map[p->random];
            pre = pre->next;
            p = p->next;
        }
        return t.next;
    }
};
