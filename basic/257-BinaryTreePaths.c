/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-01-14 16:42
Description : Given a binary tree, return all root-to-leaf paths.
For example, given the following binary tree:
   1
/   \
2     3
\
5
All root-to-leaf paths are:
["1->2->5", "1->3"]
Source      : https://leetcode.com/problems/binary-tree-paths/
*******************************************/
#include <stdlib.h>
#define LEN 1000
struct TreeNode
{
    int val;
    struct TreeNod *left, *right;
};
void traverse( struct TreeNode* root, struct TreeNode** stack, int top, char** sArr, int* count )
{
    if(!root->left && !root->right) //reaching the leaf node, let's collect now;
    {
        sArr[*count] = (char*)malloc(sizeof(char)*LEN);
        sArr[*count][0] = '\0';
        int i = 0;
        char* s = (char*)malloc(sizeof(char)*30);
        for(; i < top; i++)
        {
            snprintf(s, 30, "%d", stack[i]->val);
            strcat(sArr[*count], s);
            strcat(sArr[*count], "->");
        }
        snprintf(s, 30, "%d", stack[i]->val);
        strcat(sArr[*count], s);
        (*count)++;
    }
    else //not the leaf, inner node;
    {
        if(root->left)
        {
            stack[top+1] = root->left;
            traverse(root->left, stack, top+1, sArr, count);
        }
        if(root->right)
        {
            stack[top+1] = root->right;
            traverse(root->right, stack, top+1, sArr, count);
        }
    }
}

//AC - 4ms;
char** binaryTreePaths( struct TreeNode* root, int* returnSize )
{
    if(root == NULL) return NULL;
    int top = -1;
    struct TreeNode **stack = ( struct TreeNode **)malloc(sizeof( struct TreeNode *)*LEN);
    stack[++top] = root;
    char** ss = (char**)malloc(sizeof(char*)*LEN);
    traverse(root, stack, top, ss, returnSize);
    return ss;
}
