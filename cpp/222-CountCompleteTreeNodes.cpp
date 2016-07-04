/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-02-19 19:53
Description : Given a complete binary tree, count the number of nodes.
Definition of a complete binary tree from Wikipedia:
In a complete binary tree every level, except possibly the last, is completely filled, and all nodes in the last level are as far left as possible. It can have between 1 and 2h nodes inclusive at the last level h.
Source      : https://leetcode.com/problems/count-complete-tree-nodes/
*******************************************/
class Solution {
public:
	//recursive method - 112ms;
    int countNodes(TreeNode* root) 
    {
        if(!root) return 0;
        int lCount = 0, rCount = 0;
        for(TreeNode* l = root->left; l; l = l->left) lCount++;
        for(TreeNode* r = root->right; r; r = r->left) rCount++;
        if(lCount > rCount) return countNodes(root->left)+(1<<rCount);
        else return countNodes(root->right)+(1<<lCount);
    }
	
	//iterative method - 100ms;
	int countNodes(TreeNode* root) 
    {
        if(!root) return 0;
        int sum = 0, lCount = 0, rCount = 0;
        while(root)
        {
            lCount = 0, rCount = 0;
            for(TreeNode* l = root->left; l; l = l->left) lCount++;
            for(TreeNode* r = root->right; r; r = r->left) rCount++;
            if(lCount > rCount) root = root->left, sum += (1<<rCount);
            else root = root->right, sum += (1<<lCount);
        }
        return sum;
    }

    //best solution - 72ms;
	int countNodes(TreeNode* root) 
    {
        if(!root) return 0;
        int height = 0, sum = 0, i = 0;
        TreeNode *t = root, *t0 = NULL;
        while(t) t = t->left, height++; //get the height of the tree;
        t = root;
        int level = height - 2; //levels under the child of root;
        while(level > -1) //collect the bottom-level nodes by halving them apart;
        {
            t0 = t->left;
            for(i = 0; i < level; ++i) t0 = t0->right; 
            if(t0) { sum += 1<<level; t = t->right; } //rightmost node is not null;
            else t = t->left;
            level--; //move to the next level;
        }
        if(t) sum++; //if it's a complete tree, collect the last right node;
        return sum+((1<<(height-1))-1);
    }    
};
