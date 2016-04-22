/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-02-19 19:53
Description : Given a complete binary tree, count the number of nodes.
Definition of a complete binary tree from Wikipedia:
In a complete binary tree every level, except possibly the last, is completely filled, and all nodes in the last level are as far left as possible. It can have between 1 and 2h nodes inclusive at the last level h.
Source      : https://leetcode.com/problems/count-complete-tree-nodes/
*******************************************/
struct TreeNode
{
    int val;
    struct TreeNode *left, *right;
};

//AC - 144ms;
int countNodes0(struct TreeNode* root)
{
    if(!root) return 0;
    int lHeight=0, rHeight=0;
    for(struct TreeNode* l=root; l; l=l->left) lHeight++; //get the height of the left sub-tree;
    for(struct TreeNode* r=root; r; r=r->right) rHeight++; //height of the right sub-tree;
    if(lHeight==rHeight) return (1<<lHeight)-1;  //if it's a complete tree just return;
    return countNodes(root->left)+countNodes(root->right)+1; //if not, calculate both the left and right sub-trees respectively;
}

//AC - 60ms;
int countNodes(struct TreeNode* root)
{
    if(!root) return 0;
    struct TreeNode* p = root;
    int h=0, count=0, level=0;
    while(p) p=p->left, h++; //get the height of the tree;
    p = root;
    level = h - 2; //the amount of levels under the child of the node p;
    while(level > -1)
    {
        struct TreeNode* l = p->left;
        for(int i = 0; i < level; i++) l = l->right;
        if(l) //the tree of the left child is complete;
        {
            p = p->right;
            count += 1<<level; //add the extra nodes in the last level of the left sub-tree;
        }
        else p = p->left; //if the left sub-tree is not complete, then check the left sub-sub-tree of it;
        level--; //decrease the left level accordingly;
    }
    if(p) count++; //when it's a complete tree we need to add the last right node;
    return (1<<(h-1))-1+count; //add the complete sub-tree and the last-level nodes;
}
