/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-02-19 08:56
Description : Given a binary tree containing digits from 0-9 only, each root-to-leaf path could represent a number.

An example is the root-to-leaf path 1->2->3 which represents the number 123.

Find the total sum of all root-to-leaf numbers.

For example,

1
/ \
2   3
The root-to-leaf path 1->2 represents the number 12.
The root-to-leaf path 1->3 represents the number 13.

         Return the sum = 12 + 13 = 25.
Source      : https://leetcode.com/problems/sum-root-to-leaf-numbers/
*******************************************/
struct TreeNode
{
    int val;
    struct TreeNode *left, *right;
};
void traverse(struct TreeNode* root, struct TreeNode** stack, int* size, int* sum)
{
    if(!root->left && !root->right)
    {
        int t = (*stack)[0].val; 
        for(int i=1; i < *size; i++)
            t = 10*t + (*stack)[i].val;
        *sum += t;
    }
    if(root->left)
    {
        *size += 1;
        *stack = (struct TreeNode*)realloc(*stack, sizeof(struct TreeNode)*(*size));
        (*stack)[*size-1] = *(root->left);
        traverse(root->left, stack, size, sum);
        *size -= 1;
    }
    if(root->right)
    {
        *size += 1;
        *stack = (struct TreeNode*)realloc(*stack, sizeof(struct TreeNode)*(*size));
        (*stack)[*size-1] = *(root->right);
        traverse(root->right, stack, size, sum);
        *size -= 1;
    }
}
//AC - 0ms;
int sumNumbers0(struct TreeNode* root)
{
    if(!root) return 0;
    int sum = 0;
    struct TreeNode* stack = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    int size = 1;
    stack[size-1] = *root;
    traverse(root, &stack, &size, &sum);
    return sum;
}

//AC - 4ms;
int treeSum0(struct TreeNode* root, int x)
{
    int cur = 10*x+root->val;
    if(!root->left && !root->right) return cur;
    int ret = 0;
    if(root->left) ret += treeSum(root->left, cur);
    if(root->right) ret += treeSum(root->right, cur);
    return ret;
}

//AC - 0ms;
int treeSum(struct TreeNode* root, int x)
{
    if(!root) return 0;
    int cur = 10*x+root->val;
    if(!root->left && !root->right) return cur;
    return treeSum(root->left, cur)+treeSum(root->right, cur);
}
int sumNumbers(struct TreeNode* root)
{
    if(!root) return 0;
    return treeSum(root, 0);
}
