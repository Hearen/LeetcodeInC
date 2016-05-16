/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-02-19 10:11
Description : Serialization is the process of converting a data structure or object into a sequence of bits so that it can be stored in a file or memory buffer, or transmitted across a network connection link to be reconstructed later in the same or another computer environment.

Design an algorithm to serialize and deserialize a binary tree. There is no restriction on how your serialization/deserialization algorithm should work. You just need to ensure that a binary tree can be serialized to a string and this string can be deserialized to the original tree structure.

For example, you may serialize the following tree

1
/ \
2   3
    / \
    4   5
as "[1,2,3,null,null,4,5]", just the same as how LeetCode OJ serializes a binary tree. You do not necessarily need to follow this format, so please be creative and come up with different approaches yourself.
Source      : https://leetcode.com/problems/serialize-and-deserialize-binary-tree/
Reference   : https://leetcode.com/discuss/91524/very-intuitive-solution-in-c-well-explained
*******************************************/
struct TreeNode
{
    int val;
    struct TreeNode *left, *right;
};

#include <stdlib.h>
#define LEN 20
char* serializeHelper(struct TreeNode* root, int* len)
{
    *len = 2;
    if(!root) return "X,"; //convert null node to X ended with comma;
    char *t = (char*)malloc(sizeof(char)*LEN);
    int size = 0;
    int val = root->val;
    while(val) //invert integer to string;
    {
        t[size++] = val%10 + '0';
        val /= 10;
    }
    for(int i = 0; i < size/2; i++) //revert the string;
    {
        char c = t[size-i-1]; t[size-i-1]=t[i]; t[i]=c;
    }
    t[size++] = ','; //ended with comma as splitter;
    t[size] = '\0';
    int leftLen=0, rightLen=0;
    char *left = serializeHelper(root->left, &leftLen);
    char *right = serializeHelper(root->right, &rightLen);
    *len = size+leftLen+rightLen+2;
    t = (char*)realloc(t, sizeof(char)*(*len));
    strcat(t, left);
    strcat(t, right);
    return  t;
}

//AC - 16ms;
char* serialize(struct TreeNode* root)
{
    int len = 0;
    return serializeHelper(root, &len);
}

//modifying the string pointer is the core of this method;
struct TreeNode* helper(char** s)
{
    if(**s == 'X') return NULL;
    int num = 0;
    while(**s != ',') 
        num = 10*num + *((*s)++) - '0';
    *s += 1; //move the pointer to the start of the left sub-tree;
    struct TreeNode *root = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    root->val = num;
    root->left = helper(s); //the pointer has moved past the left sub-tree;
    while(*((*s)++) != ','); //skip the last number of the left sub-tree, moving the pointer to the start of the right sub-tree;
    root->right = helper(s);
    return root;

}

struct TreeNode* deserialize(char* s)
{
    return helper(&s); //using pointer to the pointer to move the pointer;
}
