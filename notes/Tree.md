Tue Sep 13 21:21:51 CST 2016

By LHearen

 - [In-order traversal](http://lhearen.top/2016/07/09/Tree/)
 - [Binary Tree Postorder Traversal](http://lhearen.top/2016/07/09/Tree/)
 - [Serialize and Deserialize Binary Tree](http://lhearen.top/2016/07/09/Tree/)
 - [Unique Binary Search Trees II](http://lhearen.top/2016/07/09/Tree/)
 - [Construct Binary Tree from Preorder and Inorder Traversal](http://lhearen.top/2016/07/09/Tree/)
 - [Construct Binary Tree from Preorder and Inorder Traversal](http://lhearen.top/2016/07/09/Tree/)
 - [Balanced Binary Tree](http://lhearen.top/2016/07/09/Tree/)
 - [Lowest Common Ancestor of a Binary Tree](http://lhearen.top/2016/07/09/Tree/)
 - [LCA in BST](http://lhearen.top/2016/07/09/Tree/)
 - [Symmetric Tree](http://lhearen.top/2016/07/09/Tree/)
 - [Recover Binary Search Tree](http://lhearen.top/2016/07/09/Tree/)
 - [Binary Search Tree Iterator](http://lhearen.top/2016/07/09/Tree/)
 - [Binary Tree Maximum Path Sum](http://lhearen.top/2016/07/09/Tree/)
 - [Populating Next Right Pointers in Each Node II](http://lhearen.top/2016/07/09/Tree/)
 - [Path Sum II](http://lhearen.top/2016/07/09/Tree/)
 - [House Robber III](http://lhearen.top/2016/07/09/Tree/)
 - [Kth Smallest Element in a BST](http://lhearen.top/2016/07/09/Tree/)
 - [Invert Binary Tree](http://lhearen.top/2016/09/13/Invert-Binary-Tree/)
 - [Validate Binary Search Tree](http://lhearen.top/2016/09/13/Validate-Binary-Search-Tree/)
 - [Minimum Depth of Binary Tree](http://lhearen.top/2016/09/13/Minimum-Depth-of-Binary-Tree/)
 - [Flatten Binary Tree to Linked List](http://lhearen.top/2016/09/13/Flatten-Binary-Tree-to-Linked-List/)
 - [Binary Tree Paths](http://lhearen.top/2016/09/13/Binary-Tree-Paths/)
 - [Binary Tree Right Side View](http://lhearen.top/2016/09/13/Binary-Tree-Right-Side-View/)
 - [Count Complete Tree Nodes](http://lhearen.top/2016/08/18/Count-Complete-Tree-Nodes/)
 - [Count Univalue Subtrees](http://lhearen.top/2016/09/14/Count-Univalue-Subtrees/)
 - [Binary Tree Longest Consecutive Sequence](http://lhearen.top/2016/09/14/Binary-Tree-Longest-Consecutive-Sequence/)
 - [Verify Preorder Serialization of a Binary Tree](http://lhearen.top/2016/07/12/Verify-Preorder-Serialization-of-a-Binary-Tree/)
 - [Verify Preorder Sequence in Binary Search Tree](http://lhearen.top/2016/09/14/Verify-Preorder-Sequence-in-Binary-Search-Tree/)
 - [Closest Binary Search Tree Value](http://lhearen.top/2016/09/14/Closest-Binary-Search-Tree-Value/)
 - [Largest BST Subtree](http://lhearen.top/2016/09/14/Largest-BST-Subtree/)
 - [Find Leaves of Binary Tree](http://lhearen.top/2016/09/14/Find-Leaves-of-Binary-Tree/)
 - [Binary Tree Upside Down](http://lhearen.top/2016/09/14/Binary-Tree-Upside-Down/)


### General
Tree represents nodes connected by edges. We'll going to discuss binary tree or binary search tree specifically.

Binary Tree is a special data structure used for data storage purposes. A binary tree has a special condition that each node can have two children at maximum. A binary tree have benefits of both an ordered array and a linked list as search is as quick as in sorted array and insertion or deletion operation are as fast as in linked list.

### Examples

#### In-order traversal

Recursive

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

Iterative using stack

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

Iterative using Morris Traversal

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

#### Binary Tree Postorder Traversal
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

Using pre-order-similar traversing and then reverse the result
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

Typical original iterative method

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

#### Serialize and Deserialize Binary Tree
Serialization is the process of converting a data structure or object into a sequence of bits so that it can be stored in a file or memory buffer, or transmitted across a network connection link to be reconstructed later in the same or another computer environment.  
Design an algorithm to serialize and deserialize a binary tree. There is no restriction on how your serialization/deserialization algorithm should work. You just need to ensure that a binary tree can be serialized to a string and this string can be deserialized to the original tree structure.
For example, you may serialize the following tree
```
    1
   / \
  2   3
     / \
    4   5
```
as "[1,2,3,null,null,4,5]", just the same as how LeetCode OJ serializes a binary tree. You do not necessarily need to follow this format, so please be creative and come up with different approaches yourself.
Note: Do not use class member/global/static variables to store states. Your serialize and deserialize algorithms should be stateless.

```
class Codec {
private:
    void serialize(TreeNode* root, ostringstream& out) {
        if (root) {
            out << root->val << ' ';
            serialize(root->left, out);
            serialize(root->right, out);
        } 
        else { out << "# "; }
    }
    TreeNode* deserialize(istringstream& in) {
        string val;
        in >> val;
        if (val == "#")
            return nullptr;
        TreeNode* root = new TreeNode(stoi(val));
        root->left = deserialize(in);
        root->right = deserialize(in);
        return root;
    }
public:
    string serialize(TreeNode* root) {
        ostringstream out;
        serialize(root, out);
        return out.str();
    }
    TreeNode* deserialize(string data) {
        istringstream in(data);
        return deserialize(in);
    }
};
```

#### Unique Binary Search Trees II
Given an integer n, generate all structurally unique BST's (binary search trees) that store values 1...n.  
For example,
Given n = 3, your program should return all 5 unique BST's shown below.
```
   1         3     3      2      1
    \       /     /      / \      \
     3     2     1      1   3      2
    /     /       \                 \
   2     1         2                 3
```
```
class Solution {
private:
    vector<TreeNode*> generateTrees(int begin, int end)
    {
        vector<TreeNode*> v0, v1, v2;
        if(end <= begin) {
            TreeNode* root;
            root = end==begin? new TreeNode(end) : NULL;
            v0.push_back(root);
            return v0;
        }
        for(int i = begin; i <= end; ++i) {
            v1 = generateTrees(begin, i-1);
            v2 = generateTrees(i+1, end);
            for(auto& l: v1) {
                for(auto& r: v2) {
                    TreeNode* root = new TreeNode(i);
                    root->left = l;
                    root->right = r;
                    v0.push_back(root);
                }
            }
        }
        return v0;
    }
public:
    vector<TreeNode*> generateTrees(int n) {
        if(!n) return vector<TreeNode*>();
        return generateTrees(1, n);
    }
};
```

##### Count the unique
```
int numTrees(int n) {
    if(!n) return 1;
    if(n == 1) return 1; 
    int trees[n+1]{0};
    trees[0] = trees[1] = 1;
    for(int i = 2; i <= n; ++i) {
        for(int j = 0; j < i; ++j)
            trees[i] += trees[j]*trees[i-j-1];
    }
    return trees[n];
}
```

### Classic
#### Construct Binary Tree from Preorder and Inorder Traversal
Given preorder and inorder traversal of a tree, construct the binary tree.  
> Note: You may assume that duplicates do not exist in the tree.
```
class Solution {
private:
    TreeNode* buildTree(const vector<int>& preorder, int p_l, int p_h, const vector<int>& inorder, int i_l, int i_h) {
        if(i_l > i_h) return NULL;
        int val = preorder[p_l];
        TreeNode *root = new TreeNode(val);
        int i = i_l;
        for(; i <= i_h; i++)
            if(inorder[i] == val) break;
        root->left = buildTree(preorder, p_l+1, p_l+i-i_l, inorder, i_l, i-1);
        root->right = buildTree(preorder, p_l+i-i_l+1, p_h, inorder, i+1, i_h);
        return root;
    }
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        return buildTree(preorder, 0, preorder.size()-1, inorder, 0, inorder.size()-1);
    }
};
```
#### Construct Binary Tree from Preorder and Inorder Traversal
Given preorder and inorder traversal of a tree, construct the binary tree.  
Note:
You may assume that duplicates do not exist in the tree.

```
class Solution {
private:
    TreeNode* buildTree(const vector<int>& preorder, int p_l, int p_h, const vector<int>& inorder, int i_l, int i_h) {
        if(i_l > i_h) return NULL;
        int val = preorder[p_l];
        TreeNode *root = new TreeNode(val);
        int i = i_l;
        for(; i <= i_h; i++)
            if(inorder[i] == val) break;
        root->left = buildTree(preorder, p_l+1, p_l+i-i_l, inorder, i_l, i-1);
        root->right = buildTree(preorder, p_l+i-i_l+1, p_h, inorder, i+1, i_h);
        return root;
    }
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        return buildTree(preorder, 0, preorder.size()-1, inorder, 0, inorder.size()-1);
    }
};
```

#### Balanced Binary Tree
Given a binary tree, determine if it is height-balanced.  For this problem, a height-balanced binary tree is defined as a binary tree in which the depth of the two subtrees of every node never differ by more than 1.

Actually we can return different types of values to accelerate the checking process.
```
class Solution {
private:
    int height(TreeNode* root) {
        if(!root) return 0;
        int l = height(root->left), r = height(root->right);
        if(l==-1 || r==-1 || abs(l-r)>1) return -1;
        return max(l, r)+1;
    }
public:
    bool isBalanced(TreeNode* root) {
        return height(root) != -1;
    }
};
```


#### Lowest Common Ancestor of a Binary Tree
Given a binary tree, find the lowest common ancestor (LCA) of two given nodes in the tree.  
According to the definition of LCA on Wikipedia: “The lowest common ancestor is defined between two nodes v and w as the lowest node in T that has both v and w as descendants (where we allow a node to be a descendant of itself).” 
```
        _______3______
       /              \
    ___5__          ___1__
   /      \        /      \
   6      2       0       8
         /  \
         7   4
```
For example, the lowest common ancestor (LCA) of nodes 5 and 1 is 3. Another example is LCA of nodes 5 and 4 is 5, since a node can be a descendant of itself according to the LCA definition.

```
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if(!root || root==p || root==q) return root;
        TreeNode *l = lowestCommonAncestor(root->left, p, q);
        TreeNode *r = lowestCommonAncestor(root->right, p, q);
        if(l&&r) return root;
        if(l) return l;
        if(r) return r;
        return NULL;
}
```
##### LCA in BST
```
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
	if(!root || root==p || root==q) return root;
	if(root->val>p->val && root->val>q->val) return lowestCommonAncestor(root->left, p, q);
	else if(root->val<p->val && root->val<q->val) return lowestCommonAncestor(root->right, p, q);
	else return root;
}
```

### Applications

#### Symmetric Tree
Given a binary tree, check whether it is a mirror of itself (ie, symmetric around its center).
For example, this binary tree [1,2,2,3,4,4,3] is symmetric: 
```
    1
   / \
  2   2
 / \ / \
3  4 4  3
```
But the following [1,2,2,null,3,null,3] is not:
```
    1
   / \
  2   2
   \   \
   3    3
```
Note:
Bonus points if you could solve it both recursively and iteratively.

Recursive

```
class Solution {
private:
    bool equal(TreeNode* l, TreeNode* r) {
        if(!l || !r) { if(!l && !r) return true; return false; }
        return l->val==r->val && equal(l->right, r->left) && equal(l->left, r->right);
    }
public:
    bool isSymmetric(TreeNode* root) {
        if(!root) return true;
        return equal(root->left, root->right);
    }
};
```

Iterative
```
bool isSymmetric(TreeNode* root) {
    if(!root) return true;
    vector<TreeNode*> l, r;
    l.push_back(root->left);
    r.push_back(root->right);
    while(!l.empty()) {
        vector<TreeNode*> l0, r0;
        int size = l.size();
        for(int i = 0; i < size; ++i)
        {
            if(!l[i] || !r[size-i-1]) {
                if(!l[i] && !r[size-i-1]) continue;
                return false;
            }
            if(l[i]->val != r[size-i-1]->val) return false;
            l0.push_back(l[i]->left);
            l0.push_back(l[i]->right);
            r0.push_back(r[size-i-1]->right); //its the `size-i-1` checked before
            r0.push_back(r[size-i-1]->left);
        }
        reverse(r0.begin(), r0.end()); //collected in the reverse direction before
        l = l0;
        r = r0;
    }
    return true;
}
```

#### Recover Binary Search Tree
Two elements of a binary search tree (BST) are swapped by mistake.  
Recover the tree without changing its structure.  
Note:
A solution using O(n) space is pretty straight forward. Could you devise a constant space solution?

An intuitive recursive solution using `reference to pointer`. Here is one thing should remember, never use a `uncertain` pointer. If it's uncertain, make it certain then.
```
class Solution {
private:
    void traverse(TreeNode* root, TreeNode*& pre, TreeNode*& first, TreeNode*& second) {
        if(!root) return ;
        traverse(root->left, pre, first, second);
        if(pre && pre->val>root->val) {
            if(!first) first = pre;
            second = root;
        }
        pre = root;
        traverse(root->right, pre, first, second);
    }
public:
    void recoverTree(TreeNode* root) {
        TreeNode *first = NULL, *second = NULL, *pre = NULL;
        traverse(root, pre, first, second);
        if(first) swap(first->val, second->val);
    }
};
```

Morris version

```
void recoverTree(struct TreeNode* root) {
	TreeNode *pre=NULL, *first=NULL, *second=NULL;
	while(root) {
		if(!root->left) {
			if(pre && pre->val > root->val) {
				if(!first) first = pre;
				second = root;
			}
			pre = root;
			root = root->right;
		}
		else {
			TreeNode *t = root->left;
			while(t->right && t->right!=root) t = t->right;
			if(!t->right) {
				t->right = root;
				root = root->left;
			}
			else {
				t->right = NULL;
				if(pre && pre->val > root->val) {
					if(!first) first = pre;
					second = root;
				}
				pre = root;
				root = root->right;
			}
		}
	}
	if(first) swap(first->val, second->val);
}
```

#### Binary Search Tree Iterator
Implement an iterator over a binary search tree (BST). Your iterator will be initialized with the root node of a BST.  Calling next() will return the next smallest number in the BST.  
Note: next() and hasNext() should run in average O(1) time and uses O(h) memory, where h is the height of the tree.

```
class BSTIterator {
private:    
    stack<TreeNode*> node_stack;
public:
    BSTIterator(TreeNode *root) {
        while(root) {
            node_stack.push(root);
            root = root->left;
        }
    }

    /** @return whether we have a next smallest number */
    bool hasNext() {
        return !node_stack.empty();
    }

    /** @return the next smallest number */
    int next() { TreeNode *t = node_stack.top();
        node_stack.pop();
        int ret = t->val;
        t = t->right;
        while(t) {
            node_stack.push(t);
            t = t->left;
        }
        return ret;
    }
};
```

#### Binary Tree Maximum Path Sum
Given a binary tree, find the maximum path sum.
For this problem, a path is defined as any sequence of nodes from some starting node to any node in the tree along the parent-child connections. The path does not need to go through the root.
For example:
Given the below binary tree,
```
       1
      / \
     2   3
```
Return 6.

```
class Solution {
private:
    int traverse(TreeNode* root, int& maxSum) {
        if(!root) return 0;
        int lMax = max(0, traverse(root->left, maxSum));
        int rMax = max(0, traverse(root->right, maxSum));
        maxSum = max(maxSum, lMax+rMax+root->val);
        return root->val+max(lMax, rMax);
    }
public:
    int maxPathSum(TreeNode* root) {
        int maxSum = INT_MIN;
        traverse(root, maxSum);
        return maxSum;
    }
};
```

#### Populating Next Right Pointers in Each Node II
Follow up for problem "Populating Next Right Pointers in Each Node".  What if the given tree could be any binary tree? Would your previous solution still work?  
Note: 
You may only use constant extra space.
For example,
Given the following binary tree,
```
     1
   /  \
  2    3
 / \    \
4   5    7
```
After calling your function, the tree should look like:
```
     1 -> NULL
   /  \
  2 -> 3 -> NULL
 / \    \
4-> 5 -> 7 -> NULL
```

Recursive 

```
void connect(TreeLinkNode *root) {
    if(!root) return ;
    TreeLinkNode newHead(0), *t = NULL;
    t = &newHead;
    while(root) {
        if(root->left) {
            t->next = root->left; 
            t = t->next;
        }
        if(root->right) {
            t->next = root->right;
            t = t->next;
        }
        root = root->next;
    }
    connect(newHead.next);
}
```

Iterative

```
void connect(TreeLinkNode *root) {
    if(!root) return ;
    TreeLinkNode newHead(0), *t = NULL;
    t = &newHead;
    while(root) {
        while(root) {
            if(root->left) {
                t->next = root->left; 
                t = t->next;
            }
            if(root->right) {
                t->next = root->right;
                t = t->next;
            }
            root = root->next;
        }
        root = newHead.next;
        t = &newHead;
        t->next = NULL;
    }
}
```

#### Path Sum II
Given a binary tree and a sum, find all root-to-leaf paths where each path's sum equals the given sum.
For example:
Given the below binary tree and sum = 22,
```
              5
             / \
            4   8
           /   / \
          11  13  4
         /  \    / \
        7    2  5   1
```
return
[
[5,4,11,2],
[5,8,4,5]
]

```
class Solution {
private:
    void traverse(TreeNode* root, int sum, vector<int>& v, vector<vector<int>>& vv) {
        v.push_back(root->val);
        sum -= root->val;
        if(root->left || root->right) {
            if(root->left) traverse(root->left, sum, v, vv); 
            if(root->right) traverse(root->right, sum, v, vv); 
        }
        else if(sum == 0) vv.push_back(v); 
        v.pop_back();
    }
public:
    vector<vector<int>> pathSum(TreeNode* root, int sum) {
        if(!root) return vector<vector<int>>();
        vector<int> v;
        vector<vector<int>> vv;
        traverse(root, sum, v, vv);
        return vv;
    }
};
```
##### Check existence only
```
bool hasPathSum(TreeNode* root, int sum) {
	if(!root) return false;
	sum -= root->val;
	if(!root->left && !root->right) return sum == 0;
	return hasPathSum(root->left, sum) || hasPathSum(root->right, sum);
}
```
#### House Robber III
The thief has found himself a new place for his thievery again. There is only one entrance to this area, called the "root." Besides the root, each house has one and only one parent house. After a tour, the smart thief realized that "all houses in this place forms a binary tree". It will automatically contact the police if two directly-linked houses were broken into on the same night.  
Determine the maximum amount of money the thief can rob tonight without alerting the police.  
Example 1:
```
     3
    / \
   2   3
    \   \ 
     3   1
```
Maximum amount of money the thief can rob = 3 + 3 + 1 = 7.
Example 2:
```
     3
    / \
   4   5
  / \   \ 
 1   3   1
```
Maximum amount of money the thief can rob = 4 + 5 = 9.

Memoization solution using unordered_map
```
class Solution {
private: 
    unordered_map<TreeNode*, int> rob_map;
public:
    int rob(TreeNode* root) {
        if(!root) return 0;
        if(rob_map.count(root)) return rob_map[root];
        int withRoot = root->val;
        if(root->left) withRoot += rob(root->left->left)+rob(root->left->right);
        if(root->right) withRoot += rob(root->right->left)+rob(root->right->right);
        int withoutRoot = rob(root->left)+rob(root->right);
        return rob_map[root] = max(withRoot, withoutRoot);
    }
};
```

Using `reference` to record essential variables results in better performance
Actually we can return several values sometimes using reference.
```
class Solution {
private:
    int traverse(TreeNode* root, int& lMax, int& rMax) {
        if(!root) return 0;
        int ll = 0, lr = 0, rl = 0, rr = 0;
        lMax = traverse(root->left, ll, lr);
        rMax = traverse(root->right, rl, rr);
        return max(lMax+rMax, root->val+ll+lr+rl+rr);
    }
public:
    int rob(TreeNode* root) {
        int lMax = 0, rMax = 0;
        return traverse(root, lMax, rMax);
    }
};
```

#### Kth Smallest Element in a BST
Given a binary search tree, write a function kthSmallest to find the kth smallest element in it.Note: 
You may assume k is always valid, 1 ≤ k ≤ BST's total elements.

Quite efficient binary search method (actually we can also use in-order traversing methods including recursive version and Morris Traversal version).
```
class Solution {
private:
    int countNodes(TreeNode* root) {
        if(!root) return 0;
        return 1+countNodes(root->left)+countNodes(root->right);
    }
public:
    int kthSmallest(TreeNode* root, int k) {
        int lCount = countNodes(root->left);
        if(lCount == k-1) return root->val;
        else if(lCount > k-1) return kthSmallest(root->left, k);
        else return kthSmallest(root->right, k-lCount-1);
        return 0;
    }
};
```

```
int kthSmallest(TreeNode* root, int k) 
{
    int ret = 0;
    while(root) {
        if(!root->left) {
            if(--k == 0) ret = root->val;
            root = root->right;
        }
        else {
            TreeNode* pre = root->left;
            while(pre->right && pre->right!=root) pre = pre->right;
            if(!pre->right) {
                pre->right = root;
                root = root->left;
            }
            else {
                pre->right = NULL;
                if(--k == 0) ret = root->val;
                root = root->right;
            }
        }
    }
    return ret;
}
```
### Invert Binary Tree
Invert a binary tree.
```
     4
   /   \
  2     7
 / \   / \
1   3 6   9
to
     4
   /   \
  7     2
 / \   / \
9   6 3   1
```
> Trivia: This problem was inspired by this original tweet by Max Howell:
Google: 90% of our engineers use the software you wrote (Homebrew), but you can’t invert a binary tree on a whiteboard so fuck off.

[test](https://leetcode.com/problems/invert-binary-tree/)

### Solution
Explanation will be added.

```
TreeNode* invertTree(TreeNode* root) {
	if(!root) return NULL;
	invertTree(root->left);
	invertTree(root->right);
	swap(root->left, root->right);
	return root;
}
```
### Validate Binary Search Tree
Given a binary tree, determine if it is a valid binary search tree (BST).

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

[test](https://leetcode.com/problems/validate-binary-search-tree/)

### Solution
Explanation will be added.
```
class Solution {
public:
    bool isValidBST(TreeNode* root) {
        TreeNode* prev = NULL;
        return validate(root, prev);
    }
    bool validate(TreeNode* node, TreeNode* &prev) {
        if (node == NULL) return true;
        if (!validate(node->left, prev)) return false;
        if (prev != NULL && prev->val >= node->val) return false;
        prev = node;
        return validate(node->right, prev);
    }
};
```
### Minimum Depth of Binary Tree
Given a binary tree, find its minimum depth.  The minimum depth is the number of nodes along the shortest path from the root node down to the nearest leaf node.
[test](https://leetcode.com/problems/minimum-depth-of-binary-tree/)
### Solution
Explanation will be added.
```
int minDepth(TreeNode* root) {
    if(!root) return 0;
    if(!root->left && !root->right) return 1;
    if(!root->left) return 1+minDepth(root->right);
    if(!root->right) return 1+minDepth(root->left);
    return min(minDepth(root->left), minDepth(root->right))+1;
}
```

### Flatten Binary Tree to Linked List
Given a binary tree, flatten it to a linked list in-place.
```
For example,
Given
         1
        / \
       2   5
      / \   \
     3   4   6
The flattened tree should look like:
   1
    \
     2
      \
       3
        \
         4
          \
           5
            \
             6
```
[test](https://leetcode.com/problems/flatten-binary-tree-to-linked-list/)

### Solution
Explanation will be added.

```
void flatten(TreeNode* root) {
    if(!root) return ;
    TreeNode *right = root->right;
    if(root->left) {
        flatten(root->left);
        TreeNode *pre = root->left;
        while(pre->right) pre = pre->right;
        pre->right = root->right;
        root->right = root->left;
        root->left = NULL;
    }
    flatten(right);
}
```

### Binary Tree Paths
Given a binary tree, return all root-to-leaf paths.  For example, given the following binary tree:
```
   1
 /   \
2     3
 \
  5
```
All root-to-leaf paths are: ["1->2->5", "1->3"]

[test](https://leetcode.com/problems/binary-tree-paths/)

### Solution
Explanation will be added.
```
class Solution {
private:
    void traverse(TreeNode* root, string path, vector<string>& v) {
        if(!root->left && !root->right) { v.push_back(path); return ; }  
        if(root->left) traverse(root->left, path + "->"+to_string(root->left->val), v);
        if(root->right) traverse(root->right, path + "->"+to_string(root->right->val), v);
    }
public:
    vector<string> binaryTreePaths(TreeNode* root) {
        if(!root) return vector<string>();
        vector<string> v;
        traverse(root, to_string(root->val), v);
        return v;
    }
};
```
### Binary Tree Right Side View
Given a binary tree, imagine yourself standing on the right side of it, return the values of the nodes you can see ordered from top to bottom.

For example: Given the following binary tree,
```
   1            <---
 /   \
2     3         <---
 \     \
  5     4       <---
```
You should return [1, 3, 4].

[test](https://leetcode.com/problems/binary-tree-right-side-view/)

### Solution
Explanation will be added.
Using level-order traversal is trivial, here is a more clean way utilizing the pre-order feature.
```
class Solution {
public:
    void helper(TreeNode *root, int level, vector<int> &v) {
        if(root==NULL) return ;
        if(v.size()<level) v.push_back(root->val);
        helper(root->right, level+1, v);
        helper(root->left, level+1, v);
    }
    
    vector<int> rightSideView(TreeNode *root) {
        vector<int> v;
        helper(root, 1, v);
        return v;
    }
};
```
### Count Complete Tree Nodes
Given a complete binary tree, count the number of nodes.

Definition of a complete binary tree from Wikipedia:
In a complete binary tree every level, except possibly the last, is completely filled, and all nodes in the last level are as far left as possible. It can have between 1 and 2^h nodes inclusive at the last level h.

[test](https://leetcode.com/problems/count-complete-tree-nodes/)

### Solutions

#### Recursive
One direct clean solution is the recursive method as follows, checking the height of the left and right sub-trees:
- if they are equal then the left sub-tree can be retrieved by `1<<lHeight`(the left sub-tree will a complete binary tree) while the right is still unknown, which should be further handled by recursion; 
- if they are not equal then the right sub-tree can be retrieved by `1<<rHeight` while the left is unknown.

Time complexity will be O(log(n)^2) where n is the amount of nodes, space cost is O(1);

```
class Solution {
public:
    int countNodes(TreeNode* root) 
    {
        if(!root) return 0;
        int lHeight = 0, rHeight = 0;
        for(TreeNode* p = root->left; p; p = p->left) lHeight++;
        for(TreeNode* p = root->right; p; p = p->left) rHeight++;
        if(lHeight == rHeight) return countNodes(root->right)+(1<<lHeight);
        else return countNodes(root->left)+(1<<rHeight);
    }
};
```

#### Iterative
This method is inspired by the recursive one above but more delicate and efficient. We are going to measure the height of the tree first and then according to the feature of the complete tree (as left as possible), we are to count the last-level nodes by checking whether the rightmost of the left sub-tree meet the height of the tree. 

- If the level of the rightmost is not the level the height expects, then there must be some missing nodes for the left sub-tree in the last level, we will try the left sub-tree;
- Otherwise, we will count the last-level nodes of the left sub-tree and then try the right tree further.

Now, you don't need to check both sub-trees since you already get the height of the tree and then all you need to do is check the height of the sub-trees with the related levels.

```
class Solution 
{
public:
    int countNodes(TreeNode* root) 
    {
        if(!root) return 0;
        int height = 0, sum = 0;
        for(TreeNode* p = root; p; p = p->left) height++;
        int level = height-2;
        while(level > -1)
        {
            TreeNode *t = root->left;
            for(int i = 0; i < level; ++i) t = t->right;
            if(t) { root = root->right; sum += 1<<level; }
            else root= root->left;
            level--;
        }
        if(root) sum++;
        return sum + (1<<(height-1)) - 1;
    }
};
```

### Count Univalue Subtrees
Given a binary tree, count the number of uni-value subtrees.  A Uni-value subtree means all nodes of the subtree have the same value.
For example:
Given binary tree,
```
              5
             / \
            1   5
           / \   \
          5   5   5
```
return 4.

[test](https://leetcode.com/problems/count-univalue-subtrees/)

### Solution
Explanation will be added.

```
class Solution {
    bool isSame(TreeNode* root, int val, int& count){
        if(!root) return true;
        if(!isSame(root->left, root->val, count) | !isSame(root->right, root->val, count)) return false;
        count++;
        return root->val == val;
    }
public:
    int countUnivalSubtrees(TreeNode* root) {
        int count = 0;
        isSame(root, 0, count);
        return count;
    }
};
```
### Binary Tree Longest Consecutive Sequence
Given a binary tree, find the length of the longest consecutive sequence path (ascending order). The path refers to any sequence of nodes from some starting node to any node in the tree along the parent-child connections. The longest consecutive path need to be from parent to child (cannot be the reverse).
```
For example,
   1
    \
     3
    / \
   2   4
        \
         5
Longest consecutive sequence path is 3-4-5, so return 3.
   2
    \
     3
    / 
   2    
  / 
 1
Longest consecutive sequence path is 2-3,not3-2-1, so return 2.
```
[test](https://leetcode.com/problems/binary-tree-longest-consecutive-sequence/)

### Solution
> **Note** The `len` here refers to the maximal consecutive length till the current node, including the current.

```
class Solution {
public:
    int longestConsecutive(TreeNode* root) {
        return search(root, nullptr, 0);
    }
    
    int search(TreeNode *root, TreeNode *parent, int len) {
        if (!root) return len;
        len = (parent && root->val==parent->val + 1)? len+1:1;
        return max(len, max(search(root->left, root, len), search(root->right, root, len)));
    }
};
```
### Verify Preorder Serialization of a Binary Tree
One way to serialize a binary tree is to use pre-order traversal. When we encounter a non-null node, we record the node's value. If it is a null node, we record using a sentinel value such as #.
```
     _9_
    /   \
   3     2
  / \   / \
 4   1  #  6
/ \ / \   / \
# # # #   # #
```
For example, the above binary tree can be serialized to the string "9,3,4,#,#,1,#,#,2,#,6,#,#", where # represents a null node.  
Given a string of comma separated values, verify whether it is a correct preorder traversal serialization of a binary tree. Find an algorithm without reconstructing the tree.  
Each comma separated value in the string must be either an integer or a character '#' representing null pointer.  
You may assume that the input format is always valid, for example it could never contain two consecutive commas such as "1,,3".  

- Example 1:
"9,3,4,#,#,1,#,#,2,#,6,#,#"
Return true 

- Example 2:
"1,#"
Return false 

- Example 3:
"9,#,#,1"
Return false


### Solution

Let's analyse this problem first: it's a binary tree and it's traversed in pre-order. Then there are two points right here:

- `empty nodes` can only be children
- parents always go before children

According to binary tree, we also know that the amount of `empty`nodes will exactly larger than `non-empty` nodes by one. So before we reach the end: the amount of `empty` nodes can never be larger and when reaching the end, it will be exactly one.

How are we going to check the empty and non-empty? 

- quite simple here, since the nodes are separated by `comma`, we can just traverse the string and once encountering a comma, we check its previous character, if it's `#` which represents empty nodes otherwise non-empty ones; as for the last node, we are about to take advantage of the termination character `\0` as another splitter, same as comma to ensure cleanness of code.

The solution will be as follows then.

```
bool isValidSerialization(string preorder) 
{
    int len = preorder.length(), diff = 0;
    for(int i = 0; i <= len; ++i)
    {
        if(preorder[i]==',' || preorder[i]=='\0')
        {
            if(preorder[i-1] == '#') diff++;
            else diff--;
            if(diff==1 && i==len) return true;
            if(diff > 0) return false;
        }
    }
    return diff == 1;
}
```
### Verify Preorder Sequence in Binary Search Tree
Given an array of numbers, verify whether it is the correct preorder traversal sequence of a binary search tree.  You may assume each number in the sequence is unique.

> Follow up: Could you do it using only constant space complexity?

[test](https://leetcode.com/problems/verify-preorder-sequence-in-binary-search-tree/)
### Solution
Explanation will be added.
#### Recursive - 120ms
```
class Solution {
    bool verify(vector<int>::iterator begin, vector<int>::iterator end, int low, int high){
        if(begin > end) return true;
        if(*begin<low || *begin>high) return false;
        auto newBegin = upper_bound(begin, end+1, *begin); //uppder_bound searching range - [);
        return verify(begin+1, newBegin-1, low, *begin) && verify(newBegin, end, *begin, high);
    }
public:
    bool verifyPreorder(vector<int>& preorder) {
        if(preorder.empty()) return true;
        return verify(preorder.begin(), preorder.end()-1, INT_MIN, INT_MAX);
    }
};
```
#### Iterative - 60ms
```
bool verifyPreorder(vector<int>& preorder) {
	int low = INT_MIN;
	vector<int> v;
	for(auto p: preorder){
		if(p < low) return false;
		while(v.size() && v.back()<p){ //retrieve the parent;
			low = v.back();
			v.pop_back();
		} 
		v.push_back(p);
	}
	return true;
}
```
### Closest Binary Search Tree Value
Given a non-empty binary search tree and a target value, find the value in the BST that is closest to the target.  
Note: Given target value is a floating point.  You are guaranteed to have only one unique value in the BST that is closest to the target.
> Follow-up: what if searching out k closest values and you may assume k is always valid, that is: k ≤ total nodes.  You are guaranteed to have only one unique set of k values in the BST that are closest to the target.

### Solution
Explanation will be added.
#### Primitive
[test](https://leetcode.com/problems/closest-binary-search-tree-value/)
```
class Solution {
public:
    int closestValue(TreeNode* root, double target) {
        int ret = root->val;
        while(root){
            if(fabs(ret-target) > fabs(root->val-target)) ret = root->val;
            root = root->val>target? root->left:root->right;
        }
        return ret;
    }
};
```
#### Follow-up
[test](https://leetcode.com/problems/closest-binary-search-tree-value-ii/)
##### Priority_queue
```
class Solution {
private:
    priority_queue<pair<double, int>> minHeap;
public:
    vector<int> closestKValues(TreeNode* root, double target, int k) {
        vector<int> res;
        traverse(root, target, k);
        while(minHeap.size()){
            res.push_back(minHeap.top().second);
            minHeap.pop();
        }
        return res;
    }
    
    void traverse(TreeNode* root, double target, int k){
        if(root == NULL) return;
        double diff = abs(root->val-target);
        minHeap.push({diff, root->val});
        if(minHeap.size() > k) minHeap.pop();
        traverse(root->left, target, k);
        traverse(root->right, target, k);
    }
};
```
##### In-order
```
class Solution {
    void inorder(TreeNode* root, double target, bool isReversed, vector<int>& v){
        if(!root) return ;
        inorder(isReversed? root->right:root->left, target, isReversed, v);
        if((isReversed&&root->val<target) || (!isReversed&&root->val>=target)) return ;
        v.push_back(root->val);
        inorder(isReversed? root->left:root->right, target, isReversed, v);
    }
public:
    vector<int> closestKValues(TreeNode* root, double target, int k) {
        vector<int> v0, v1;
        inorder(root, target, false, v0);
        inorder(root, target, true, v1);
        vector<int> v;
        int i = v0.size()-1, j = v1.size()-1;
        while(k--) v.push_back((j<0 || (i>=0&&fabs(v0[i]-target)<fabs(v1[j]-target)))? v0[i--]:v1[j--]);
        return v;
    }
};
```
### Largest BST Subtree
Given a binary tree, find the largest subtree which is a Binary Search Tree (BST), where largest means subtree with largest number of nodes in it.

Note:
A subtree must include all of its descendants.
Here's an example:
```
    10              
    / \
   5  15           5
  / \   \         / \
 1   8   7       1   8
```
The Largest BST Subtree in this case is the highlighted one. 
The return value is the subtree's size, which is 3.
> Follow up: Can you figure out ways to solve it with O(n) time complexity?

[test](https://leetcode.com/problems/largest-bst-subtree/)
### Solution
Explanation will be added.

```
class Solution {
    bool isBST(TreeNode* root, int& maxSize, int& low, int& high){
        if(!root) return true;
        int lMaxSize = 0, rMaxSize = 0;
        int lLow = 0, lHigh = 0, rLow = 0, rHigh = 0;
        bool lResult = isBST(root->left, lMaxSize, lLow, lHigh);
        bool rResult = isBST(root->right, rMaxSize, rLow, rHigh);
        if(lResult && rResult){
            if((!root->left || root->val>lHigh) && (!root->right || root->val<rLow)){
                maxSize = lMaxSize+rMaxSize+1;
                low = root->left? lLow:root->val;
                high = root->right? rHigh:root->val;
                return true;
            }
        }
        maxSize = max(lMaxSize, rMaxSize);
        return false;
    }
public:
    int largestBSTSubtree(TreeNode* root) {
        int maxSize = 0, low = 0, high = 0;
        isBST(root, maxSize, low, high);
        return maxSize;
    }
};
```
### Find Leaves of Binary Tree
Given a binary tree, collect a tree's nodes as if you were doing this: Collect and remove all leaves, repeat until the tree is empty.
```
Example:
Given binary tree 
          1
         / \
        2   3
       / \     
      4   5    
Returns [4, 5, 3], [2], [1].

Explanation:
1. Removing the leaves [4, 5, 3] would result in this tree: 
          1
         / 
        2          
2. Now removing the leaf [2] would result in this tree: 1          
3. Now removing the leaf [1] would result in the empty tree: []         
Returns [4, 5, 3], [2], [1].
```

[test](https://leetcode.com/problems/find-leaves-of-binary-tree/)

### Solution
Explanation will be added.

```
class Solution {
    int retrieveLevel(TreeNode* root, vector<vector<int>>& vv){
        if(!root) return 0;
        int level = max(retrieveLevel(root->left, vv), retrieveLevel(root->right, vv))+1;
        if(vv.size() < level) vv.push_back(vector<int>());
        vv[level-1].push_back(root->val);
        return level;
    }
public:
    vector<vector<int>> findLeaves(TreeNode* root) {
        vector<vector<int>> vv;
        retrieveLevel(root, vv);
        return vv;
    }
};
```
### Binary Tree Upside Down
Given a binary tree where all the right nodes are either leaf nodes with a sibling (a left node that shares the same parent node) or empty, flip it upside down and turn it into a tree where the original right nodes turned into left leaf nodes. Return the new root.
```
For example:
Given a binary tree {1,2,3,4,5},
    1
   / \
  2   3
 / \
4   5
return the root of the binary tree [4,5,2,#,#,3,1].
   4
  / \
 5   2
    / \
   3   1  
```
[test](https://leetcode.com/problems/binary-tree-upside-down/)

### Solution
Explanation will be added.

```
TreeNode* upsideDownBinaryTree(TreeNode* root) {
	if(!root || (!root->left&&!root->right)) return root;
	TreeNode *newRoot = upsideDownBinaryTree(root->left);
	root->left->left = root->right;
	root->left->right = root;
	root->left = root->right = NULL;
	return newRoot;
}
```
