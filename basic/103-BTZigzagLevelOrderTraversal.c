/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-01-06 19:57
Description : Given a binary tree, return the zigzag level order traversal of its nodes' values. (ie, from left to right, then right to left for the next level and alternate between).
For example:
Given binary tree {3,9,20,#,#,15,7},
    3
    / \
    9  20
        /  \
        15   7
return its zigzag level order traversal as:
[
[3],
[20,9],
[15,7]
]
Source      : https://leetcode.com/problems/binary-tree-zigzag-level-order-traversal/
*******************************************/
#include <stdlib.h>
struct TreeNode
{
    int val;
    struct TreeNode* left;
    struct TreeNode* right;
};
void traverse(struct TreeNode*** stack0, struct TreeNode*** stack1, int top, int*** table, int** colSize, int* count)
{
    if(top < 0)
        return;
    (*count)++;
    *table = (int**)realloc(*table, sizeof(int*)*(*count));
    (*table)[*count-1] = (int*)malloc(sizeof(int)*(top+1));
    *colSize = (int*)realloc(*colSize, sizeof(int)*(*count));
    (*colSize)[*count-1] = top+1;
    if(*count%2)
    {
        for(int i=0; i<=top; i++)
            (*table)[*count-1][i]=(*stack0)[i]->val;
    }
    else
    {
        for(int i=top; i>-1; i--)
            (*table)[*count-1][top-i] = (*stack0)[i]->val;
    }
    int index = -1;
    *stack1 = (struct TreeNode**)realloc(*stack1, sizeof(struct TreeNode*)*2*(top+1));
    for(int i = 0; i <= top; i++)
    {
        if((*stack0)[i]->left != NULL)
            (*stack1)[++index] = (*stack0)[i]->left;
        if((*stack0)[i]->right != NULL)
            (*stack1)[++index] = (*stack0)[i]->right;
    }
    if(index < 0)
        return;
    top = index;
    traverse(stack1, stack0, top, table, colSize, count);
}

//AC - 0ms;
int** zigzagLevelOrder(struct TreeNode* root, int** colSize, int* count)
{
    if(root == NULL)
        return NULL;
    struct TreeNode** stack0 = (struct TreeNode**)malloc(sizeof(struct TreeNode*));
    struct TreeNode** stack1 = (struct TreeNode**)malloc(sizeof(struct TreeNode*));
    *colSize = (int*)malloc(sizeof(int));
    int top = -1;
    stack0[++top] = root;
    int** table = (int**)malloc(sizeof(int*)); 
    *count = 0;
    traverse(&stack0, &stack1, top, &table, colSize, count);
    return table;
}
