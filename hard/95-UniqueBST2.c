/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-03-24 09:05
Description : Given n, generate all structurally unique BST's (binary search trees) that store values 1...n.

For example,
Given n = 3, your program should return all 5 unique BST's shown below.

   1         3     3      2      1
   \       /     /      / \      \
    3     2     1      1   3      2
    /     /       \                 \
   2     1         2                 3
Source      : https://leetcode.com/problems/unique-binary-search-trees-ii/
*******************************************/
#include <stdlib.h>
struct TreeNode
{
    int val;
    struct TreeNode *left, *right;
};

struct TreeNode* push(struct TreeNode*** arr, int* returnSize, int a)
{
    struct TreeNode *t = NULL;
    if(a > -1) //only valid value can be allocated;
    {
        t = (struct TreeNode*)malloc(sizeof(struct TreeNode));
        t->left = t->right = NULL;
        t->val = a;
    }
    *returnSize += 1;
    *arr = (struct TreeNode**)realloc(*arr, sizeof(struct TreeNode*)*(*returnSize));
    (*arr)[*returnSize-1] = t;
    return t; //return this node for -> root;
}
struct TreeNode* generate(int begin, int end, int* returnSize)
{
    struct TreeNode** arr = (struct TreeNode**)malloc(sizeof(struct TreeNode*));
    if(begin >= end)
    {
        if(begin > end) 
            push(&arr, returnSize, -1);
        if(begin == end)
            push(&arr, returnSize, begin);
        return arr;
    }
    for(int i = begin; i <= end; i++) //try to set each value as root;
    {
        int count0=0, count1=0;
        struct TreeNode **arr0 = generate(begin, i-1, &count0);
        struct TreeNode **arr1 = generate(i+1, end, &count1);
        for(int j = 0; j < count0; j++) //try to use different node as left and right child;
            for(int k = 0; k < count1; k++)
            {
                struct TreeNode* t = push(&arr, returnSize, i);
                t->left = arr0[j];
                t->right = arr1[k];
            }
    }
    return arr;
}

//AC - 8ms;
struct TreeNode** generateTrees(int n, int* returnSize)
{
    *returnSize = 0;
    if(!n) return NULL;
    return generate(1, n, returnSize);
}
