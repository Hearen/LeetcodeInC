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
struct TreeNode
{
    int val;
    struct TreeNode *left, *right;
};

struct TreeNode** generateTrees(int n, int* returnSize)
{

}
