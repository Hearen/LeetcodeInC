/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-03-06 17:01
Description : A linked list is given such that each node contains an additional random pointer which could point to any node in the list or null.

Return a deep copy of the list.
Source      : https://leetcode.com/problems/copy-list-with-random-pointer/
*******************************************/
#include <stdlib.h>
struct RandomListNode
{
    int label;
    struct RandomListNode *next;
    struct RandomListNode *random;
};

struct Mapper
{
    struct RandomListNode *key;
    struct RandomListNode *value;
};

struct RandomListNode *nodeMaker(struct RandomListNode *node)
{
    struct RandomListNode *t = (struct RandomListNode*)malloc(sizeof(struct RandomListNode));
    t->label = node->label;
    t->next = node->next;
    t->random = node->random;
    return t;
}

//AC - 84ms;
struct RandomListNode *copyRandomList0(struct RandomListNode *head)
{
    if(!head) return NULL;
    struct RandomListNode *newHead = nodeMaker(head);
    struct RandomListNode *t = newHead;
    struct RandomListNode *p = head;
    struct Mapper *dict = (struct Mapper*)malloc(sizeof(struct Mapper));
    int size = 0;
    while(p) //doing the complete copy but the random will be further handled;
    {
        struct RandomListNode *t0 = nodeMaker(p);
        size++;
        dict = (struct Mapper*)realloc(dict, sizeof(struct Mapper)*size); //mapping for later random pointer;
        dict[size-1].key = p;
        dict[size-1].value = t0;
        t->next = t0;
        p = p->next;
        t = t->next;
    }
    p = newHead->next;
    while(p)
    {
        for(int i = 0; i < size; i++)
        {
            if(!p->random) break;
            if(dict[i].key == p->random)
            {
                p->random = dict[i].value;
                break;
            }
        }
        p = p->next;
    }
    return newHead->next;
}

//AC - 24ms;
struct RandomListNode* copyRandomList(struct RandomListNode *head)
{
    if(!head) return NULL;
    struct RandomListNode *newHead=NULL, *oldNode=head, *newNode=NULL;
    while(oldNode) //copy the node and place the new node just after the original one;
    {
        newNode = (struct RandomListNode*)malloc(sizeof(struct RandomListNode));
        newNode->next = oldNode->next;
        newNode->label = oldNode->label;
        newNode->random = NULL;
        oldNode->next = newNode;
        oldNode = oldNode->next->next;
    }
    oldNode = head;
    while(oldNode) //using the adjacent attribute to find the random pointer;
    {
        if(oldNode->random)
            oldNode->next->random = oldNode->random->next;
        oldNode = oldNode->next->next;
    }
    
    newHead = head->next;
    newNode = head->next;
    oldNode = head;
    while(oldNode && oldNode->next) //splitting the two merged list into two independent ones restoring the original list;
    {
        oldNode->next = oldNode->next->next;
        if(oldNode->next == NULL)
        {
            newNode->next = NULL;
            break;
        }
        newNode->next = newNode->next->next;
        newNode = newNode->next;
        oldNode = oldNode->next;
    }
    return newHead;
}
