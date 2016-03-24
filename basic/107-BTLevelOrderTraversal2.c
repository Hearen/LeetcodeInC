/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-02-18 21:06
Description : Given a binary tree, return the bottom-up level order traversal of its nodes' values. (ie, from left to right, level by level from leaf to root).

For example:
Given binary tree {3,9,20,#,#,15,7},
    3
    / \
    9  20
        /  \
        15   7
return its bottom-up level order traversal as:
[
[15,7],
[9,20],
[3]
]
Source      : https://leetcode.com/problems/binary-tree-level-order-traversal-ii/
*******************************************/
struct TreeNode
{
    int val;
    struct TreeNod *left, *right;
};
#include <stdlib.h>
//AC - 0ms;
//finding the depth can avoid reversing process but it will not save cost;
//using high-level language can insert the next array in the front which also can avoid reversing but it may use double queue to achieve that in the background;
//naive solution can be good enough here.
//maybe try to get the depth first can accelerate to some extent;
int** levelOrderBottom(struct TreeNode* root, int** colSize, int* returnSize)
{
    if(!root) return NULL;
    struct TreeNode** queue0 = (struct TreeNode*)malloc(sizeof(struct TreeNode*));
    struct TreeNode** queue1 = (struct TreeNode*)malloc(sizeof(struct TreeNode*));
    int size = 1;
    queue0[0] = root;
    int **arr = (int**)malloc(sizeof(int*)); //before revoking realloc, we have to provide an address first;
    *returnSize = 0;
    while(size)
    {
        *returnSize += 1;
        *colSize = (int*)realloc(*colSize, sizeof(int)*(*returnSize));
        (*colSize)[*returnSize-1] = size;
        arr = (int**)realloc(arr, sizeof(int*)*(*returnSize));
        arr[*returnSize-1] = (int*)malloc(sizeof(int)*size);
        queue1 = (struct TreeNode*)realloc(queue1, sizeof(struct TreeNode*)*2*size);
        int index = 0;
        for(int i = 0; i < size; i++)
        {
            arr[*returnSize-1][i] = queue0[i]->val;
            if(queue0[i]->left)
                queue1[index++] = queue0[i]->left;
            if(queue0[i]->right)
                queue1[index++] = queue0[i]->right;
        }
        struct TreeNode** t = queue0; queue0 = queue1; queue1 = t;
        size = index;
    }
    size = *returnSize;
    for(int i = 0; i < size/2; i++)
    {
        int t0 = (*colSize)[i]; (*colSize)[i]=(*colSize)[size-i-1]; (*colSize)[size-i-1]=t0;
        int *t1 = arr[i]; arr[i]=arr[size-i-1]; arr[size-i-1]=t1;
    }
    return arr;
}

