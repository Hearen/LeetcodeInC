/*******************************************
Author      : LHearen
E-mail      : LHearen@126.com
Time        : Thu, 23 Jun 2016 09:42 CST
Description : Follow up for problem "Populating Next Right Pointers in Each Node".
What if the given tree could be any binary tree? Would your previous solution still work?
Note:
You may only use constant extra space.
For example,
Given the following binary tree,
         1
        /  \
        2    3
        / \    \
        4   5    7
After calling your function, the tree should look like:
1 -> NULL
/  \
2 -> 3 -> NULL
/ \    \
4-> 5 -> 7 -> NULL
Source      : https://leetcode.com/problems/populating-next-right-pointers-in-each-node-ii/
*******************************************/
struct TreeLinkNode
{
    int val;
    TreeLinkNode *left, *right, *next;
    TreeLinkNode(int x): val(x), left(NULL), right(NULL), next(NULL) {}
};
class Solution {
public:
    //Always remember to use header when it comes to collecting linked list;
    //AC - recursive method - 40ms;
    void connect(TreeLinkNode *root) 
    {
        if(!root) return ;
        TreeLinkNode t(0), *cur;
        cur = &t;
        while(root)
        {
            if(root->left)
            {
                cur->next = root->left;
                cur = cur->next;
            }
            if(root->right)
            {
                cur->next = root->right;
                cur = cur->next;
            }
            root = root->next;
        }
        connect(t.next);
    }

    //AC - iterative method - 36ms;
    void connect(TreeLinkNode *root) 
    {
        TreeLinkNode t(0), cur;
        while(root)
        {
            t.next = NULL;
            cur = &t;
            while(root)
            {
                if(root->left)
                {
                    cur->next = root->left;
                    cur = cur->next;
                }
                if(root->right)
                {
                    cur->next = root->right;
                    cur = cur->next;
                }
                root = root->next;
            }
            root = t.next;
        }
    }
};
