/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-02-20 09:16
Description : Implement an iterator over a binary search tree (BST). Your iterator will be initialized with the root node of a BST.
Calling next() will return the next smallest number in the BST.
Note: next() and hasNext() should run in average O(1) time and uses O(h) memory, where h is the height of the tree.
Source      : https://leetcode.com/problems/binary-search-tree-iterator/
*******************************************/
#include <cstdbool.h>
struct TreeNode
{
    int val;
    struct TreeNode *left, *right;
};

#define LEN 100
struct BSTIterator
{
    struct TreeNode** stack;
    int size;
};

void collectLeft(struct TreeNode* root, struct BSTIterator* t)
{
    for(struct TreeNode* l=root; l; l=l->left)
        t->stack[(t->size)++] = l;
}

//AC - 16ms; - using a fixed size is better in this case - removing realloc method;
//AC - 12ms;
struct BSTIterator* bstIteratorCreate(struct TreeNode* root)
{
    struct BSTIterator* t = (struct BSTIterator*)malloc(sizeof(struct BSTIterator));
    t->stack = (struct TreeNode**)malloc(sizeof(struct TreeNode*)*LEN);
    t->size = 0;
    collectLeft(root, t);
    return t;
}

bool bstIteratorHasNext(struct BSTIterator* iter)
{
    return iter->size;
}

int bstIteratorNext(struct BSTIterator* iter)
{
    int ret = iter->stack[iter->size-1]->val;
    collectLeft(iter->stack[iter->size-1]->right, iter); //since the current node is being popped, collecting the next bigger part - its right children;
    iter->size--;
    return ret;
}

void bstIteratorFree(struct BSTIterator* iter)
{
    free(iter->stack);
    free(iter);
}
