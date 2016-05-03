/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-01-28 16:05
Description : You are given an integer array nums and you have to return a new counts array. The counts array has the property where counts[i] is the number of smaller elements to the right of nums[i].

Example:
Given nums = [5, 2, 6, 1]
To the right of 5 there are 2 smaller elements (2 and 1).
To the right of 2 there is only 1 smaller element (1).
To the right of 6 there is 1 smaller element (1).
To the right of 1 there is 0 smaller element.
Return the array [2, 1, 1, 0].
Source      : https://leetcode.com/problems/count-of-smaller-numbers-after-self/
*******************************************/
#include <stdlib.h>
typedef struct MyTreeNode
{
    int val, lessCount, count;
    struct MyTreeNode *left, *right;
} TreeNode;

TreeNode* makeTreeNode(int val)
{
    TreeNode *node = (TreeNode*)malloc(sizeof(TreeNode));
    node->val = val;
    node->lessCount = 0;
    node->count = 1;
    node->left = node->right = NULL;
    return node;
}

//without count for the repeated numbers - 24ms;
void insert0(TreeNode* root, int val, int *lessCount)
{
    if(val < root->val)
    {
        root->lessCount++;
        if(NULL == root->left) root->left = makeTreeNode(val);
        else insert0(root->left, val, lessCount);
    }
    else 
    {
        *lessCount += root->lessCount;
        if(val > root->val) (*lessCount)++;
        if(NULL == root->right) root->right = makeTreeNode(val);
        else insert0(root->right, val, lessCount);
    }
}

//using another member variable to record the count of the 
//repeated numbers which reduces the time from 24ms to 20ms;
void insert(TreeNode* root, int val, int *lessCount)
{
    int curVal = root->val;
    if(val < curVal)
    {
        root->lessCount++;
        if(NULL == root->left) root->left = makeTreeNode(val);
        else insert(root->left, val, lessCount);
    }
    else if(val > curVal)
    {
        *lessCount += root->lessCount + root->count;
        if(NULL == root->right) root->right = makeTreeNode(val);
        else insert(root->right, val, lessCount);
    }
    else
    {
        *lessCount += root->lessCount;
        root->count++;
        return ;
    }
}

//AC - 20ms;
int* countSmaller(int* nums, int size, int* returnSize)
{
    *returnSize = size;
    if(size == 0)
        return NULL;
    int *count = (int*)malloc(sizeof(int)*size);
    memset(count, 0, sizeof(int)*size);
    TreeNode *root = makeTreeNode(nums[size-1]);
    for(int i = size-2; i > -1; i--)
        insert(root, nums[i], count+i);
    return count;
}

