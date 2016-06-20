/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-02-19 15:39
Description : Given a binary tree, return the inorder traversal of its nodes' values.

For example:
Given binary tree {1,#,2,3},
   1
    \
    2
    /
   3
return [1,3,2].

Note: Recursive solution is trivial, could you do it iteratively?
Source      :https://leetcode.com/problems/binary-tree-inorder-traversal/
*******************************************/
class Solution {
private:
    void traverse(TreeNode* root, vector<int>& v)
    {
        if(!root) return;
        traverse(root->left, v);
        v.push_back(root->val);
        traverse(root->right, v);
    }
public:
    //AC - recursive method;
    vector<int> inorderTraversal(TreeNode* root) 
    {
        vector<int> v;
        traverse(root, v);
        return v;
    }
    
    //AC - iterative method;
    vector<int> inorderTraversal(TreeNode* root) 
    {
        vector<int> v;
        if(!root) return v;
        stack<TreeNode*> nodeStack;
        while(root || !nodeStack.empty())
        {
            while(root)
            {
                nodeStack.push(root);
                root = root->left;
            }
            root = nodeStack.top();
            nodeStack.pop();
            v.push_back(root->val);
            root = root->right;
        }
        return v;
    }

    //AC - Morris Traversal;
    vector<int> inorderTraversal(TreeNode* root) 
    {
        vector<int> v;
        while(root)
        {
            if(!root->left)
            {
                v.push_back(root->val);
                root = root->right;

            }
            else
            {
                TreeNode *pre = root->left;
                while(pre->right && pre->right!=root) pre = pre->right;
                if(!pre->right)
                {
                    pre->right = root;
                    root = root->left;
                }
                else
                {
                    v.push_back(root->val);
                    root = root->right;
                    pre->right = NULL;
                }
            }
        }
        return v;
    }
};
