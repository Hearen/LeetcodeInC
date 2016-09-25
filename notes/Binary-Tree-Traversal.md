
### Preorder Traversal
Given a binary tree, return the preorder traversal of its nodes' values.
```
For example:
Given binary tree {1,#,2,3},
   1
    \
     2
    /
   3
return [1,2,3].
```
Note: Recursive solution is trivial, could you do it iteratively?

[test](https://leetcode.com/problems/binary-tree-preorder-traversal/)

### Solution
Explanation will be added.
#### Recursive
```
class Solution {
private:
    void traverse(TreeNode* root, vector<int>& v) {
        if(!root) return ;
        v.push_back(root->val);
        traverse(root->left, v);
        traverse(root->right, v);
    }
public:
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> v;
        traverse(root, v);
        return v;
    }
};
```
#### Stack
```
vector<int> preorderTraversal(TreeNode* root) {
	vector<int> v;
	if(!root) return v;
	stack<TreeNode*> node_stack;
	TreeNode *t = NULL;
	node_stack.push(root);
	while(!node_stack.empty()) {
		t = node_stack.top();
		node_stack.pop();
		v.push_back(t->val);
		if(t->right) node_stack.push(t->right);
		if(t->left) node_stack.push(t->left);
	}
	return v;
}
```
#### Morris Traversal
```
vector<int> preorderTraversal(TreeNode* root) {
	vector<int> v;
	if(!root) return v;
	TreeNode *pre = NULL;
	while(root) {
		if(!root->left) {
			v.push_back(root->val);
			root = root->right;
		}
		else {
			pre = root->left;
			while(pre->right && pre->right!=root) pre = pre->right;
			if(!pre->right) {
				pre->right = root;
				v.push_back(root->val);
				root = root->left;
			}
			else {
				pre->right = NULL;
				root = root->right;
			}
		}
	}
	return v;
}
```

### Inorder
Given a binary tree, return the inorder traversal of its nodes' values.
```
For example:
Given binary tree [1,null,2,3],
   1
    \
     2
    /
   3
return [1,3,2].
```
Note: Recursive solution is trivial, could you do it iteratively?
[test](https://leetcode.com/problems/binary-tree-inorder-traversal/)
### Solution
#### Recursive

```
class Solution {
private:
    void traverse(TreeNode* root, vector<int>& v) {
        if(!root) return;
        traverse(root->left, v);
        v.push_back(root->val);
        traverse(root->right, v);
    }
public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> v;
        traverse(root, v);
        return v;
    }
};
```

#### Stack

```
vector<int> inorderTraversal(TreeNode* root) {
	vector<int> v;
	if(!root) return v;
	stack<TreeNode*> nodeStack;
	while(root || !nodeStack.empty()) {
		while(root) {
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
```

#### Morris Traversal

```
vector<int> inorderTraversal(TreeNode* root) {
	vector<int> v;
	while(root) {
		if(!root->left) {
			v.push_back(root->val);
			root = root->right;
		}
		else {
			TreeNode *pre = root->left;
			while(pre->right && pre->right!=root) pre = pre->right;
			if(!pre->right) {
				pre->right = root;
				root = root->left;
			}
			else {
				v.push_back(root->val);
				root = root->right;
				pre->right = NULL;
			}
		}
	}
	return v;
}
```
### Binary Tree Postorder Traversal
Given a binary tree, return the postorder traversal of its nodes' values.
For example:
Given binary tree {1,#,2,3},
```
   1
    \
     2
    /
   3
```
return [3,2,1].
[test](https://leetcode.com/problems/binary-tree-postorder-traversal/)
### Solution
#### Recursive
```
class Solution {
    void traverse(TreeNode* root, vector<int>& v){
        if(!root) return ;
        traverse(root->left, v);
        traverse(root->right, v);
        v.push_back(root->val);
    }
public:
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> v;
        traverse(root, v);
        return v;
    }
};
```
#### Pre-order-similar traversing
```
vector<int> postorderTraversal(TreeNode* root) {
    vector<int> v;
    while(root) {
        if(!root->right) {
            v.push_back(root->val);
            root = root->left;
        }
        else {
            TreeNode *pre = root->right;
            while(pre->left && pre->left!=root) pre = pre->left;
            if(!pre->left) {
                pre->left = root;
                v.push_back(root->val);
                root = root->right;
            }
            else {
                pre->left = NULL;
                root = root->left;
            }
        }
    }
    reverse(v.begin(), v.end());
    return v;
}
```

### Iterative 

```
vector<int> postorderTraversal(TreeNode* root) {
    if(!root) return vector<int>();
    stack<TreeNode*> node_stack;
    vector<int> v;
    node_stack.push(root);
    TreeNode *pre = NULL, *cur = NULL;
    while(!node_stack.empty()) {
        cur = node_stack.top();
        if(!pre || pre->left==cur || pre->right==cur) {
            if(cur->left) node_stack.push(cur->left);
            else if(cur->right) node_stack.push(cur->right);
            else { v.push_back(cur->val); node_stack.pop();  }
        }
        else if(cur->left == pre) {
            if(cur->right) node_stack.push(cur->right);
            else { v.push_back(cur->val); node_stack.pop();  }
        }
        else if(cur->right == pre) {
            v.push_back(cur->val);
            node_stack.pop();
        }
        pre = cur;
    }
    return v;
}
```
