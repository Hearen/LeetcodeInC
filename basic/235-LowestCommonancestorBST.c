/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-01-19 14:10
Description : Given a binary search tree (BST), find the lowest common ancestor (LCA) of two given nodes in the BST.
According to the definition of LCA on Wikipedia: “The lowest common ancestor is defined between two nodes v and w as the lowest node in T that has both v and w as descendants (where we allow a node to be a descendant of itself).”
    _______6______
    /              \
___2__          ___8__
/      \        /      \
0      _4       7       9
    /  \
    3   5
For example, the lowest common ancestor (LCA) of nodes 2 and 8 is 6. Another example is LCA of nodes 2 and 4 is 2, since a node can be a descendant of itself according to the LCA definition.
Source      : https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-search-tree/
*******************************************/
#include <stdlib.h>
struct TreeNode
{
    int val;
    struct TreeNod *left, *right;
};
//AC - 24ms;
struct TreeNode* lowestCommonAncestor2( struct TreeNode* root, struct TreeNode *p, struct TreeNode* q )
{
    if(!p) return q;
    if(!q) return p;
    if(!root || root == p || root == q) return root;
    struct TreeNode *left = lowestCommonAncestor(root->left, p, q);
    struct TreeNode *right = lowestCommonAncestor(root->right, p, q);
    if(left&&right) return root;
    if(!left) return right;
    if(!right) return left;
}


//AC - 20ms;
struct TreeNode* lowestCommonAncestor0( struct TreeNode* root, struct TreeNode *p, struct TreeNode* q )
{
    if(root == NULL || root == p || root == q ||
            (root->val > p->val && root->val < q->val) ||
            (root->val < p->val && root->val > q->val)) return root; //all the possible cases;
    if(root->val > p->val && root->val > q->val) //in the left sub;
        return lowestCommonAncestor(root->left, p, q);
    else //in the right sub;
        return lowestCommonAncestor(root->right, p, q);
}

struct TreeNode* lowestCommonAncestor1( struct TreeNode* root, struct TreeNode *p, struct TreeNode* q )
{
    if(p->val<root->val && q->val<root->val) return lowestCommonAncestor(root->left, p, q);
    else if(p->val>root->val && q->val>root->val) return lowestCommonAncestor(root->right, p, q);
    return root;
}

struct TreeNode* lowestCommonAncestor3( struct TreeNode* root, struct TreeNode *p, struct TreeNode* q )
{
    while(1)
    {
        if(p->val<root->val && q->val<root->val) root = root->left;
        else if(p->val>root->val && q->val>root->val) root = root->right;
        else return root;
    }
}

