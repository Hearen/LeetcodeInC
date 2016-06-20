/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : 2016-02-19 16:17
Description : Given a binary tree, return the preorder traversal of its nodes' values.
For example:
Given binary tree {1,#,2,3},
   1
    \
    2
    /
    3
return [1,2,3].
Note: Recursive solution is trivial, could you do it iteratively?
Source      : https://leetcode.com/problems/binary-tree-preorder-traversal/
*******************************************/
class Solution {
private:
    void traverse(TreeNode* root, vector<int>& v)
    {
        if(!root) return ;
        v.push_back(root->val);
        traverse(root->left, v);
        traverse(root->right, v);
    }
public:
    //AC - recursive method;
    vector<int> preorderTraversal(TreeNode* root) 
    {
        vector<int> v;
        traverse(root, v);
        return v;
    }

    //AC - using stack to do iteratively;
    vector<int> preorderTraversal(TreeNode* root) 
    {
        vector<int> v;
        if(!root) return v;
        stack<TreeNode*> nodeStack;
        nodeStack.push(root);
        while(!nodeStack.empty())
        {
            root = nodeStack.top();
            nodeStack.pop();
            v.push_back(root->val);
            if(root->right) nodeStack.push(root->right);
            if(root->left) nodeStack.push(root->left);
        }
        return v;
    }

    //AC - Morris Traversal;
    vector<int> preorderTraversal(TreeNode* root) 
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
                    v.push_back(root->val);
                    root = root->left;
                }
                else
                {
                    pre->right = NULL;
                    root = root->right;
                }
            }
        }
        return v;
    }
};

