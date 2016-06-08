/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : Wed, 08 Jun 2016 15:23 CST
Description : Given a binary tree, determine if it is a valid binary search tree (BST).

Assume a BST is defined as follows:

The left subtree of a node contains only nodes with keys less than the node's key.
The right subtree of a node contains only nodes with keys greater than the node's key.
Both the left and right subtrees must also be binary search trees.
Example 1:
2
/ \
1   3
Binary tree [2,1,3], return true.
Example 2:
1
/ \
2   3
Binary tree [1,2,3], return false.
Source      : https://leetcode.com/problems/validate-binary-search-tree/
*******************************************/
class Solution {
private:
    bool valid(TreeNode* root, long lower, long upper)
    {
        if(!root) return true;
        if(root->val<=lower || root->val>=upper) return false;
        if(valid(root->left, lower, root->val) && valid(root->right, root->val, upper)) return true;
        return false;
    }
public:
    //recursive with trick;
    bool isValidBST(TreeNode* root) 
    {
        return valid(root, (long)INT_MIN-1, (long)INT_MAX+1);
    }

    //Mrris Traversal;
    bool isValidBST(TreeNode* root) 
    {
        if(!root) return true;
        int cur = 0; 
        long prev = (long)INT_MIN-1;
        bool flag = true; //using flag here to record the status to avoid return too early without restoring the tree which will cause Runtime Error.
        while(root)
        {
            if(!root->left)
            {
                cur = root->val;
                root = root->right;
                if(cur <= prev) flag =  false;
                prev = cur;
            }
            else
            {
                TreeNode* pre = root->left;
                while(pre->right && pre->right!=root)
                pre = pre->right;
                if(!pre->right)
                {
                    pre->right = root;  
                    root = root->left;
                }
                else
                {
                    pre->right = NULL;  //restore the tree;
                    cur = root->val;
                    root = root->right;
                    if(cur <= prev) flag = false;
                    prev = cur;
                }
            }
        }
        return flag;
    }
};
