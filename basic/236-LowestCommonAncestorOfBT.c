/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-01-19 14:32
Description : Given a binary tree, find the lowest common ancestor (LCA) of two given nodes in the tree.
According to the definition of LCA on Wikipedia: “The lowest common ancestor is defined between two nodes v and w as the lowest node in T that has both v and w as descendants (where we allow a node to be a descendant of itself).”

_______3______
/              \
___5__          ___1__
/      \        /      \
6      _2       0       8
        /  \
        7   4
For example, the lowest common ancestor (LCA) of nodes 5 and 1 is 3. Another example is LCA of nodes 5 and 4 is 5, since a node can be a descendant of itself according to the LCA definition.
Source      : https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-tree/
*******************************************/
struct TreeNode
{
    int val;
    struct TreeNod *left, *right;
};

//AC - 12ms - return the LCA or the node itself;
struct TreeNode* lowestCommonAncestor( struct TreeNode* root, struct TreeNode *p, struct TreeNode* q )
{
    if(!p) return q; //corner case to accelerate from 16ms to 12ms;
    if(!q) return p;
    //the essential part: 1. p or q is the ancestor; 
    //2. p or q are in different sub-trees so the LCA will be in the higher level;
    if(!root || root == p || root == q) return root; 
    struct TreeNode *left = lowestCommonAncestor(root->left, p, q);
    struct TreeNode *right = lowestCommonAncestor(root->right, p, q);
    if(left&&right) return root; //in different sub-trees;
    if(!left) return right; //in the same sub-tree;
    if(!right) return left;
}

