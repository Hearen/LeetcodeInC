/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-02-20 08:23
Description : Given an array where elements are sorted in ascending order, convert it to a height balanced BST.
Source      : https://leetcode.com/problems/convert-sorted-array-to-binary-search-tree/
*******************************************/
struct TreeNode
{
    int val;
    struct TreeNode *left, *right;
};
#include <stdlib.h>

//AC - 4ms;
struct TreeNode* sortedArrayToBST(int* nums, int size)
{
    if(!size) return NULL;
    int mid = size>>1; //get the mid from the size; 
    struct TreeNode* root = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    root->val = nums[mid];
    root->left=root->right=NULL;
    if(size==1) return root;
    root->left = sortedArrayToBST(nums, mid);
    root->right = sortedArrayToBST(nums+mid+1, size-mid-1); //if size==1 nums+mid+1 will cross the line and result as error;
    return root;
}
